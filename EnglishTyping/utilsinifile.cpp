#include "utilsinifile.h"

UtilsIniFile::UtilsIniFile()
{
}

UtilsIniFile::~UtilsIniFile()
{
}

QVariant UtilsIniFile::getValue(QString iniFilename, QString Section, QString key, QVariant defaultValue)
{
    QVariant value;

    QSettings* ini = new QSettings(iniFilename, QSettings::IniFormat);
    ini->setIniCodec(QTextCodec::codecForName("UTF8"));
    value = ini->value(Section + '/' + key, defaultValue);
    delete ini;

    return value;
}

//读取配置参数值
/*QString UtilsIniFile::getValue(QString iniFilename, QString Section, QString key, QString defaultValue)
{
    QVariant value;

    QSettings* ini = new QSettings(iniFilename, QSettings::IniFormat);
    ini->setIniCodec(QTextCodec::codecForName("UTF8"));
    value = ini->value(Section + '/' + key, defaultValue);
    delete ini;

    return value.toString();
}

int UtilsIniFile::getValue(QString iniFilename, QString Section, QString key, int defaultValue)
{
    QVariant value;

    QSettings* ini = new QSettings(iniFilename, QSettings::IniFormat);
    ini->setIniCodec(QTextCodec::codecForName("UTF8"));
    value = ini->value(Section + '/' + key, defaultValue);
    delete ini;

    return value.toInt();
}*/

//写入配置参数值
bool UtilsIniFile::setValue(QString iniFilename, QString Section, QString key, QVariant value)
{
    try {
        QSettings* ini = new QSettings(iniFilename, QSettings::IniFormat);
        ini->setIniCodec(QTextCodec::codecForName("UTF8"));
        ini->setValue(Section + '/' + key, value);
        delete ini;

        return true;
    } catch (...) {
        return false;
    }
}
