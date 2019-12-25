#include "controller.h"

void Controller::process(const Mode& mode, const QString& password, const QString& root, const QString& deepLink){
    DirUtils dirUtils;
    qDebug() <<"Root folder: "<< root;

    PathCrypter path_crypter;
    FileCrypter file_crypter;
    Fullpath fullpath = getFullPath(dirUtils, root, deepLink);

    std::vector<Fullpath> files = dirUtils.GetFiles(fullpath, mode);
    if (files.size()==0){
        qDebug() << "No entries found";
    }else {
        qDebug() << files.size() << " entries found";
    }


    for (std::vector<Fullpath>::iterator it = files.begin(); it != files.end(); it++) {
        Fullpath path_fp = (*it);

        Fullpath processedPath_fp;
        if (mode == Mode::Encrypt){
            // Getting the encoded paths
            processedPath_fp = path_crypter.GetEncodedPath(path_fp, password);
        }else{
            // Getting the decoded paths
            processedPath_fp = path_crypter.GetDecodedPath(path_fp,password);
        }

        // Creating the directory or file
        dirUtils.CheckAndCreateDirectory(processedPath_fp);
        if(path_fp.isDir){
            // qDebug()<<"Created Dir: "<< dirUtils.GetAbsolutePath(processedPath_fp);
        }else{
            QString absProcessedPath_str = dirUtils.GetAbsolutePath(processedPath_fp);
            QString absPath_str = dirUtils.GetAbsolutePath(path_fp);
            file_crypter.processFile(absPath_str.toLatin1().data(), absProcessedPath_str.toLatin1().data(), password);
            // qDebug()<<"Created File: "<< absEncodedPath_str;
        }
    }
}

Fullpath getFullPath(const DirUtils& dirUtils, const QString& root, const QString& deeperPath){
    return deeperPath.compare("")==0  ? dirUtils.CreateRootFullPath(root): dirUtils.AddDeepLinkToFP(dirUtils.CreateRootFullPath(root), deeperPath, true);
}

