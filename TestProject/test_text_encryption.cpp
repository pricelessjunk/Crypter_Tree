#include "test_text_encryption.h"

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

// QTEST_MAIN(TestTextEncryption)
