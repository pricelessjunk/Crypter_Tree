#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "common.h"
#include "widget.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:

    void on_btnOk_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
