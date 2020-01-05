#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "dir_utils.h"
#include "path_crypter.h"
#include "file_crypter.h"
#include "common.h"
#include <QThread>

Fullpath getFullPath(const DirUtils& dirUtils, const QString& root, const QString& deeperPath);

class Controller
{
    const int maxThreadCount;

public:
    Controller():maxThreadCount(QThreadPool::globalInstance()->maxThreadCount()/2){}

    void process(const Mode& mode, const QString& password, const QString& root, const QString& deepLink);
};

#endif // CONTROLLER_H
