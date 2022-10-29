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
	int nowIndex = 0;//��������mWordList;
	QString pythonPath;
	QString pyPath;
	bool mIsWebTrans = false;
	QString tempChineseLabel;
	QString mip;//����ͨѶ�õ�ip��ַ;
	QString mport;//����ͨѶ�õ�port��;
	QNetworkRequest request;
	QNetworkAccessManager *manager = new QNetworkAccessManager(this);
	QLabel showFileName;
	QTime mtime;
	QString judge_read_way = "json";//�ж϶�ȡ�ļ���json����csv;
	QTimer *mtimer;//һ����ʱ��;
	QTime mtimeRecorder;
	QLabel right_time_label;//���ұ�������ʱ��label;
	QTextToSpeech  *tts;
	bool isTips;
	Translator translator;
	QString defautPath;//������ȡһ��ʱ��ʾ�ĵ���;
	QString file_name_global;
	int all_world_number = 0;//��¼���ʸ���;

	void writeDefautPathIni();
	QString unicodeToUtf8(QString);  //unicodeתutf-8,���ڴ���������
	QString myregex(const QString &str);
	void qtSpeek(QString mtext);
	void printLog();
	void mtransWay(QString eworld);
	QString JsonToQstring(QJsonObject jsonObject);
	void buildConnectWay();
	void showChineseLabel();//����001Ĭд����;
	void initWordList();
	temp_word_Struct getStringLineInformation(QString line);


public slots:
	void chooseFileWay_M();
	void JudgeTorF();
	void parsingJson(QNetworkReply * reply);   //get������ɺ󴥷��ۺ��� 
	void timeupdate();
	void changeTimeLabelState();
	void changeTipsState();
	void openIni();

};

#endif // ENGLISHTYPING_H
