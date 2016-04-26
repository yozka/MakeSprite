#pragma once
#include "buildResource.h"
#include <QList>
#include <QPixmap>
#include <QMap>
///--------------------------------------------------------------------------------------






//максимальная размерность атласа
#define ATLAS_WIDTH		1024	//
#define ATLAS_HEIGHT	1024	//


//
// описание атласа спрайтов
// все спрайты находящиеся в тайлсетах склеиваются в атласы
// 
// спрайт, кооторый находится в атласе, имеет шестетеричный номер типа DWORD
// NNNNXXYY
//			NNNN	- номер атласа спрайта
//			XX		- распоолжение в атласе по горизонтале от 0 до 255
//			YY		- расположение в атласе по вертикале от 0 до 255
//
//
// спрайт который имеет номер от 0 до 0000NNNN не является атласом
//







///--------------------------------------------------------------------------------------
/// структура одного спрайта из тайлсета
struct TSprite
{
	int				number;	//сгенерированный номер спрайта
	QString			name;	//название спрайта
	QPixmap			image;  //если нет тайла, то картинка




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
typedef QList<TSprite> AListSprite;//список спрайтов
///--------------------------------------------------------------------------------------







   
 ///=====================================================================================
///
/// Генератор спрайтов
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


	bool generate(const QString &pathLink, const QString &pathFX); //генератор спрайтов
	bool findSprite(const int number) const;
	int  findSpriteAtlas(const QString &name) const;


protected:


	

	
	bool linkedAtlas();//создание спрайтов атласов
	
	bool linkedFiles(const QString &filePath);//вытаскивание спрайтов из директории
	bool linkedFilesFXtoAtlas(const QString &filePath);//вытаскивание спецеффектов из директории

	bool saveToFiles(); //сохранение файлов на диск
	bool saveToSource();//Сгенирировать описание спрайтов в файл

	int getIdentitySpriteNumber() const; //взять порядковый номер для свободного спрайта


private:

	AListSprite	mSprites;	//список спрайтов
	AListSprite mSpriteAtlas; //список спрайтов в атласе
	int			mSizeSpriteAtlas; //размер файлов картинок в атласах

	QMap<QString, int> mFrame; //фреймы для атласов анимации


};


