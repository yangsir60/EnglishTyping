#ifndef TANSLATOR_H
#define TANSLATOR_H

#include <iostream>
#include <QString>
#include <time.h>
#include <QTextCodec>
#include <QDebug>
#include <QObject>
#include "MD5.h"

using namespace std;
class Translator : public QObject
{
	Q_OBJECT
private:
	//支持7个翻译目标语种的标号
	string lan[7];
	int index;      //选择语种的下标
	/* 因为百度翻译需要一个MD5加密的签名
	* 但是我找到的MD5加密的方法都只支持string类型
	* 所以这里先生产string类型url再转成Qstring
	* ps:不知道string和Qstring的区别可以去补一下课*/
	string myurl;   //存放string类型url
	string appid;   //appid
	QString qstr;   //传入的Qstring类型翻译的内容，需要转成string类型
	string q;       //string类型翻译的内容
	string from;    //翻译内容的语种，一般为‘auto’
	string to;      //翻译目标语种
	string salt;    //一串随机数，我是用时间戳当成随机数
	string secret_key;   //密钥
	string sign;    //MD5加密的签名
	QString url;    //Qstring类型url


public:
	Translator();     //默认构造函数
	Translator(const QString &);     //构造函数
	QString GetUrl();   //生产url的方法
	void SetQstr(const QString &);   //设置需要翻译内容的函数
	void SetIndex(const int&);      //设置翻译目标语种的函数
	void SetAppid(string mappid){ appid = mappid;};
	void SetKey(string mkey){ secret_key = mkey; };
};

#endif // TANSLATOR_H

