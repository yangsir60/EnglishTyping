#ifndef UTILSFILES_H
#define UTILSFILES_H

#include <QApplication>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <QObject>

class UtilsFiles : public QObject {
    Q_OBJECT
public:
    UtilsFiles();
    ~UtilsFiles();

    QString getApplicationPath(); //获取执行文件路径
    bool fileExists(QString filename); //判断文件是否存在
    bool dirExists(QString path); //判断文件夹是否存在
    bool mkPath(QString path); //创建文件夹
    void getFileNames(QString path, QString filters, QStringList* fList); //获取文件列表

    bool checkFileOrDirExist(const QString qstrFileDirOrPath); //文件或目录是否存在
    void clearEmptyFolder(const QString& qstrDirPath); //删除空的文件夹
    bool deleteDir(const QString& path); //删除文件夹

    bool copyFileToPath(QString sourceFn, QString toFn, bool coverFileIfExist); //复制文件
    bool copyDirectoryFiles(const QString& fromDir, const QString& toDir, bool coverFileIfExist); //复制文件夹
};

#endif // UTILSFILES_H
