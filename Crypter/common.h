#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <QDebug>

#define vector_qstring_size_t std::vector<QString>::size_type

const QString SUFFIX_ENC = "_enc";
const QString PWD = "koosi";

struct Fullpath {
    std::vector<QString> elements;
    bool isDir;
};

//void print(std::string input){
//    std::cout << input << std::endl;
//}


#endif // COMMON_H
