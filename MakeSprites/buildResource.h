#pragma once
#include <QObject>
#include <QList>
#include <QString>


#define QTEXT(s)(QString::fromLocal8Bit(s))
///--------------------------------------------------------------------------------------








   
 ///=====================================================================================
///
/// Базовый класс сборщика ресурсов
/// 
/// 
///--------------------------------------------------------------------------------------
class 
	ABuildResource
		:
			public QObject
{
	Q_OBJECT


public:
	ABuildResource(const QString &fileName);
	virtual ~ABuildResource();




protected:



	void setError(const QString &error);//Установка ошибки
	void message(const QString &msg);//отсылка сообщения
	
	QString contentPath() const; //возвратим текущий католог где можно сохранять файлы
	QString exportFileName() const; //название главного файла для экспорта
	QString	baseFileName() const; //имя файла без расширения


	bool saveFile(const QString &fileName, const QString &xml); //сохранение файла на диск




private:

	QString mFileName;
	QString mError;

signals:

	void signal_message(QString msg);
};


