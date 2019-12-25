#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "dir_utils.h"
#include "path_crypter.h"
#include "file_crypter.h"
#include "common.h"

Fullpath getFullPath(const DirUtils& dirUtils, const QString& root, const QString& deeperPath);

class Controller
{
public:
    void process(const Mode& mode, const QString& password, const QString& root, const QString& deepLink);
};

#endif // CONTROLLER_H
