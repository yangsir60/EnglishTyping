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
		emit enterPressed(ui.lineEdit->text());  // �����س������µ��źŲ�����������е��ı�
		event->accept();  // �����¼�����ֹ��������
	}
	else {
		QWidget::keyPressEvent(event);  // ������λ���¼��������ദ��
	}
}

