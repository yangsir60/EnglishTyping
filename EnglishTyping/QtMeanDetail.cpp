#include "QtMeanDetail.h"

QtMeanDetail::QtMeanDetail(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

QtMeanDetail::~QtMeanDetail()
{
}

void QtMeanDetail::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
		emit enterPressed(ui.lineEdit->text());  // 发出回车键按下的信号并传递输入框中的文本
		event->accept();  // 接受事件，防止继续传递
	}
	else {
		QWidget::keyPressEvent(event);  // 其他键位的事件交给父类处理
	}
}

