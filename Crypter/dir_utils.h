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

#include <direct.h>
#define GetCurrentDir _getcwd
//For Unix
//#include <unistd.h>
//#define GetCurrentDir getcwd

#include "common.h"

enum Mode {Encrypt, Decrypt};

enum SearchMode {ALL, DIR_ONLY};

class DirUtils {

public:
    std::vector<Fullpath> GetFiles(Fullpath base, Mode mode, SearchMode searchMode = ALL);
    QString GetCurrentWorkingDir();
    QString GetAbsolutePath(Fullpath &path);
    Fullpath CreateFullPath(const Fullpath& base, const QString& name, const bool& isDir) const;
    Fullpath CreateRootFullPath(const QString& base) const;
    void CreateDirectory(const QString& name) const;
    bool DoesDirectoryExist(const QString& name) const;
private:
    bool FilterFilesWithExtensions(const QString &mainStr, const std::vector<QString>& exceptionList) const;
};

#endif /* DIRUTIL_H_ */
