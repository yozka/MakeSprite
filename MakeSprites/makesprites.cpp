#include "makesprites.h"
#include "sprite.h"

#include <QFileDialog>
#include <QSettings>
#include <QCloseEvent>




MakeSprites::MakeSprites(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	readSettings();
}

MakeSprites::~MakeSprites()
{

}

void MakeSprites::readSettings()
{
	QSettings settings("hexotreeoptions");
	ui.pathLink->setText(settings.value("pathLink", "").toString());
	ui.pathFX->setText(settings.value("pathFX", "").toString());
	ui.fileName->setText(settings.value("fileName", "").toString());
	
	
	
}

void MakeSprites::closeEvent(QCloseEvent *e)
{
      saveSettings();
      e->accept();

}


void MakeSprites::saveSettings()
{
	QSettings settings("hexotreeoptions");
	settings.setValue("pathLink", ui.pathLink->text());
	settings.setValue("pathFX", ui.pathFX->text());
	settings.setValue("fileName", ui.fileName->text());


}



void MakeSprites::on_butPathLink_clicked()
{
	QString pathLink = ui.pathLink->text();
	pathLink = QFileDialog::getExistingDirectory(this, tr("Open Directory images"),
                                             pathLink,
                                             QFileDialog::ShowDirsOnly
                                             | QFileDialog::DontResolveSymlinks);
	if (!pathLink.isEmpty())
	{
		ui.pathLink->setText(pathLink);
	}

}



void MakeSprites::on_butPathFX_clicked()
{
	QString pathFX = ui.pathFX->text();
	pathFX = QFileDialog::getExistingDirectory(this, tr("Open Directory FX images"),
                                             pathFX,
                                             QFileDialog::ShowDirsOnly
                                             | QFileDialog::DontResolveSymlinks);
	if (!pathFX.isEmpty())
	{
		ui.pathFX->setText(pathFX);
	}

}


void MakeSprites::on_butFileName_clicked()
{
	QString fileName = ui.fileName->text();
	fileName = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("Скрипт программы для линковки"), fileName);
	if (!fileName.isEmpty())
	{
		ui.fileName->setText(fileName);
	}
}



void MakeSprites::slot_message(QString msg)
{
	ui.info->append(msg);
}

void MakeSprites::on_butSave_clicked()
{
	ui.info->clear();

	ASprite sprite(ui.fileName->text());
	connect(&sprite, SIGNAL(signal_message(QString)), this, SLOT(slot_message(QString)));
	sprite.generate(ui.pathLink->text(), ui.pathFX->text());


}