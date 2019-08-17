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
}

Login::~Login()
{
    delete ui;
}

void Login::on_btnOk_clicked()
{
    if(ui->lePassInput->text().compare(runtimeConfigs.value(KEY_PASSWORD))!=0){
        ui->lblLoginStatus->setText("Wrong Password.");
        return;
    }

    ActivityPage* ap = new ActivityPage(this);
    this->hide();
    ap->loadRuntimes(runtimeConfigs);
    ap->setModal(true);
    ap->show();
}

void Login::on_btnGenerate_clicked()
{
    QString output = string_crypter_ptr ->EncodeString(ui->genPassInputLineEdit->text(), PWDENC);
    ui->leGenPassOutput->setText(output);
    ui->lblLoginStatus->setText("Password generation successful.");
}

void Login::on_btnChange_clicked()
{
    if(ui->OldPassLineEdit->text().compare(runtimeConfigs.value(KEY_PASSWORD))!=0){
        ui->lblLoginStatus->setText("Wrong Old Password.");
        return;
    }

    QFile qFile("config" + SEPERATOR +"crypter.cfg");
    QFile wqFile("config" + SEPERATOR +"crypter.cfg.write");

    if (qFile.open(QIODevice::ReadOnly) && wqFile.open(QIODevice::WriteOnly))
    {
        QTextStream in(&qFile);
        QTextStream out(&wqFile);

        while (!in.atEnd())
        {
            QString line = in.readLine();

            if(line.startsWith(KEY_PASSWORD + ":")){
                line = KEY_PASSWORD + ":" + string_crypter_ptr ->EncodeString(ui->newPassLineEdit->text(), PWDENC);
            }

            out << line << "\n";
        }

        qFile.close();
        wqFile.close();

        QString name = qFile.fileName();
        qFile.remove();
        wqFile.rename(name);

        loadConfig();
        ui->lblLoginStatus->setText("Password changed successfully");
        ui->OldPassLineEdit->setText("");
        ui->newPassLineEdit->setText("");
    }
}

void Login::loadConfig()
{
    QFile qFile("config" + SEPERATOR +"crypter.cfg");

    if (qFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&qFile);
        runtimeConfigs.clear();

        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList splits = line.split(":");

            QString key = splits.front();
            if(key.compare(KEY_PASSWORD)==0){
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



