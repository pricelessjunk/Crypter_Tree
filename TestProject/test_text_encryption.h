#ifndef TEST_TEXT_ENCRYPTION_H
#define TEST_TEXT_ENCRYPTION_H

#include <QtTest/QtTest>

#include "../Crypter/path_crypter.h"
#include "../Crypter/dir_utils.h"

class TestTextEncryption: public QObject
{
    Q_OBJECT
private slots:
    void testTextEncryption();
    void testTextDecryption();
};

#endif // TEST_TEXT_ENCRYPTION_H
