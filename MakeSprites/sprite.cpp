#include "sprite.h"


#include <QDir>
#include <QPixmap>
#include <QPainter>


///--------------------------------------------------------------------------------------






   
 ///=====================================================================================
///
/// constructor
/// 
/// 
///--------------------------------------------------------------------------------------
ASprite :: ASprite (const QString &fileName)
	:
	ABuildResource(fileName)
{


}
///--------------------------------------------------------------------------------------






   
 ///=====================================================================================
///
/// destructor
/// 
/// 
///--------------------------------------------------------------------------------------
ASprite :: ~ASprite ()
{


}
///--------------------------------------------------------------------------------------






   
 ///=====================================================================================
///
/// ��������� ��������
/// 
/// 
///--------------------------------------------------------------------------------------
bool ASprite :: generate(const QString &pathLink, const QString &pathFX)
{
	setError(QString());

	message(QTEXT("��������� ��������...\n"));
	message(QTEXT("������� ����������� � �������� Autoload\n"));
	mSprites.clear();




	
	message(QTEXT("������ 1...\n����������\n"));
	
	//����� ���� � ������� ��� ��������
	linkedFilesFXtoAtlas(pathFX);


	/*
	for (AListSprite::iterator item = mSpriteAtlas.begin(); item != mSpriteAtlas.end(); ++item)
	{
		item->image.save(QTEXT("D:\\SP\\") + item->name + QTEXT(".png"), "PNG");
	}*/


	message(QTEXT("\n\n ������ 2...\n������\n"));
	linkedAtlas();



	//������ 2. ������� ������� ��������� � ���������� linked
	message(QTEXT("\n\n������ 3...\n������� ��� ��������\n"));
	
	//����� ���� � ������� ��� ��������
	linkedFiles(pathLink);
	//







	//���������� �������� �� ����
	if (!saveToFiles())
	{
		//��������� ������ ��� ���������� ������
		return false;
	}

	if (saveToSource())
	{
		//������ ��� ��������� ���� � ��������� ��������
		return false;
	}
	message(QTEXT("\n\n����� ��������: ") + QString::number(mSprites.count()));
	message("\n");
	return true;
}
///--------------------------------------------------------------------------------------













   
 ///=====================================================================================
///
/// ������������ �������� �� ����������
/// 
/// 
///--------------------------------------------------------------------------------------
bool ASprite :: linkedFiles(const QString &filePath)
{
	message(QTEXT("Linked: ") + filePath + QTEXT("\n"));
	QDir dir(filePath);
	QStringList listFiles = dir.entryList(QDir::NoDotAndDotDot | QDir::Files);
	for (int index = 0; index < listFiles.count(); index++)
	{
		QString sFileName = dir.absoluteFilePath(listFiles[index]);
		
		

		const QPixmap image(sFileName);
		if (!image.isNull())
		{
			QFileInfo info(sFileName);
			QString sName = info.baseName();
			int iNumber = getIdentitySpriteNumber();
			mSprites.push_back(TSprite(iNumber, sName, image));
			message(QTEXT(" number: ")+QString::number(iNumber) + QTEXT("\t name: ") + sName);
		}


		

	}
	return true;
}
///--------------------------------------------------------------------------------------












   
 ///=====================================================================================
///
/// ������������ ������������ �� ����������
/// 
/// 
///--------------------------------------------------------------------------------------
bool ASprite :: linkedFilesFXtoAtlas(const QString &filePath)
{
	message(QTEXT("Linked FX: ") + filePath + QTEXT("\n"));
	QDir dir(filePath);
	QStringList listFiles = dir.entryList(QDir::NoDotAndDotDot | QDir::Files);
	for (int index = 0; index < listFiles.count(); index++)
	{
		QString sFileName = dir.absoluteFilePath(listFiles[index]);
		
		

		const QPixmap image(sFileName);
		if (!image.isNull())
		{
			QFileInfo info(sFileName);
			QString sName = info.baseName();
			message(QTEXT("\t name: ") + sName);


			int wh = image.height();
			int count = image.width() / wh;
			if ((image.width() % wh) != 0)
			{
				message(QTEXT(" ERROR size!!!!\n\n\n"));
				continue;
			}
			message(QTEXT("\t count: ") + QString::number(count) + QTEXT(", \t wh: ") + QString::number(wh));
			
			for (int i = 0; i < count; i++)
			{
				QString sNameFrame = sName;
				if (count > 1)
				{
					sNameFrame = sName+QTEXT("_frame") + QString::number(i);
				}
				QPixmap sprite = image.copy(wh * i, 0, wh, wh);
				mSpriteAtlas.push_back(TSprite(0, sNameFrame, sprite));
			}

			mFrame[sName] = count;
			message(QTEXT("\n"));
		}


		

	}
	message(QTEXT("\n"));
	return true;
}
///--------------------------------------------------------------------------------------









   
 ///=====================================================================================
