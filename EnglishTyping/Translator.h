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
	//֧��7������Ŀ�����ֵı��
	string lan[7];
	int index;      //ѡ�����ֵ��±�
	/* ��Ϊ�ٶȷ�����Ҫһ��MD5���ܵ�ǩ��
	* �������ҵ���MD5���ܵķ�����ֻ֧��string����
	* ��������������string����url��ת��Qstring
	* ps:��֪��string��Qstring���������ȥ��һ�¿�*/
	string myurl;   //���string����url
	string appid;   //appid
	QString qstr;   //�����Qstring���ͷ�������ݣ���Ҫת��string����
	string q;       //string���ͷ��������
	string from;    //�������ݵ����֣�һ��Ϊ��auto��
	string to;      //����Ŀ������
	string salt;    //һ���������������ʱ������������
	string secret_key;   //��Կ
	string sign;    //MD5���ܵ�ǩ��
	QString url;    //Qstring����url


public:
	Translator();     //Ĭ�Ϲ��캯��
	Translator(const QString &);     //���캯��
	QString GetUrl();   //����url�ķ���
	void SetQstr(const QString &);   //������Ҫ�������ݵĺ���
	void SetIndex(const int&);      //���÷���Ŀ�����ֵĺ���
	void SetAppid(string mappid){ appid = mappid;};
	void SetKey(string mkey){ secret_key = mkey; };
};

#endif // TANSLATOR_H

