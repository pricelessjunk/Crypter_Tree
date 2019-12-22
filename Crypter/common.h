#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <QDebug>
#include <QMap>

/*
 * MACROS
 */
#define vector_qstring_size_t std::vector<QString>::size_type

static QMap<QString, QString> runtimeConfigs ;

#ifdef _WIN32
const QString SEPERATOR = "\\";
const QString CONFIG_PATH = qEnvironmentVariable("CRYPTER_CONFIG").append("\\crypter.cfg");
#define MKDIR mkdir(name.toLatin1().data())
#else
const QString SEPERATOR = "/";
const QString CONFIG_PATH = (new QString(std::getenv("HOME")))->append("/.config/crypter/crypter.cfg");
#define MKDIR mkdir(name.toLatin1().data(), S_IRWXU|S_IRGRP|S_IXGRP |S_IROTH|S_IXOTH)
#endif

enum Mode {Encrypt, Decrypt};
enum SearchMode {ALL, DIR_ONLY};

struct Fullpath {
    std::vector<QString> elements;
    bool isDir;
};

#endif // COMMON_H

/*
 * CONSTANTS
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

static const QString SUFFIX_ENC = "_enc";
static const QString KEY_PASSWORD = "password";
static const QString KEY_EXCEPTION = "exception";

static const QString STATUS_LIST_IS_EMPTY = "List is empty.";
static const QString STATUS_NO_SUCH_DIRECTORY = "No such directory.";
static const QString STATUS_NO_ITEM_SELECTED = "No item selected.";
static const QString STATUS_DECRYPTING = "Decrypting...";
static const QString STATUS_ENCRYPTING = "Encrypting...";
static const QString STATUS_DECRYPTION_COMPLETED = "Decryption completed";
static const QString STATUS_ENCRYPTION_COMPLETED = "Encryption completed";
static const QString STATUS_LOADED = "Loaded";

static const QString ENCRYPT = "Encrypt";
static const QString DECRYPT = "Decrypt";


#endif  // CONSTANTS_H
