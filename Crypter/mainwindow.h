#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDialog>
#include <iostream>
#include <memory>

#include <QtWidgets/QListWidget>
#include <QMovie>
#include <QMessageBox>

#include "dir_utils.h"
#include "controller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    std::unique_ptr<DirUtils> dir_utils_ptr;
    std::unique_ptr<Controller> controller_ptr;
    std::unique_ptr<PathCrypter> path_crypter_ptr;
    Fullpath cur_dir;
    Mode current_state;
    std::unique_ptr<QMovie> qmovie_ptr = std::unique_ptr<QMovie>(new QMovie(":/ajax-loader.gif"));

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setStatus(QString status);
    void loadRuntimes(QMap<QString,QString>& input);

private slots:
    void on_encryptDecryptButton_clicked();

    void on_btnEncryptSearch_clicked();

    void on_btnDecryptSearch_clicked();

    void on_listWidget_decoded_itemSelectionChanged();

    void on_listWidget_itemSelectionChanged();

    void on_deleteButton_clicked();

private:
    Ui::MainWindow *ui;

    int load_paths(std::vector<Fullpath> paths, QString root = "");

    int load_translations(std::vector<Fullpath>& paths, QString& root);

    void showLoadingAnimation(bool loading);

};

#endif // MAINWINDOW_H
