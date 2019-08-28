#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <QDebug>
#include <QMap>

#define vector_qstring_size_t std::vector<QString>::size_type
const QString SUFFIX_ENC = "_enc";
const QString KEY_PASSWORD = "password";
const QString KEY_EXCEPTION = "exception";
const QString CONFIG_PATH = (new QString(std::getenv("HOME")))->append("/.config/crypter/crypter.cfg");

static QMap<QString, QString> runtimeConfigs ;

#ifdef _WIN32
const QString SEPERATOR = "\\";
#else
const QString SEPERATOR = "/";
#endif

enum Mode {Encrypt, Decrypt};
enum SearchMode {ALL, DIR_ONLY};

struct Fullpath {
    std::vector<QString> elements;
    bool isDir;
};

#endif // COMMON_H
