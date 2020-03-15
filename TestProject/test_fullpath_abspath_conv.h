#ifndef TEST_FULLPATH_ABSPATH_CONV_H
#define TEST_FULLPATH_ABSPATH_CONV_H

#include <QtTest/QtTest>

#include "../Crypter/dir_utils.h"

class TestAbspathFullpathConv: public QObject
{
    Q_OBJECT
private slots:
    void test_abspath_to_fullpath();
    void test_fullpath_to_abspath();
};

#endif // TEST_FULLPATH_ABSPATH_CONV_H
