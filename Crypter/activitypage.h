#ifndef ACTIVITYPAGE_H
#define ACTIVITYPAGE_H

#include <QDialog>
#include <iostream>
#include <memory>

#include <QtWidgets/QListWidget>
#include <QMovie>

#include "dir_utils.h"
#include "controller.h"

namespace Ui {
class ActivityPage;
}

class ActivityPage : public QDialog
{
    Q_OBJECT
    std::unique_ptr<DirUtils> dir_utils_ptr;
    std::unique_ptr<Controller> controller_ptr;
    std::unique_ptr<PathCrypter> path_crypter_ptr;
    Fullpath cur_dir;
    Mode current_state;
    std::unique_ptr<QMovie> qmovie_ptr = std::unique_ptr<QMovie>(new QMovie(":/ajax-loader.gif"));

public:
    explicit ActivityPage(QWidget *parent = nullptr);
    ~ActivityPage();
    void setStatus(QString status);

private slots:
    void on_encryptDecryptButton_clicked();

    void on_btnEncryptSearch_clicked();

    void on_btnDecryptSearch_clicked();

private:
    Ui::ActivityPage *ui;

    int load_paths(std::vector<Fullpath> paths, QString root = "");

    int load_translations(std::vector<Fullpath>& paths, QString& root);

    void showLoadingAnimation(bool loading);

};

#endif // ACTIVITYPAGE_H