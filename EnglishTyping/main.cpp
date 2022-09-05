#include "englishtyping.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	EnglishTyping w;
	//w.resize(280, 300-30);
	//w.resize(280 - 2, 300 - 32);
	w.resize(280 - 2, 200);
	//w.resize(200, 200);
	w.show();
	return a.exec();
}
