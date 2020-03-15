QT       += core testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TESTPROJ
TEMPLATE = app

INCLUDEPATH    = ../Crypter

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

include(../Crypter/Crypter.pri)

SOURCES += \
    main_test.cpp \
    test_fullpath_abspath_conv.cpp \
    test_text_encryption.cpp \

HEADERS += \
    test_fullpath_abspath_conv.h \
    test_text_encryption.h \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

