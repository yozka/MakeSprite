#pragma once
#include <QObject>
#include <QList>
#include <QString>


#define QTEXT(s)(QString::fromLocal8Bit(s))
///--------------------------------------------------------------------------------------








   
 ///=====================================================================================
///
/// ������� ����� �������� ��������
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



	void setError(const QString &error);//��������� ������
	void message(const QString &msg);//������� ���������
	
	QString contentPath() const; //��������� ������� ������� ��� ����� ��������� �����
	QString exportFileName() const; //�������� �������� ����� ��� ��������
	QString	baseFileName() const; //��� ����� ��� ����������


	bool saveFile(const QString &fileName, const QString &xml); //���������� ����� �� ����




private:

	QString mFileName;
	QString mError;

signals:

	void signal_message(QString msg);
};


