#pragma once
#include "buildResource.h"
#include <QList>
#include <QPixmap>
#include <QMap>
///--------------------------------------------------------------------------------------






//������������ ����������� ������
#define ATLAS_WIDTH		1024	//
#define ATLAS_HEIGHT	1024	//


//
// �������� ������ ��������
// ��� ������� ����������� � ��������� ����������� � ������
// 
// ������, �������� ��������� � ������, ����� ������������� ����� ���� DWORD
// NNNNXXYY
//			NNNN	- ����� ������ �������
//			XX		- ������������ � ������ �� ����������� �� 0 �� 255
//			YY		- ������������ � ������ �� ��������� �� 0 �� 255
//
//
// ������ ������� ����� ����� �� 0 �� 0000NNNN �� �������� �������
//







///--------------------------------------------------------------------------------------
/// ��������� ������ ������� �� ��������
struct TSprite
{
	int				number;	//��������������� ����� �������
	QString			name;	//�������� �������
	QPixmap			image;  //���� ��� �����, �� ��������




	//constructor 2
	TSprite(const int number, const QString &name, const QPixmap& image)
		:
		number(number),
		name(name),
		image(image)

	{
	}
	//
};
///--------------------------------------------------------------------------------------



///--------------------------------------------------------------------------------------
typedef QList<TSprite> AListSprite;//������ ��������
///--------------------------------------------------------------------------------------







   
 ///=====================================================================================
///
/// ��������� ��������
/// 
/// 
///--------------------------------------------------------------------------------------
class 
	ASprite
		:
			public ABuildResource
{
	Q_OBJECT


public:
	ASprite(const QString &fileName);
	virtual ~ASprite();


	bool generate(const QString &pathLink, const QString &pathFX); //��������� ��������
	bool findSprite(const int number) const;
	int  findSpriteAtlas(const QString &name) const;


protected:


	

	
	bool linkedAtlas();//�������� �������� �������
	
	bool linkedFiles(const QString &filePath);//������������ �������� �� ����������
	bool linkedFilesFXtoAtlas(const QString &filePath);//������������ ������������ �� ����������

	bool saveToFiles(); //���������� ������ �� ����
	bool saveToSource();//������������� �������� �������� � ����

	int getIdentitySpriteNumber() const; //����� ���������� ����� ��� ���������� �������


private:

	AListSprite	mSprites;	//������ ��������
	AListSprite mSpriteAtlas; //������ �������� � ������
	int			mSizeSpriteAtlas; //������ ������ �������� � �������

	QMap<QString, int> mFrame; //������ ��� ������� ��������


};


