#ifndef QT5TEST_H
#define QT5TEST_H

#include <QtWidgets/QMainWindow>
#include "ui_qt5test.h"

class qt5test : public QMainWindow
{
	Q_OBJECT

public:
	qt5test(QWidget *parent = 0);
	~qt5test();

private:
	Ui::qt5testClass ui;
};

#endif // QT5TEST_H
