#include "Translator.h"

#if _MSC_VER >=1600    // MSVC2015>1899,����MSVC2010���ϰ汾������ʹ��
#pragma execution_character_set("utf-8")
#endif
Translator::Translator(){
	lan[0] = "en";
	lan[1] = "zh";
	lan[2] = "fra";
	lan[3] = "de";
	lan[4] = "kor";
	lan[5] = "jp";
	lan[6] = "th";

}
Translator::Translator(const QString &qerry)
:qstr(qerry)
{
	lan[0] = "en";
	lan[1] = "zh";
	lan[2] = "fra";
	lan[3] = "de";
	lan[4] = "kor";
	lan[5] = "jp";
	lan[6] = "th";
	q = qstr.toStdString();
	index = 0;
}

void Translator::SetQstr(const QString &qstring){
	qstr = qstring;
	q = qstr.toStdString();

}
void Translator::SetIndex(const int& in){
	index = in;
}



QString Translator::GetUrl(){
	//����ǩ��
	myurl = "http://fanyi-api.baidu.com/api/trans/vip/translate?";
	//appid = "20220826001320749";  //���appid
	from = "auto";
	to = lan[index];  //ѡ��Ŀ������
	time_t myt = time(NULL);  //��ȡʱ���
	salt = to_string(myt);
	//secret_key = "dVAL3rPXzroewfeDkZI9";  //�����Կ
	sign = "";
	//ǩ��ƴ��
	sign.append(appid);
	sign.append(q);
	sign.append(salt);
	sign.append(secret_key);

	//ǩ��MD5����
	MD5 md5 = MD5(sign);
	sign = md5.outstr(32).c_str();

	//����url
	myurl.append("&q=");
	myurl.append(q);
	myurl.append("&from=");
	myurl.append(from);
	myurl.append("&to=");
	myurl.append(to);
	myurl.append("&appid=");
	myurl.append(appid);
	myurl.append("&salt=");
	myurl.append(salt);
	myurl.append("&sign=");
	myurl.append(sign);
	//stringתQstring
	url = QString::fromStdString(myurl);
	return url;
}
