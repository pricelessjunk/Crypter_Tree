#include "test_fullpath_abspath_conv.h"


void TestAbspathFullpathConv::test_abspath_to_fullpath()
{
    DirUtils dir_utils;

    {
        // Logic exists for folder only now
        QString root = "D:" + SEPERATOR + "path1";
        QString abspath =  root + SEPERATOR + "path2" + SEPERATOR + "path3";
        Fullpath fp = dir_utils.GetFullPathFolder(abspath, root);
        QCOMPARE(true, fp.isDir);
        QCOMPARE(3, fp.elements.size());
        QCOMPARE(root, fp.elements[0]);
        QCOMPARE("path2", fp.elements[1]);
        QCOMPARE("path3", fp.elements[2]);
    }
}

void TestAbspathFullpathConv::test_fullpath_to_abspath()
{
    DirUtils dir_utils;

    {
        // Folder
        Fullpath fp;
        fp.isDir = true;
        const QString root = "D:" + SEPERATOR + "path1";
        fp.elements = {root, "path2", "path3"};

        QString path = dir_utils.GetAbsolutePath(fp);
        const QString result = root + SEPERATOR + "path2" + SEPERATOR + "path3";
        QCOMPARE(path, result);
    }

    {
        // File
        Fullpath fp;
        fp.isDir = false;
        const QString root = "D:" + SEPERATOR + "path1";
        fp.elements = {root, "path2", "path3.jpg"};

        QString path = dir_utils.GetAbsolutePath(fp);
        const QString result = root + SEPERATOR + "path2" + SEPERATOR + "path3.jpg";
        QCOMPARE(path, result);
    }
}

//QTEST_MAIN(TestAbspathFullpathConv);
