#ifndef MAKESPRITES_H
#define MAKESPRITES_H

#include <QtWidgets/QDialog>
#include "ui_makesprites.h"

class MakeSprites : public QDialog
{
	Q_OBJECT

public:
	MakeSprites(QWidget *parent = 0);
	~MakeSprites();

private:
	Ui::MakeSpritesClass ui;

	void readSettings();
	void saveSettings();

	void closeEvent(QCloseEvent *e);
public slots:

	void on_butPathLink_clicked(); 
	void on_butPathFX_clicked(); 
	void on_butFileName_clicked();
	void on_butSave_clicked();

	void slot_message(QString msg);
};

#endif // MAKESPRITES_H
