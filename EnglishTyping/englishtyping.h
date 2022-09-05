#ifndef ENGLISHTYPING_H
#define ENGLISHTYPING_H

#include <QtWidgets/QMainWindow>
#include "ui_englishtyping.h"
#include <QVector>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <regex>
#include <utilsinifile.h>
#include <utilsfiles.h>
#include <QtNetwork/QtNetwork>
class EnglishTyping : public QMainWindow
{
	Q_OBJECT

public:
	EnglishTyping(QWidget *parent = 0);
	~EnglishTyping();
	QString JsonToQstring(QJsonObject jsonObject);
	void buildConnectWay();
	void moXie001();//����001Ĭд����;
	void start001();
	QString read_01_path;
	struct MyWord
	{
		QString mWord;
		QString chinese;
		int rightn;
		int wrongn;
	};
	QVector<MyWord> mWordList;
	QString editText;
	int nowIndex=0;//��������mWordList;
	QString unicodeToUtf8(QString);  //unicodeתutf-8,���ڴ�����������
	QString myregex(const QString &str);
	QString pythonPath;
	QString pyPath;
	void readThisWord(int index);
	std::string exe_cmd(const char *cmd);
	bool mIsWebTrans=false;
	void mtransWay(QString eworld);
	QString tempChineseLabel;
	QString mip;//����ͨѶ�õ�ip��ַ;
	QString mport;//����ͨѶ�õ�port��;
	QTcpSocket *m_tcpClient;//�������н���ͨѶ;
	QNetworkRequest request;
	QNetworkAccessManager *manager = new QNetworkAccessManager(this);
	void socket_read(int index);

private:
	Ui::EnglishTypingClass ui;

public slots:
	void chooseFileWay_M();
	void saveEditInfo();
	void parsingJson(QNetworkReply * reply);   //get������ɺ󴥷��ۺ��� 
};

#endif // ENGLISHTYPING_H