///
/// �������� �������� �������
/// 
/// 
///--------------------------------------------------------------------------------------
bool ASprite :: linkedAtlas()
{
	message(QTEXT("\n\n\n................................\nLinked atlas\n"));



	if (mSpriteAtlas.empty())
	{
		return true;
	}
	mSizeSpriteAtlas = mSpriteAtlas[0].image.width();

	//������� ������
	//� ������� � 1 �������
	message(QTEXT("\n�������� �������\n"));
	QPixmap atlas(ATLAS_WIDTH, ATLAS_HEIGHT);
	atlas.fill(Qt::transparent);

	int margin = 0;//1

	const int atlasCol = (ATLAS_WIDTH - margin) / (mSizeSpriteAtlas + margin);
	const int atlasRow = (ATLAS_HEIGHT - margin) / (mSizeSpriteAtlas + margin);

	int xCount = 0;
	int yCount = 0;
	int numberAtlas = 1; //����� �������� ������



	QPainter *paint = new QPainter(&atlas); //���������
	for (AListSprite::iterator item = mSpriteAtlas.begin(); item != mSpriteAtlas.end(); ++item)
	{
		if (yCount >= atlasRow)
		{
			//�������� ���������� ������
			message(QTEXT("\n atlas_") + QString::number(numberAtlas) + QTEXT("\n"));
			mSprites.push_back(TSprite(numberAtlas, QTEXT("atlas_") + QString::number(numberAtlas), atlas.copy()));
			numberAtlas++;
			xCount = 0;
			yCount = 0;
			atlas.fill(Qt::transparent);
		}

		paint->drawPixmap((int)(xCount * (mSizeSpriteAtlas + margin) + margin), (int)(yCount * (mSizeSpriteAtlas + margin) + margin), item->image);
		item->number = (numberAtlas << 0x10)  | (xCount << 0x8) | (yCount);

		
		//��������� ������
		xCount++;
		if (xCount >= atlasCol)
		{
			xCount = 0;
			yCount++;
		}
	}
	delete paint;
	if (xCount > 0)
	{
		yCount++;
	}

	if (xCount > 0 || yCount > 0)
	{
		//�������� ���������� ������
		int atlasWidth = ATLAS_WIDTH;
		int atlasHeight = yCount * (mSizeSpriteAtlas + margin) + margin;
		int height = 2;
		while (height < atlasHeight)
		{
			height = height * 2;
		}
		atlasHeight = height;

		QRect rect(0, 0, atlasWidth, atlasHeight);
		message(QTEXT("\n atlas_") + QString::number(numberAtlas) + QTEXT("\n"));
		mSprites.push_back(TSprite(numberAtlas, QTEXT("atlas_") + QString::number(numberAtlas), atlas.copy(rect)));
	}
	//

	return true;
}
///--------------------------------------------------------------------------------------




   
 ///=====================================================================================
///
/// ����� ����� �� ��� ������
/// 
/// 
///--------------------------------------------------------------------------------------
bool ASprite :: findSprite(const int number) const
{
	for (AListSprite::const_iterator item = mSprites.begin();
			item != mSprites.end();
				++item)
	{
		if (item->number == number)
		{
			return true;
		}
	}
	return false;
}
///--------------------------------------------------------------------------------------








   
 ///=====================================================================================
///
/// ������ ������� �� ��� ��������
/// 
/// 
///--------------------------------------------------------------------------------------
int ASprite :: findSpriteAtlas(const QString &name) const
{
	for (AListSprite::const_iterator item = mSpriteAtlas.begin();
			item != mSpriteAtlas.end();
				++item)
	{
		if (item->name == name)
		{
			return item->number;
		}
	}
	return -1;
}
///--------------------------------------------------------------------------------------





   
 ///=====================================================================================
///
/// ����� ���������� ����� ��� ���������� �������
/// 
/// 
///--------------------------------------------------------------------------------------
int ASprite :: getIdentitySpriteNumber() const
{
	int iNumber = 1;
	while (findSprite(iNumber))
	{
		iNumber++;
	}
	return iNumber;
}
///--------------------------------------------------------------------------------------










 ///=====================================================================================
