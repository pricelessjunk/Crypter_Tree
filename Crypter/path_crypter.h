/*
 * StringCrypter.h
 *
 *  Created on: May 4, 2019
 *      Author: fenris
 */

#ifndef PATHCRYPTER_H_
#define PATHCRYPTER_H_

#include <ctype.h>
#include <map>

#include "common.h"

class PathCrypter {
public:
    Fullpath GetEncodedPath(Fullpath &path, const QString &password);
    Fullpath GetDecodedPath(Fullpath &path, const QString &password);
    QString EncodeString(const QString &input, const QString &password);
    QString DecodeString(const QString &input, const QString &password);
private:
    const char* alnum_str =
            "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int NUM_CHAR_LIST_SIZE = 10;
    int CAP_ALNUM_CHAR_LIST_SIZE = 36;
    int ALNUM_CHAR_LIST_SIZE = 62;
    std::map<QString, QString> cache;
    char GetPrelistValue(int prelist_index);
    int GetPrelistIndex(char prelist_value);
};

#endif /* PATHCRYPTER_H_ */
