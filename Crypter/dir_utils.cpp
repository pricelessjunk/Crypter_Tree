/*
     * DirUtility.cpp
     *
     *  Created on: May 4, 2019
     *      Author: fenris
     */

#include "dir_utils.h"

std::vector<Fullpath> DirUtils::GetFiles(QString root_path_str, Mode mode, SearchMode searchMode) {
    Fullpath root_path_fp = CreateRootFullPath(root_path_str);
    return GetFiles(root_path_fp, mode, searchMode);
}

std::vector<Fullpath> DirUtils::GetFiles(Fullpath root_path_fp, Mode mode, SearchMode searchMode) {
    std::vector<Fullpath> files;
    QString root = GetAbsolutePath(root_path_fp);

    //qDebug() << "processing: " << root;

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(root.toLatin1().data())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            char* c_name = ent->d_name;
            QString name(c_name);

            if((mode==Encrypt && name.endsWith(SUFFIX_ENC))||(mode==Decrypt && !name.endsWith(SUFFIX_ENC))) {
                continue;
            }

            // Skip files with extensions .exe, .dll
            std::vector<QString> exceptionList {".exe", ".dll"};
            if(mode==Encrypt && FilterFilesWithExtensions(name, exceptionList)){
                continue;
            }

            QString abs_path = root + "\\" + name;

            struct stat s;
            if( stat(abs_path.toLatin1().data(),&s) == 0 )
            {
                //When it is a dir
                if( s.st_mode & S_IFDIR )
                {
                    if (name.compare(".") != 0 && name.compare("..") != 0) {
                        Fullpath path = CreateFullPath(root_path_fp, name, true);
                        files.push_back(path);
                        //qDebug() << "\tAdded :" << abs_path;

                        std::vector<Fullpath> temp_files = GetFiles(path, mode, searchMode);
                        files.insert(files.end(), temp_files.begin(), temp_files.end());
                    }
                }
                //When it is a file
                else if( (s.st_mode & S_IFREG) && searchMode==ALL){
                    Fullpath file_path = CreateFullPath(root_path_fp, name, false);
                    files.push_back(file_path);
                     //qDebug() << "\tAdded :" << abs_path;
                }
                else{
                     qDebug()<<name<<": no idea what it is";
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

QString DirUtils::GetAbsolutePath(Fullpath& path) {
    QString output("");

    for (vector_qstring_size_t i=0;i<path.elements.size();i++) {
        output+=path.elements[i];
        if(i != path.elements.size() - 1){
            output+="\\";
        }
    }
    return output;
}

bool DirUtils::FilterFilesWithExtensions(const QString &mainStr, const std::vector<QString>& exceptionList) const{
    for (vector_qstring_size_t i=0; i<exceptionList.size(); i++) {
        if(mainStr.endsWith(exceptionList.at(i))){
            return true;
        }
    }

    return false;
}

Fullpath DirUtils::CreateRootFullPath(const QString& base) const{
    Fullpath path;
    path.isDir = true;
    path.elements.push_back(base);
    return path;
}

Fullpath DirUtils::CreateFullPath(const Fullpath& base, const QString& name, const bool& isDir) const{
    Fullpath path;
    path.isDir = isDir;
    path.elements.insert(path.elements.end(), base.elements.begin(), base.elements.end());
    path.elements.push_back(name);
    return path;
}

void DirUtils::CreateDirectory(const QString& name) const{
    if (mkdir(name.toLatin1().data()) != 0){
        qDebug() << "Directory already exists";
    }
}

bool DirUtils::DoesDirectoryExist(const QString& name) const{
    struct stat s;
    return  stat (name.toLatin1().data(), &s) == 0;
}
