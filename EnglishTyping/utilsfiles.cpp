#include "utilsfiles.h"

UtilsFiles::UtilsFiles()
{
}

UtilsFiles::~UtilsFiles()
{
}

//获取执行文件路径
QString UtilsFiles::getApplicationPath()
{
    return QCoreApplication::applicationDirPath();
}

//判断文件是否存在
bool UtilsFiles::fileExists(QString filename)
{
    //QFileInfo file(filename);
    //return file.exists();
	return QFileInfo::exists(filename);
}

//判断文件夹是否存在
bool UtilsFiles::dirExists(QString path)
{
    QDir dir(path);
    return dir.exists();
}

//创建文件夹
bool UtilsFiles::mkPath(QString path)
{
    QDir dir;
    return dir.mkpath(path);
}

//获取文件列表
void UtilsFiles::getFileNames(QString path, QString filters, QStringList* fList)
{
    fList->clear();

    QDir dir(path); //判断路径是否存在
    if (!dir.exists())
        return;

    //定义迭代器并设置过滤器
    QDirIterator dir_iterator(path,
        filters.split(","),
        QDir::Files | QDir::NoSymLinks,
        QDirIterator::Subdirectories);

    while (dir_iterator.hasNext()) {
        dir_iterator.next();
        QFileInfo file_info = dir_iterator.fileInfo();
        QString absolute_file_path = file_info.absoluteFilePath();
        fList->append(file_info.path() + "/" + file_info.fileName());
    }
}

//文件或目录是否存在
bool UtilsFiles::checkFileOrDirExist(const QString qstrFileDirOrPath)
{
    bool bRet = false;
    QFileInfo objFileInfo(qstrFileDirOrPath);
    if (objFileInfo.isFile()) {
        bRet = objFileInfo.exists();
    } else if (objFileInfo.isDir()) {
        bRet = objFileInfo.exists();
    } else {
        bRet = false;
    }

    return bRet;
}

/**************************************************
 * 功能：删除空的文件夹
 * 输入参数：
 *      qstrDirPath：文件夹路径
 * 返回值：
 *      bool：true -- 删除成功，false -- 删除失败
 * **************************************************/
void UtilsFiles::clearEmptyFolder(const QString& qstrDirPath)
{
    if (!checkFileOrDirExist(qstrDirPath))
        return;

    QDir qdrPath(qstrDirPath);
    qdrPath.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden); //set filter
    QFileInfoList lstFileInfo = qdrPath.entryInfoList(); //get all file info
    foreach (QFileInfo objFileInfo, lstFileInfo) {
        if (objFileInfo.isDir()) {
            QString qstrSubFilePath = objFileInfo.absoluteFilePath();
            QDir qdrSubPath(qstrSubFilePath);
            qdrSubPath.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);
            QFileInfoList qlstFileInfo = qdrSubPath.entryInfoList();
            if (qlstFileInfo.count() <= 0) {
                qdrSubPath.rmdir(qstrSubFilePath);
            } else {
                clearEmptyFolder(qstrSubFilePath);
            }
        }
    }
}

//删除文件夹
bool UtilsFiles::deleteDir(const QString& path)
{
    if (path.isEmpty()) {
        return false;
    }
    QDir dir(path);
    if (!dir.exists()) {
        return true;
    }

    return dir.removeRecursively(); // 删除文件夹
}

//复制文件
bool UtilsFiles::copyFileToPath(QString sourceFn, QString toFn, bool coverFileIfExist)
{
    if (!QFile::exists(sourceFn)) {
        return false;
    }

    if (sourceFn == toFn) {
        return true;
    }

    QFile createfile;
    bool exist = createfile.exists(toFn);
    if (exist) {
        if (coverFileIfExist) {
            createfile.remove(toFn);
        } else
            return false;
    }

    return !QFile::copy(sourceFn, toFn);
}

//复制文件夹
bool UtilsFiles::copyDirectoryFiles(const QString& fromDir, const QString& toDir, bool coverFileIfExist)
{
    QDir sourceDir(fromDir);
    QDir targetDir(toDir);
    if (!targetDir.exists()) { /**< 如果目标目录不存在，则进行创建 */
        if (!targetDir.mkdir(targetDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach (QFileInfo fileInfo, fileInfoList) {
        if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if (fileInfo.isDir()) { /**< 当为目录时，递归的进行copy */
            if (!copyDirectoryFiles(fileInfo.filePath(),
                    targetDir.filePath(fileInfo.fileName()),
                    coverFileIfExist))
                return false;
        } else { /**< 当允许覆盖操作时，将旧文件进行删除操作 */
            if (coverFileIfExist && targetDir.exists(fileInfo.fileName())) {
                targetDir.remove(fileInfo.fileName());
            }

            /// 进行文件copy
            if (!QFile::copy(fileInfo.filePath(),
                    targetDir.filePath(fileInfo.fileName()))) {
                return false;
            }
        }
    }
    return true;
}
