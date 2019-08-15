#include "login.h"
#include "ui_login.h"

Login::Login(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    string_crypter_ptr = std::unique_ptr<PathCrypter>(new PathCrypter());
}

Login::~Login()
{
    delete ui;
}

void Login::on_btnOk_clicked()
{
    if(ui->lePassInput->text().compare("koosi")!=0){
        ui->lblLoginStatus->setText("Wrong Password.");
        return;
    }

    ActivityPage* ap = new ActivityPage(this);
    this->hide();
    ap->setModal(true);
    ap->show();
}

void Login::on_btnGenerate_clicked()
{
    QString output = string_crypter_ptr ->EncodeString(ui->genPassInputLineEdit->text(), "koosi");
    ui->leGenPassOutput->setText(output);
    ui->lblLoginStatus->setText("Password generation successful.");
}
