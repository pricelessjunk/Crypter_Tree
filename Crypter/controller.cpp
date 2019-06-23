#include "controller.h"

void Controller::encrypt(const QString& root,const QString& password)
{
    DirUtils dirUtils;
    qDebug() <<"Root folder: "<< root;

    PathCrypter path_crypter;
    FileCrypter file_crypter;

    std::vector<Fullpath> files = dirUtils.GetFiles(dirUtils.CreateRootFullPath(root),Mode::Encrypt);
    qDebug() << "File list acquired";

    for (std::vector<Fullpath>::iterator it = files.begin(); it != files.end(); it++) {
        Fullpath path = (*it);


        QString abs_encoded_path = path_crypter.GetEncodedPath(path,password);
        if(path.isDir){
            qDebug()<<"Creating Dir: "<< abs_encoded_path;
            dirUtils.CreateDirectory(abs_encoded_path);
        }else{
            qDebug()<<"Creating File: "<< abs_encoded_path;
            QString abs_path = dirUtils.GetAbsolutePath(path);
            file_crypter.encryptFile(abs_path.toLatin1().data(), abs_encoded_path.toLatin1().data(), password);
        }
    }
}

void Controller::decrypt(const QString& root,const QString& password){
    DirUtils dirUtils;
    qDebug() <<"Root folder: "<< root;

    PathCrypter path_crypter;
    FileCrypter file_crypter;

    std::vector<Fullpath> files = dirUtils.GetFiles(dirUtils.CreateRootFullPath(root), Mode::Decrypt);
    qDebug() << "File list acquired";

    for (std::vector<Fullpath>::iterator it = files.begin(); it != files.end(); it++) {
        Fullpath path = (*it);


        QString abs_decoded_path = path_crypter.GetDecodedPath(path,password);
        if(path.isDir){
            //qDebug()<<"Creating Dir: "<< abs_decoded_path;
            dirUtils.CreateDirectory(abs_decoded_path);
        }else{
            //qDebug()<<"Creating File: "<< abs_decoded_path;
            QString abs_path = dirUtils.GetAbsolutePath(path);
            file_crypter.decryptFile(abs_path.toLatin1().data(), abs_decoded_path.toLatin1().data(), password);
        }
    }
}

