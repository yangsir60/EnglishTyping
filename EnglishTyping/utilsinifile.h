#ifndef UTILSINIFILE_H
#define UTILSINIFILE_H

#include <QObject>
#include <QSettings>
#include <QTextCodec>

class UtilsIniFile : public QObject {
    Q_OBJECT
public:
    UtilsIniFile();
    ~UtilsIniFile();

    //读取配置参数值
    //QString getValue(QString iniFilename, QString Section, QString key, QString defaultValue = "");
    QVariant getValue(QString iniFilename, QString Section, QString key, QVariant defaultValue);

    //写入配置参数值
    bool setValue(QString iniFilename, QString Section, QString key, QVariant value);
};

#endif // UTILSINIFILE_H
