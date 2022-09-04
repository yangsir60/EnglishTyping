#include "qt5test.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qt5test w;
	w.show();
	return a.exec();
}
