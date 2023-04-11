#include "englishtyping.h"
#include "qDebug.h"
#include <iostream>
#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QProcess>
#include <stdlib.h>
#include <QtConcurrent>
#include <mtools.h>
using namespace std;
EnglishTyping::EnglishTyping(QWidget *parent)
: QMainWindow(parent)
{
	ui.setupUi(this);
	//隐藏提示面板;
	ui.label->hide();
	//读取ini文件;
	UtilsIniFile iniTools;
	UtilsFiles fileTools;
	QString configPath = fileTools.getApplicationPath() + "/config/config.ini";
	if (!fileTools.fileExists(configPath)){
		qDebug() << "> WARNING: config.ini is not Exists! Please create config.ini file";
	}
	else{
		mIsWebTrans = iniTools.getValue(configPath, "system", "isWeb", false).toBool();
		mip = iniTools.getValue(configPath, "system", "mip", "").toString();
		mport = iniTools.getValue(configPath, "system", "mport", "").toString();
		isTips = iniTools.getValue(configPath, "system", "isTips", false).toBool();
		defautPath = iniTools.getValue(configPath, "system", "defautPath", "").toString();
		std::string appid = iniTools.getValue(configPath, "trans", "appid", "").toString().toStdString();
		std::string key = iniTools.getValue(configPath, "trans", "key", "").toString().toStdString();
		translator.SetAppid(appid);
		translator.SetKey(key);
	}
	//初始化单词列表;
	initWordList();
	//开启一个计时器;
	mtimer = new QTimer(this);
	mtime.start();
	mtimer->start(1000);
	mtimeRecorder.setHMS(0, 0, 0);
	right_time_label.setText(mtimeRecorder.toString("hh:mm:ss"));
	ui.statusBar->addWidget(&right_time_label);
	//建立连接;
	buildConnectWay();
	//设置语音朗读;
	tts = new QTextToSpeech(this);;
	tts->setLocale(QLocale::Chinese);
	tts->setRate(0.0);//语速;
	tts->setPitch(1.0);//音高;
	tts->setVolume(1.0);//音量;
}

EnglishTyping::~EnglishTyping()
{
	printLog();
	writeDefautPathIni();
}

void EnglishTyping::buildConnectWay()
{
	connect(ui.action_json, SIGNAL(triggered()), this, SLOT(chooseFileWay_M()));
	connect(ui.action_csv, SIGNAL(triggered()), this, SLOT(chooseFileWay_M()));
	connect(ui.action_showtime, SIGNAL(triggered()), this, SLOT(changeTimeLabelState()));
	connect(ui.action_hidetime, SIGNAL(triggered()), this, SLOT(changeTimeLabelState()));
	connect(ui.actioncloseTips, SIGNAL(triggered()), this, SLOT(changeTipsState()));
	connect(ui.actionopenTips, SIGNAL(triggered()), this, SLOT(changeTipsState()));
	connect(ui.action, SIGNAL(triggered()), this, SLOT(openIni()));
	connect(mtimer, SIGNAL(timeout()), this, SLOT(timeupdate()));
	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(parsingJson(QNetworkReply*)));
}

void EnglishTyping::openIni(){
	QProcess pro;
	UtilsFiles fileTools;
	QString configPath = fileTools.getApplicationPath() + "/config/config.ini";
	QString iniPath = "notepad.exe " + configPath;
	pro.start(iniPath);
	pro.waitForFinished(-1);
}

void EnglishTyping::showChineseLabel()
{
	if (mWordList.size() != 0){
		if (mIsWebTrans){
			mtransWay(mWordList[nowIndex].mWord);//request请求完毕后parsingjson里面进行了lbchinese的显示;
		}
		else{
			ui.lb_chinese->setText(mWordList[nowIndex].chinese);
		}
		ui.english_sr->setText("");
	}
}

