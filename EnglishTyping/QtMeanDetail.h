#pragma once

#include <QKeyEvent>
#include <QWidget>
#include "ui_QtMeanDetail.h"

class QtMeanDetail : public QWidget
{
	Q_OBJECT

public:
	QtMeanDetail(QWidget *parent = Q_NULLPTR);
	~QtMeanDetail();
	Ui::QtMeanDetail ui;
	void keyPressEvent(QKeyEvent *event);
private:

signals :
	void enterPressed(const QString& text);  // 回车键按下的信号
};
