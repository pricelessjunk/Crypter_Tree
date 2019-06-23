#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "dir_utils.h"
#include "path_crypter.h"
#include "file_crypter.h"
#include "common.h"

class Controller
{
public:
    void encrypt(const QString& root,const QString& password);
    void decrypt(const QString& root,const QString& password);
};

#endif // CONTROLLER_H
