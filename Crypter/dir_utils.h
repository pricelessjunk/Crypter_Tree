/*
 * DirUtility.h
 *
 *  Created on: May 4, 2019
 *      Author: fenris
 */

#ifndef DIRUTIL_H_
#define DIRUTIL_H_

#include <errno.h>
#include <dirent.h> // For DIR
#include <sys/stat.h>

#include <QDir>

//#include <direct.h>
//#define GetCurrentDir _getcwd
//For Unix
#include <unistd.h>
#define GetCurrentDir getcwd

#include "common.h"

class DirUtils {

public:
    std::vector<Fullpath> GetFiles(QString root_path_str, Mode mode, SearchMode searchMode = ALL);
    std::vector<Fullpath> GetFiles(Fullpath root_path_fp, Mode mode, SearchMode searchMode = ALL);
    QString GetCurrentWorkingDir();
    QString GetAbsolutePath(const Fullpath &path);
    Fullpath GetFullPathFolder(const QString absPath, const QString root);
    Fullpath AddDeepLinkToFP(const Fullpath& base, const QString& name, const bool& isDir) const;
    Fullpath CreateRootFullPath(const QString& base) const;
    void CheckAndCreateDirectory(const Fullpath& name);
    bool DoesDirectoryExist(const QString& name) const;
    void DeleteFolder(const QString& name) const;
private:
    QString GetAbsolutePath(const Fullpath &path, vector_qstring_size_t index);
    bool FilterFilesWithExtensions(const QString &mainStr) const;
};

#endif /* DIRUTIL_H_ */
