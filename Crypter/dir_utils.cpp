/*
     * DirUtility.cpp
     *
     *  Created on: May 4, 2019
     *      Author: fenris
     */

#include "dir_utils.h"

std::vector<Fullpath> DirUtils::GetFiles(QString rootPath_str, Mode mode, SearchMode searchMode) {
    Fullpath rootPath_fp = CreateRootFullPath(rootPath_str);
    return GetFiles(rootPath_fp, mode, searchMode);
}

std::vector<Fullpath> DirUtils::GetFiles(Fullpath rootPath_fp, Mode mode, SearchMode searchMode) {
    std::vector<Fullpath> files;
    QString root = GetAbsolutePath(rootPath_fp);

    DIR *dir;
    struct dirent *ent;
    qDebug() << "Processing: " << root;
    if ((dir = opendir(root.toLatin1().data())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            char* name_c = ent->d_name;
            QString name(name_c);

            if((mode==Encrypt && name.endsWith(SUFFIX_ENC))||(mode==Decrypt && !name.endsWith(SUFFIX_ENC))) {
                continue;
            }

            if(mode==Encrypt && FilterFilesWithExtensions(name)){
                continue;
            }

            QString abs_path = root + SEPERATOR + name;

            struct stat s;
            if( stat(abs_path.toLatin1().data(),&s) == 0 )
            {
                //When it is a dir
                if( s.st_mode & S_IFDIR )
                {
                    if (name.compare(".") != 0 && name.compare("..") != 0) {
                        Fullpath path_fp = AddDeepLinkToFP(rootPath_fp, name, true);
                        files.push_back(path_fp);
                        //qDebug() << "\tAdded :" << abs_path;

                        std::vector<Fullpath> temp_files = GetFiles(path_fp, mode, searchMode);
                        files.insert(files.end(), temp_files.begin(), temp_files.end());
                    }
                }
                //When it is a file
                else if( (s.st_mode & S_IFREG) && searchMode==ALL){
                    Fullpath file_path = AddDeepLinkToFP(rootPath_fp, name, false);
                    files.push_back(file_path);
                }
                else{
                    //qDebug()<<name<<": no idea what it is";
                }
            }else{
                 qDebug()<<"Error at "<<name<<".Error " <<strerror(errno);
            }
        }
        closedir(dir);
    }else {
        perror("Could not open directory");
    }

    return files;
}

QString DirUtils::GetCurrentWorkingDir() {
    char buff[FILENAME_MAX];
    GetCurrentDir(buff, FILENAME_MAX);
    QString current_working_dir(buff);
    return current_working_dir;
}

QString DirUtils::GetAbsolutePath(const Fullpath& path) {
    // Sending -1 to keep compatibility with index to which it should parse.
    return GetAbsolutePath(path, path.elements.size());
}

QString DirUtils::GetAbsolutePath(const Fullpath& path, vector_qstring_size_t index) {
    QString output("");

    for (vector_qstring_size_t i=0; i < index; i++) {
        output+=path.elements[i];
        if(i != index - 1){
            output+=SEPERATOR;
        }
    }
    return output;
}

bool DirUtils::FilterFilesWithExtensions(const QString &mainStr) const{
    QStringRef extension(&mainStr, mainStr.length()-4, 4);
    return runtimeConfigs.value(KEY_EXCEPTION).contains(extension);
}

Fullpath DirUtils::CreateRootFullPath(const QString& base) const{
    Fullpath path;
    path.isDir = true;
    path.elements.push_back(base);
    return path;
}

Fullpath DirUtils::AddDeepLinkToFP(const Fullpath& base, const QString& deepLink, const bool& isDir) const{
    Fullpath path;
    path.isDir = isDir;
    path.elements.insert(path.elements.end(), base.elements.begin(), base.elements.end());

    QStringList splits = deepLink.split(SEPERATOR);
    path.elements.insert(path.elements.end(), splits.begin(), splits.end());

    return path;
}

void DirUtils::CheckAndCreateDirectory(const Fullpath& fullPath){
    vector_qstring_size_t ignoreFileName = fullPath.isDir? 0: 1;

    for (vector_qstring_size_t i=1; i< fullPath.elements.size() - ignoreFileName; i++) {
        QString name = GetAbsolutePath(fullPath, static_cast<vector_qstring_size_t>(i + 1));  // +1 To keep compatibility with size
        if (MKDIR != 0){
            qDebug() << "An error occured during creating the directory" << name;
        }
    }
}

bool DirUtils::DoesDirectoryExist(const QString& name) const{
    struct stat s;
    return  stat (name.toLatin1().data(), &s) == 0;
}
