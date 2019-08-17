#include "login.h"
#include "ui_login.h"
#include <QFile>


Login::Login(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    string_crypter_ptr = std::unique_ptr<PathCrypter>(new PathCrypter());

    loadConfig();
    PWD = runtimeConfigs.take("password");
}

Login::~Login()
{
    delete ui;
}

void Login::on_btnOk_clicked()
{
    if(ui->lePassInput->text().compare(PWD)!=0){
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
    QString output = string_crypter_ptr ->EncodeString(ui->genPassInputLineEdit->text(), PWDENC);
    ui->leGenPassOutput->setText(output);
    ui->lblLoginStatus->setText("Password generation successful.");
}

void Login::loadConfig()
{
    QFile qFile("../config/crypter.cfg");

    if (qFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&qFile);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList splits = line.split(":");

            QString key = splits.front();
            if(key.compare("password")==0){
                runtimeConfigs.insert(key, getDecryptedPass(splits.back()));
            }else {
                runtimeConfigs.insert(key, splits.back());
            }


        }
        qFile.close();
    }

    qDebug() << "Loading config complete";
}

QString Login::getDecryptedPass(QString& input){
    return string_crypter_ptr ->DecodeString(input, PWDENC);
}

