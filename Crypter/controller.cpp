#include "controller.h"

void Controller::encrypt(const QString& password, const QString& root, const QString& deepLink)
{
    DirUtils dirUtils;
    qDebug() <<"Root folder: "<< root;

    PathCrypter path_crypter;
    FileCrypter file_crypter;
    Fullpath fullpath = getFullPath(dirUtils, root, deepLink);

    std::vector<Fullpath> files = dirUtils.GetFiles(fullpath, Mode::Encrypt);
    if (files.size()==0){
        qDebug() << "No entries found";
    }else {
        qDebug() << files.size() << " entries found";
    }


    for (std::vector<Fullpath>::iterator it = files.begin(); it != files.end(); it++) {
        Fullpath path_fp = (*it);

        // Getting the encoded paths
        Fullpath encodedPath_fp = path_crypter.GetEncodedPath(path_fp, password);

        // Creating the directory or file
        dirUtils.CheckAndCreateDirectory(encodedPath_fp);
        if(path_fp.isDir){
            qDebug()<<"Created Dir: "<< dirUtils.GetAbsolutePath(encodedPath_fp);
        }else{
            QString absEncodedPath_str = dirUtils.GetAbsolutePath(encodedPath_fp);
            QString absPath_str = dirUtils.GetAbsolutePath(path_fp);
            file_crypter.encryptFile(absPath_str.toLatin1().data(), absEncodedPath_str.toLatin1().data(), password);
            qDebug()<<"Created File: "<< absEncodedPath_str;
        }
    }
}

void Controller::decrypt(const QString& password, const QString& root, const QString& deepLink){
    DirUtils dirUtils;
    qDebug() <<"Root folder: "<< root;

    PathCrypter path_crypter;
    FileCrypter file_crypter;
    Fullpath fullpath = getFullPath(dirUtils, root, deepLink);

    std::vector<Fullpath> files = dirUtils.GetFiles(fullpath, Mode::Decrypt);
    if (files.size()==0){
        qDebug() << "No entries found";
    }else {
        qDebug() << files.size() << " entries found";
    }

    for (std::vector<Fullpath>::iterator it = files.begin(); it != files.end(); it++) {
        Fullpath path_fp = (*it);

        // Getting the decoded paths
        Fullpath decodedPath_fp = path_crypter.GetDecodedPath(path_fp,password);

        // Creating the directory or file
        dirUtils.CheckAndCreateDirectory(decodedPath_fp);
        if(path_fp.isDir){
            //qDebug()<<"Created Dir: "<< abs_decoded_path;
        }else{
            QString absDecodedPath_str = dirUtils.GetAbsolutePath(decodedPath_fp);
            QString absPath = dirUtils.GetAbsolutePath(path_fp);
            file_crypter.decryptFile(absPath.toLatin1().data(), absDecodedPath_str.toLatin1().data(), password);
            //qDebug()<<"Created File: "<< abs_decoded_path;
        }
    }
}

Fullpath getFullPath(const DirUtils& dirUtils, const QString& root, const QString& deeperPath){
    return deeperPath.compare("")==0  ? dirUtils.CreateRootFullPath(root): dirUtils.AddDeepLinkToFP(dirUtils.CreateRootFullPath(root), deeperPath, true);
}