void EnglishTyping::initWordList()
{
	//在打开时读取默认路径;
	if (read_01_path.size() == 0){
		read_01_path = defautPath;
		QString postfix = read_01_path.split(".")[read_01_path.split(".").length() - 1];
		judge_read_way = postfix;
		showFileName.setText(read_01_path.split("/")[read_01_path.split("/").length() - 1]);
		ui.statusBar->addWidget(&showFileName);
	}
	if (judge_read_way == "json")
	{
		QFile file(read_01_path);
		bool isOpen = file.open(QIODevice::ReadOnly);
		if (isOpen == false)
			return;
		QByteArray data = file.readAll();
		file.close();
		//读取json数据到结构体;
		QJsonDocument doc = QJsonDocument::fromJson(data);
		if (!doc.isObject())
			return;
		QJsonObject jObj = doc.object();
		QStringList jsonkeys = jObj.keys();
		for (int i = 0; i < jObj.size(); i++)
		{
			QString trans = jObj.value(jsonkeys[i]).toString();
			MyWord tempword;
			tempword.mWord = jsonkeys[i];
			tempword.chinese = trans;
			tempword.rightn = 0;
			tempword.wrongn = 0;
			mWordList.append(tempword);
		}
	}
	else if (judge_read_way == "csv"){	//读取csv文件;
		QFile file(read_01_path);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
			qDebug() << "open file wrong;";
			return;
		}
		QTextStream * out = new QTextStream(&file);//文本流  ;
		QStringList tempOption = out->readAll().split("\n");//每行以\n区分 ;
		for (int i = 0; i < tempOption.count(); i++)
		{
			QStringList tempbar = tempOption.at(i).split(",");//一行中的单元格以，区分;  

			if (mtools::IsEnglish(tempbar[0])){
				MyWord tempword;
				tempword.mWord = tempbar[0];
				tempword.chinese = "";
				tempword.rightn = 0;
				tempword.wrongn = 0;
				mWordList.append(tempword);
			}
		}
		file.close();
	}
	cout << "这里有 " << mWordList.size() << " 个单词" << endl;
	all_world_number = mWordList.size();
	connect(ui.english_sr, SIGNAL(returnPressed()), this, SLOT(JudgeTorF()), Qt::UniqueConnection);
	//mtimeRecorder.setHMS(0, 0, 0, 0);//每次打开一个文件从0开始计时;
	showChineseLabel();
}

EnglishTyping::temp_word_Struct EnglishTyping::getStringLineInformation(QString line)
{
	QStringList qStrlist =  line.split(",");
	temp_word_Struct word_struct;
	//qDebug() << line << endl;
	for (int i = 0; i < qStrlist.size();i++)
	{
		QString temp_str = qStrlist[i];
		if (i == 0){
			word_struct.index = temp_str.toInt();
		}
		if (i == 1){
			word_struct.word = temp_str;
		}
		if (i == 2){
			word_struct.chinese = temp_str;
			//cout << "---" << endl;
			//qDebug() << word_struct.chinese << endl;
		}
		if (i == 3){
			word_struct.right_count = temp_str.toInt();
		}
		if (i == 4){
			word_struct.wrong_count = temp_str.toInt();
		}
	}
	return word_struct;
}

QString EnglishTyping::JsonToQstring(QJsonObject jsonObject)
{
	QJsonDocument document;
	document.setObject(jsonObject);
	QByteArray simpbyte_array = document.toJson(QJsonDocument::Compact);
	QString simpjson_str(simpbyte_array);

	return simpjson_str;
}

void EnglishTyping::chooseFileWay_M()
{
	QString fileName;
	QObject* obj = sender();
	if (obj->objectName() == "action_json"){
		fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("导入"), "D:/BaiduNetdiskWorkspace/Lite Code/translate python", QString::fromLocal8Bit("json文件 (*.json)"));
		judge_read_way = "json";
	}
	else if (obj->objectName() == "action_csv"){
		fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("导入"), "D:/BaiduNetdiskWorkspace/Lite Code/translate python", QString::fromLocal8Bit("json文件 (*.csv)"));
		judge_read_way = "csv";
	}
	read_01_path = fileName;
	//在界面左下角显示读取的是什么文件;
	fileName = fileName.split("/")[fileName.split("/").length() - 1];
	file_name_global = fileName;
	showFileName.setText(fileName);
	ui.statusBar->addWidget(&showFileName);
	mWordList.clear();
	initWordList();
}

//判断输入单词的对错和在控制台打印出单词信息;
void EnglishTyping::JudgeTorF()
{
	//cout << mWordList[nowIndex].chinese.toLocal8Bit().toStdString() << endl;//回车后显示这个词的英语,汉语;
	int wrongIndex = -1;//判断是否有错误的词语;
	editText = ui.english_sr->text();//得到输入框内的英文;
	if (editText.toLower() == mWordList[nowIndex].mWord.toLower()){//判断单词写的是否正确并读出对的单词;
		ui.tips->setText("Right");
		ui.tips->setStyleSheet("color: rgb(0, 170, 0);font: 18pt Microsoft YaHei;");
		ui.label->hide();
		mWordList[nowIndex].rightn++;
		qtSpeek(mWordList[nowIndex].mWord);
	}
	else{
		ui.tips->setText("Wrong");
		ui.tips->setStyleSheet("color: rgb(255, 0, 0);font: 18pt Microsoft YaHei;");
		ui.label->setText(mWordList[nowIndex].mWord);
		if (isTips){
			ui.label->show();
		}
		else{
			ui.label->hide();
		}
		mWordList[nowIndex].wrongn++;
		wrongIndex = nowIndex;
		qtSpeek(mWordList[nowIndex].mWord);
	}
	cout << mWordList[nowIndex].mWord.toStdString() << ", right " << mWordList[nowIndex].rightn << " wrong " << mWordList[nowIndex].wrongn;
	nowIndex++;
	cout << " ," << nowIndex <<"th "<< endl;
	qDebug() << "-----------------------------------------";
	if (wrongIndex != -1){
		nowIndex = wrongIndex;
	}
	if (nowIndex == mWordList.size()){
		nowIndex = 0;
	}
	//qDebug() << "nowindex " << nowIndex;
	showChineseLabel();
}

