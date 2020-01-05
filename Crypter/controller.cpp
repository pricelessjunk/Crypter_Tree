#include "controller.h"


void Controller::process(const Mode& mode, const QString& password, const QString& root, const QString& deepLink){
    DirUtils dirUtils;
    qDebug() <<"Root folder: "<< root;

    PathCrypter path_crypter;
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

        QThreadPool::globalInstance()->setMaxThreadCount(maxThreadCount);
        if(path_fp.isDir){
            // qDebug()<<"Created Dir: "<< dirUtils.GetAbsolutePath(processedPath_fp);
        }else{
            QString absProcessedPath_str = dirUtils.GetAbsolutePath(processedPath_fp);
            QString absPath_str = dirUtils.GetAbsolutePath(path_fp);

            while ( QThreadPool::globalInstance()->activeThreadCount() == maxThreadCount){
                QThread::msleep(50);
            }

            FileCrypter* file_crypter = new FileCrypter(absPath_str, absProcessedPath_str, password);
            QThreadPool::globalInstance()->start(file_crypter);
        }
    }

    while(QThreadPool::globalInstance()->activeThreadCount()!=0){
         // qDebug() << "Threads still remaining " << QThreadPool::globalInstance()->activeThreadCount();
        QThread::msleep(50);
    }

    qDebug() << "All threads completed successfully.";
}

Fullpath getFullPath(const DirUtils& dirUtils, const QString& root, const QString& deeperPath){
    return deeperPath.compare("")==0  ? dirUtils.CreateRootFullPath(root): dirUtils.AddDeepLinkToFP(dirUtils.CreateRootFullPath(root), deeperPath, true);
}

