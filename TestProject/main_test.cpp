#ifndef MAIN_TEST_H
#define MAIN_TEST_H

#include "test_text_encryption.h"
#include "test_fullpath_abspath_conv.h"

#include <QtTest/QtTest>

int main(int argc, char *argv[])
{
   int status = 0;

   {
       TestTextEncryption ta;
       status |= QTest::qExec(&ta, argc, argv);
   }

   {
       TestAbspathFullpathConv ta;
       status |= QTest::qExec(&ta, argc, argv);
   }

   return status;
}

#endif // MAIN_TEST_H