void EnglishTyping::parsingJson(QNetworkReply * reply)
{
	if (reply->error() == QNetworkReply::NoError){   //判断是否请求成功;
		QString all = reply->readAll();   //读出返回数据;
		//qDebug() << all;   //打印出来会发现中文和一些外文是Unicode编码的转义字符，如\\u187d
		QString re = myregex(all);   //解析出翻译结果，即取出dst字段;
		//qDebug() << re;
		QString res = unicodeToUtf8(re);    //unicode转utf8
		tempChineseLabel = res;
		//qDebug() << ": " << res;
		mWordList[nowIndex].chinese = res;
		cout << mWordList[nowIndex].chinese.toLocal8Bit().toStdString() << "  ";
		ui.lb_chinese->setText(tempChineseLabel);
	}
	else{
		qDebug() << reply->errorString() << " error " << reply->error();
	}
}

void EnglishTyping::timeupdate()
{
	mtimeRecorder = mtimeRecorder.addSecs(1);
	right_time_label.setText(mtimeRecorder.toString("hh:mm:ss"));
}

void EnglishTyping::changeTimeLabelState()
{
	QObject *obj = sender();
	if (obj->objectName() == "action_showtime"){
		right_time_label.show();
	}
	else if (obj->objectName() == "action_hidetime"){
		right_time_label.hide();
	}
}

void EnglishTyping::changeTipsState()
{
	QObject *obj = sender();
	if (obj->objectName() == "actionopenTips"){
		isTips = true;
	}
	else if (obj->objectName() == "actioncloseTips"){
		isTips = false;
	}
}

QString EnglishTyping::myregex(const QString &qstr){   //正则解析函数，这里就不解释了，不会正则的可以去补一下课;
	string ans;
	string str = qstr.toStdString();
	string pattern = "\"(.+?)\"";
	regex e("\\[(.*)\\]");
	regex r(pattern);
	smatch m;
	regex_search(str, m, e);

	string temp = m[1];
	auto res = vector<string>(9);

	sregex_iterator pos(temp.cbegin(), temp.cend(), r), end;
	for (; pos != end; ++pos) {
		res.push_back(pos->str(1));
	}
	for (auto temp : res)
		ans = temp;
	return QString::fromStdString(ans);
}


QString EnglishTyping::unicodeToUtf8(QString str) //unicode转utf8
{
	QString result;
	int index = str.indexOf("\\u");
	//qDebug() << index;
	//判断是否存在为转移字符，实践表明只有英文字母是可以正常显示不需要转码的
	if (index != -1){
		/* 判断字符串是否全为转义字符，实践表明中文和韩文等全是转移;
		* 法语和德语只有个别特殊符号是转义字符;
		*  */
		if (index == 0){   //全为转义;
			while (index != -1){
				;
				QString s1 = str.mid(index + 2, 4);
				result.append(s1.toUShort(0, 16));
				index = str.indexOf("\\u", index + 5);
			}
			return result.toUtf8().constData();
		}
		else{   //部分转义;
			while (index != -1){
				QString s1 = str.mid(index + 2, 4);
				result = s1.toUShort(0, 16);
				str.replace(index - 1, 7, result.toUtf8().constData());
				index = str.indexOf("\\u", index + 5);
			}
			return str;
		}
	}
	return str;
}

void EnglishTyping::mtransWay(QString eworld)
{
	//English word to chinese;
	translator.SetQstr(eworld);
	translator.SetIndex(1);
	QString url = translator.GetUrl();
	request.setUrl(QUrl(url));
	manager->get(request);
}

