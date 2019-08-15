#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <QDebug>

#define vector_qstring_size_t std::vector<QString>::size_type

const QString SUFFIX_ENC = "_enc";
//const QString SEPERATOR = "\\";
const QString SEPERATOR = "/";
const QString PWD = "koosi";
const QString PWDENC= "\x6b\x6f\x6f\x73\x69\x24\x32\x34\x38\x38";

enum Mode {Encrypt, Decrypt};
enum SearchMode {ALL, DIR_ONLY};

struct Fullpath {
    std::vector<QString> elements;
    bool isDir;
};

#endif // COMMON_H
