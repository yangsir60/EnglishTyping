#include "englishtyping.h"
#include "qDebug.h"
#include <iostream>
#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <Translator.h>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QProcess>
#include <stdlib.h>
#include <QtConcurrent>
using namespace std;
EnglishTyping::EnglishTyping(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	buildConnectWay();
	
	ui.label->hide();
	//mtransWay("English");
	
	
	UtilsIniFile iniTools;
	UtilsFiles fileTools;
	QString configPath = fileTools.getApplicationPath()+"/config/config.ini";
	if (!fileTools.fileExists(configPath)){
		qDebug() << "> WARNING: config.ini is not Exists! Please create config.ini file";
	}
	else{
		pythonPath = iniTools.getValue(configPath, "system", "pythonPath","").toString();
		pyPath = iniTools.getValue(configPath, "system", "pyPath", "").toString();
		mIsWebTrans = iniTools.getValue(configPath, "system", "isWeb", false).toBool();
		mip = iniTools.getValue(configPath, "system", "mip", "").toString();
		mport = iniTools.getValue(configPath, "system", "mport", "").toString();
	}
	start001();
	m_tcpClient = new QTcpSocket(this);
}

EnglishTyping::~EnglishTyping()
{

}

void EnglishTyping::buildConnectWay()
{
	connect(ui.action_json, SIGNAL(triggered()), this, SLOT(chooseFileWay_M()));
	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(parsingJson(QNetworkReply*)));
}

void EnglishTyping::moXie001()
{
	if (mWordList.size() != 0){
		//cout << mWordList[nowIndex].mWord.toStdString() << endl;
		if (mIsWebTrans){
			mtransWay(mWordList[nowIndex].mWord);
		}
		else{
			ui.lb_chinese->setText(mWordList[nowIndex].chinese);
		}
		//cout << mWordList[nowIndex].chinese.toLocal8Bit().toStdString() << endl;
		ui.english_sr->setText("");
	}
}

void EnglishTyping::start001()
{
	if (read_01_path.size() == 0){
		read_01_path = "D:\\BaiduNetdiskWorkspace\\Lite Code\\translate python\\20220604.json";
	}
	QFile file(read_01_path);
	bool isOpen = file.open(QIODevice::ReadOnly);
	if (isOpen == false)
		return;
	QByteArray data = file.readAll();
	file.close();
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
	connect(ui.english_sr, SIGNAL(returnPressed()), this, SLOT(saveEditInfo()), Qt::UniqueConnection);
	moXie001();
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
	QString fileName = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("����"), "D:/BaiduNetdiskWorkspace/Lite Code/translate python", tr("json�ļ� (*.json)"));
	read_01_path = fileName;
	mWordList.clear();
	start001();
}

void EnglishTyping::saveEditInfo()
{
	cout << mWordList[nowIndex].chinese.toLocal8Bit().toStdString() << endl;//�س�����ʾ����ʵ�Ӣ��,����;
	int wrongIndex=-1;//�ж��Ƿ��д���Ĵ���;
	editText = ui.english_sr->text();
	if (editText == mWordList[nowIndex].mWord){
		ui.tips->setText("Right");
		//ui.tips->setStyleSheet("color:rgb(0, 170, 0);font: 18pt \"΢���ź�\";");
		ui.tips->setStyleSheet("color: rgb(0, 170, 0);font: 18pt Microsoft YaHei;");
		
		ui.label->hide();
		mWordList[nowIndex].rightn++;
		if (mport.size()==0)
			QtConcurrent::run(this, &EnglishTyping::readThisWord,nowIndex);
		else{
			socket_read(nowIndex);
		}
	}
	else{
		ui.tips->setText("Wrong");
		ui.tips->setStyleSheet("color: rgb(255, 0, 0);font: 18pt Microsoft YaHei;");
		ui.label->setText(mWordList[nowIndex].mWord);
		ui.label->hide();
		//qDebug() << ui.label->size()<<" "<<ui.label->margin();
		mWordList[nowIndex].wrongn++;
		wrongIndex = nowIndex;
		if (mport.size() == 0)
			QtConcurrent::run(this, &EnglishTyping::readThisWord,nowIndex);
		else{
			socket_read(nowIndex);
		}
	}
	qDebug() << mWordList[nowIndex].mWord << ", You write right " << mWordList[nowIndex].rightn << " wrong " << mWordList[nowIndex].wrongn;
	qDebug() << "-----------------------------------------";
	nowIndex++;
	if (wrongIndex != -1){
		nowIndex = wrongIndex;
	}
	if (nowIndex == mWordList.size()){
		nowIndex = 0;
	}
	//qDebug() << "nowindex " << nowIndex;
	moXie001();
}