void EnglishTyping::printLog()
{
	double cost_time = mtime.elapsed() / 1000.0;
	UtilsFiles filetools;
	QString logPath = filetools.getApplicationPath() + "/log";
	if (!filetools.dirExists(logPath)){
		filetools.mkPath(logPath);
	}
	//得到结束时间;
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_time_str = current_date_time.toString("yyyy-MM-dd hh-mm-ss");
	QString log_name = logPath + "/" + "this_word_file" + ".txt";
	QString record_file_path = logPath + "/" + "RecordFile" + ".txt";
	QString all_word_file_path = logPath + "/" + "all_word_record" + ".txt";
	//创建log单词文件//把这次打完得到的单词情况记录下来（this_word_file）；作为这次打完后的原始样本;
	QFile mfile(log_name);
	if (!mfile.open(QIODevice::WriteOnly | QIODevice::Text)){
		return;
	}
	QTextStream out(&mfile);
	out << current_time_str << "    ";
	if (cost_time > 60){
		double ss = int(cost_time) % 60;
		double mm = cost_time / 60;
		out << mtimeRecorder.toString("hh:mm:ss") << endl;
	}
	else{
		out << mtimeRecorder.toString("hh:mm:ss") << endl;
	}
	for (int i = 0; i < mWordList.size(); i++)
	{
		out << i + 1 << "," << mWordList[i].mWord << "," << mWordList[i].chinese << "," << mWordList[i].wrongn << "," << mWordList[i].rightn << endl;
	}
	mfile.close();
	//创建记录文件(ReccordFile),记录每次的时间与文件;
	QFile mRecordFile(record_file_path);
	if (!mRecordFile.open(QIODevice::Append | QIODevice::Text)){
		return;
	}
	QTextStream out2(&mRecordFile);
	out2 << current_time_str << "    ";
	if (cost_time > 60){
		double ss = int(cost_time) % 60;
		double mm = cost_time / 60;
		out2 << mtimeRecorder.toString("hh:mm:ss");
	}
	else{
		out2 << mtimeRecorder.toString("hh:mm:ss");
	}
	out2 << "  " << showFileName.text() << endl;
	mRecordFile.close();
	
	//读取（all_word_file）的单词文件,得到每一行的数据;
	QFile testQt(all_word_file_path);
	if (!testQt.open(QIODevice::ReadOnly | QIODevice::Text)){
		qDebug() << "testqt File open failed";
	}
	QTextStream testIn(&testQt);
	QVector<QString> read_list;
	QVector<temp_word_Struct> all_word_list;
	while (!testIn.atEnd())
	{
		QString line = testIn.readLine();
		temp_word_Struct temp_word = getStringLineInformation(line);
		all_word_list.append(temp_word);
		read_list.append(line);
	}
	testQt.close();
	//mWordList这次单词文件一个个循环一遍，循环这次的单词文件来与总单词文件进行比对;
	for (int i = 0; i < mWordList.size(); i++)
	{
		int flag = 1;
		for (int j = 0; j < read_list.size(); j++){
			if (mWordList[i].mWord == all_word_list[j].word){
				flag = 0;
				all_word_list[j].chinese = mWordList[i].chinese;
				all_word_list[j].right_count = all_word_list[j].right_count + mWordList[i].rightn;
				all_word_list[j].wrong_count = all_word_list[j].wrong_count + mWordList[i].wrongn;
				break;
			}
		}
		if (flag == 1){
			temp_word_Struct temp_word;
			temp_word.index = all_word_list[all_word_list.size() - 1].index + 1;
			temp_word.word = mWordList[i].mWord;
			temp_word.chinese = mWordList[i].chinese;
			temp_word.right_count = mWordList[i].rightn;
			temp_word.wrong_count = mWordList[i].wrongn;
			all_word_list.append(temp_word);
		}
	}
	//读取（this_word）后写如总单词文件（all_word）；
	QFile test_write(all_word_file_path);
	if (!test_write.open(QIODevice::WriteOnly | QIODevice::Text)){
		qDebug() << "File open failed";
	}
	QTextStream out3(&test_write);
	//out.setCodec("utf-8");
	for (int i = 0; i < all_word_list.size(); i++)
	{
		
		out3 << all_word_list[i].index << "," << all_word_list[i].word << "," << unicodeToUtf8(all_word_list[i].chinese) << "," << all_word_list[i].right_count << "," << all_word_list[i].wrong_count << endl;
	}
	test_write.close();

	


}

void EnglishTyping::qtSpeek(QString mtext)
{
	if (tts->state() == QTextToSpeech::Ready)
	{
		tts->say(mtext);
	}
}

void EnglishTyping::writeDefautPathIni()
{
	UtilsFiles fileTools;
	UtilsIniFile ini_tools;
	QString configPath = fileTools.getApplicationPath() + "/config/config.ini";
	ini_tools.setValue(configPath, "system", "defautPath", read_01_path);
}
