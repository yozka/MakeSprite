#include "makesprites.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MakeSprites w;
	w.show();
	return a.exec();
}
