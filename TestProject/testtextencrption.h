#ifndef TESTTEXTENCRYPTION_H
#define TESTTEXTENCRYPTION_H

#include <QtTest/QtTest>

#include "../Crypter/path_crypter.h"
#include "../Crypter/dir_utils.h"

class TestTextEncryption: public QObject
{
    Q_OBJECT
private slots:
    void testTextEncryption();
    void testTextDecryption();
//    void testEncrypt();
//    void testDecrypt();
};

#endif // TESTTEXTENCRYPTION_H