void EnglishTyping::parsingJson(QNetworkReply * reply)
{
	if (reply->error() == QNetworkReply::NoError){   //�ж��Ƿ�����ɹ�
		QString all = reply->readAll();   //������������
		//qDebug() << all;   //��ӡ�����ᷢ�����ĺ�һЩ������Unicode�����ת���ַ�����\\u187d
		QString re = myregex(all);   //����������������ȡ��dst�ֶ�
		//qDebug() << re;
		QString res = unicodeToUtf8(re);    //unicodeתutf8
		tempChineseLabel = res;
		qDebug() << ": "<<res;
		//qDebug() << tempChineseLabel << " tempch";
		ui.lb_chinese->setText(tempChineseLabel);
	}
	else{
		qDebug() << reply->errorString() << " error " << reply->error();
	}
}

QString EnglishTyping::myregex(const QString &qstr){   //�����������������Ͳ������ˣ���������Ŀ���ȥ��һ�¿�
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

void EnglishTyping::readThisWord(int index)
{

	
		//cout << "py" << endl;
		QString english_word = mWordList[index].mWord;
		QString command = pythonPath + " " + pyPath + " " + english_word;
		QByteArray ba_command = command.toLocal8Bit(); // must
		char *ch_command = ba_command.data();
		//cout << ch_command << endl;
		//system(ch_command);
		exe_cmd(ch_command);
	
	
}

QString EnglishTyping::unicodeToUtf8(QString str) //unicodeתutf8
{
	QString result;
	int index = str.indexOf("\\u");
	//qDebug() << index;
	//�ж��Ƿ����Ϊת���ַ���ʵ������ֻ��Ӣ����ĸ�ǿ���������ʾ����Ҫת���
	if (index != -1){
		/* �ж��ַ����Ƿ�ȫΪת���ַ���ʵ���������ĺͺ��ĵ�ȫ��ת��
		* ����͵���ֻ�и������������ת���ַ�
		*  */
		if (index == 0){   //ȫΪת��
			while (index != -1){
				QString s1 = str.mid(index + 2, 4);
				result.append(s1.toUShort(0, 16));
				index = str.indexOf("\\u", index + 5);
			}
			return result.toUtf8().constData();
		}
		else{   //����ת��
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
	//    return result.toUtf8().constData();
}

string EnglishTyping::exe_cmd(const char *cmd)
{
	char buffer[128] = { 0 };
	string result;
	FILE *pipe = _popen(cmd, "r");
	if (!pipe) throw std::runtime_error("_popen() failed!");
	while (!feof(pipe))
	{
		if (fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	}
	_pclose(pipe);
	return result;
}

void EnglishTyping::mtransWay(QString eworld)
{
	//English word to chinese;
	Translator translator;
	translator.SetQstr(eworld);
	translator.SetIndex(1);
	QString url = translator.GetUrl();
	request.setUrl(QUrl(url));
	manager->get(request);
}

void EnglishTyping::socket_read(int index)
{
	//cout << "����ͨѶ" << endl;
	QString english_word = mWordList[index].mWord;
	std::string res = english_word.toLocal8Bit().toStdString();
	//cout << res << endl;
	char *buff = const_cast<char *>(res.c_str());
	m_tcpClient->close();
	delete(m_tcpClient);
	m_tcpClient = new QTcpSocket(this);
	m_tcpClient->connectToHost(QHostAddress("127.0.0.1"), 12345);
	m_tcpClient->write(buff);
	//QApplication::processEvents();
}