#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <QDebug>

#define vector_qstring_size_t std::vector<QString>::size_type

const QString SUFFIX_ENC = "_enc";
const QString PWD = "koosi";

enum Mode {Encrypt, Decrypt};
enum SearchMode {ALL, DIR_ONLY};

struct Fullpath {
    std::vector<QString> elements;
    bool isDir;
};

#endif // COMMON_H