///
/// ���������� ������ �� ����
/// 
/// 
///--------------------------------------------------------------------------------------
bool ASprite :: saveToFiles()
{
	QString sRootPath = contentPath() + QDir::separator() + QTEXT("Autoload") + QDir::separator();
	
	//���������� �� ���� �������� � �������� �� �� ����
	for (AListSprite::const_iterator item = mSprites.begin();
			item != mSprites.end();
				++item)
	{

		//������� ��������� ���������		
		int iFolder = (item->number / 100) * 100;
		QString sPath = sRootPath + QString::number(iFolder);
		QDir dir(sPath);
		if (!dir.exists())
		{
			if (!dir.mkpath(sPath))
			{
				setError(sPath + QTEXT(" ������� �� ������!!!"));
				return false;
			}
		}

		//��������� ����
		QString sFileName = sPath + QDir::separator() + QString::number(item->number) + QTEXT(".PNG");
		QFile::remove(sFileName);

		const QPixmap &image = item->image;
		if (!image.save(sFileName, "PNG", 100))
		{
			setError(sFileName + QTEXT(" �� ��������!!!"));
			return false;
		}
	
	}
	return true;
}
///--------------------------------------------------------------------------------------










 ///=====================================================================================
///
/// ������������� �������� �������� � ����
/// 
/// 
///--------------------------------------------------------------------------------------
bool ASprite :: saveToSource()
{
	QString sFileName = contentPath() + QDir::separator();
	sFileName += QTEXT("SpriteDescription.cs");


	QString source = QTEXT("#region Using framework\n"
		"using System;\n"
		"#endregion\n"

		"\t ///=====================================================================================\n"
		"\t///\n"
		"\t/// <summary>\n"
		"\t/// �������������� ��������� �����\n"
		"\t/// �������� ���� ��������\n"
		"\t/// </summary>\n"
		"\t/// \n"
		"\t///--------------------------------------------------------------------------------------\n"
		"\tpublic class sprite\n"
		"\t{\n");

	for (AListSprite::const_iterator item = mSprites.begin();
			item != mSprites.end();
				++item)
	{
		QString sName = item->name;
		if (!sName.isEmpty())
		{
			source += QTEXT("\t\tpublic const uint ") + sName + QTEXT(" = ") + QString::number(item->number) + QTEXT(";\n");
		}
	}


	source += QTEXT("\n\t\t/// ������� ����������� � �������\n");
	for (AListSprite::const_iterator item = mSpriteAtlas.begin();
			item != mSpriteAtlas.end();
				++item)
	{
		QString sName = item->name;
		if (!sName.isEmpty())
		{
			source += QTEXT("\t\tpublic const uint ") + sName + QTEXT(" = ") + QString::number(item->number) + QTEXT(";\n");
		}
	}
	source += QTEXT("\n");



	source += QTEXT("\n\t\t/// �������� ������� � �������\n");
	const QStringList nameFrames = mFrame.keys();
	foreach(QString nameFrame, nameFrames)
	{
		//static public readonly uint[] fx_shapes_7 = { 0, 2, 3 };
		const int count = mFrame[nameFrame];
		if (count <= 1)
		{
			continue;
		}
		QStringList arrayFrame;
		for (int i = 0; i < count; i++)
		{
			QString name = nameFrame + QTEXT("_frame") + QString::number(i);
			int number = findSpriteAtlas(name);
			if (number > 0)
			{
				arrayFrame.append(QString::number(number));
			}
			else
			{
				message(QTEXT("\n\nerror!!!!! : ") + name);
			}
		}
		source += QTEXT("\t\tpublic static readonly uint[] ") + nameFrame + QTEXT(" = {") + arrayFrame.join(",") + QTEXT("};\n");
	}
	source += QTEXT("\n");



	//����� ���������� ��������
	source += QTEXT("\n\t\t/// <summary>\n"
        "\t\t/// ����� ���������� ��������\n"
        "\t\t/// </summary>\n"
		"\t\tpublic const int count = ")+ QString::number(mSprites.count()) + QTEXT(";\n");



	//������������ ����� ��������
	int maxNumber = mSprites.first().number;
	for (AListSprite::const_iterator item = mSprites.begin(); item != mSprites.end(); ++item)
	{
		if (item->number > maxNumber)
		{
			maxNumber = item->number;
		}
	}
	source += QTEXT("\n\t\t/// <summary>\n"
        "\t\t/// ������������ ����� �������\n"
        "\t\t/// </summary>\n"
		"\t\tpublic const int maxNumber = ")+ QString::number(maxNumber) + QTEXT(";\n");




	source += QTEXT("\t\t/// <summary>\n"
        "\t\t/// ����������� ������ ������� � �������\n"
        "\t\t/// </summary>\n"
        "\t\tpublic const int sizeAtlas = ");
	
	source += QString::number(mSizeSpriteAtlas);

	source += QTEXT(";\n"

		"\t}\n");


	saveFile(sFileName, source);

	return false;
}