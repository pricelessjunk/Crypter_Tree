#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // QApplication::quit();

    Login l;
    l.setWindowTitle(TITLE_LOGIN);
    l.show();

    return a.exec();
}

