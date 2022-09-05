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
	void moXie001();//开启001默写方法;
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
	int nowIndex=0;//用来索引mWordList;
	QString unicodeToUtf8(QString);  //unicode转utf-8,用于处理返回数据
	QString myregex(const QString &str);
	QString pythonPath;
	QString pyPath;
	void readThisWord(int index);
	std::string exe_cmd(const char *cmd);
	bool mIsWebTrans=false;
	void mtransWay(QString eworld);
	QString tempChineseLabel;
	QString mip;//进程通讯用的ip地址;
	QString mport;//进程通讯用的port号;
	QTcpSocket *m_tcpClient;//用来进行进程通讯;
	QNetworkRequest request;
	QNetworkAccessManager *manager = new QNetworkAccessManager(this);
	void socket_read(int index);
	QLabel showFileName;
	void printLog();
	QTime mtime;
	

private:
	Ui::EnglishTypingClass ui;

public slots:
	void chooseFileWay_M();
	void saveEditInfo();
	void parsingJson(QNetworkReply * reply);   //get请求完成后触发槽函数 
};

#endif // ENGLISHTYPING_H
