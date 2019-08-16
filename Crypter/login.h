#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <fstream>
#include "common.h"
#include "activitypage.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT
    std::unique_ptr<PathCrypter> string_crypter_ptr;
    const QString PWDENC= "\x6b\x6f\x6f\x73\x69\x24\x32\x34\x38\x38";

public:
    explicit Login(QDialog *parent = nullptr);
    ~Login();

private slots:

    void on_btnOk_clicked();

    void on_btnGenerate_clicked();

private:
    Ui::Login *ui;

    void loadConfig();

    QString getDecryptedPass(QString& input);
};

#endif // LOGIN_H
