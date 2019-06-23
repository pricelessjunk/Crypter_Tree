#include "testtextencrption.h"

void TestTextEncryption::testTextEncryption(){
    PathCrypter crypter;

    QString input("abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    QString encoded = crypter.EncodeString(input, "koosi");
    QCOMPARE(encoded, "3I3N3O3T3K3N3S3T3Y3P3S3X3Y3d3U3X3c3d3i3Z3c3h3i3n3e3h2Z2a2f2W2Z2e2f2k2b2e2q2r2w2n2q2v2w312s2v3031362x3035363B32353A3B3G373A3F");
}

void TestTextEncryption::testTextDecryption(){
    PathCrypter crypter;

    QString input("3I3N3O3T3K3N3S3T3Y3P3S3X3Y3d3U3X3c3d3i3Z3c3h3i3n3e3h2Z2a2f2W2Z2e2f2k2b2e2q2r2w2n2q2v2w312s2v3031362x3035363B32353A3B3G373A3F");
    QString decoded = crypter.DecodeString(input, "koosi");
    QCOMPARE(decoded,"abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

//void TestTextEncryption::testEncrypt(){
//    PathCrypter crypter;
//    DirUtils dirutils;

//    Fullpath path = dirutils.CreateRootFullPath("D:\\User\\Desktop\\test\\user");
//    Fullpath pathExtended = dirutils.CreateFullPath(path,"user",true);
//    QString encryptedPath = crypter.GetEncodedPath(pathExtended , "koosi");
//    QCOMPARE(encryptedPath, QString("D:\\User\\Desktop\\test\\3W383Y1c_enc"));
//}

//void TestTextEncryption::testDecrypt(){
//    PathCrypter crypter;
//    DirUtils dirutils;

//    Fullpath path = dirutils.CreateRootFullPath("D:\\User\\Desktop\\test\\3c3G3g3i3a3a2Q_enc");
//    Fullpath pathExtended = dirutils.CreateFullPath(path,"user",true);
//    QString encryptedPath = crypter.GetEncodedPath(pathExtended , "koosi");
//    QCOMPARE(encryptedPath, QString("D:\\User\\Desktop\\test\\3W383Y1c_enc"));
//}

QTEST_MAIN(TestTextEncryption)
