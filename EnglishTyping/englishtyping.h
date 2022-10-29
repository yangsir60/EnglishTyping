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
#include <QTimer>
#include <Translator.h>
#include <QTextToSpeech>
class EnglishTyping : public QMainWindow
{
	Q_OBJECT
private:
	Ui::EnglishTypingClass ui;
	struct temp_word_Struct
	{
		int index;
		QString word;
		QString chinese;
		int right_count;
		int wrong_count;
	};
public:
	EnglishTyping(QWidget *parent = 0);
	~EnglishTyping();
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
	int nowIndex = 0;//用来索引mWordList;
	QString pythonPath;
	QString pyPath;
	bool mIsWebTrans = false;
	QString tempChineseLabel;
	QString mip;//进程通讯用的ip地址;
	QString mport;//进程通讯用的port号;
	QNetworkRequest request;
	QNetworkAccessManager *manager = new QNetworkAccessManager(this);
	QLabel showFileName;
	QTime mtime;
	QString judge_read_way = "json";//判断读取文件是json还是csv;
	QTimer *mtimer;//一个定时器;
	QTime mtimeRecorder;
	QLabel right_time_label;//最右边用来计时的label;
	QTextToSpeech  *tts;
	bool isTips;
	Translator translator;
	QString defautPath;//用来读取一打开时显示的单词;
	QString file_name_global;
	int all_world_number = 0;//记录单词个数;

	void writeDefautPathIni();
	QString unicodeToUtf8(QString);  //unicode转utf-8,用于处理返回数据
	QString myregex(const QString &str);
	void qtSpeek(QString mtext);
	void printLog();
	void mtransWay(QString eworld);
	QString JsonToQstring(QJsonObject jsonObject);
	void buildConnectWay();
	void showChineseLabel();//开启001默写方法;
	void initWordList();
	temp_word_Struct getStringLineInformation(QString line);


public slots:
	void chooseFileWay_M();
	void JudgeTorF();
	void parsingJson(QNetworkReply * reply);   //get请求完成后触发槽函数 
	void timeupdate();
	void changeTimeLabelState();
	void changeTipsState();
	void openIni();

};

#endif // ENGLISHTYPING_H
