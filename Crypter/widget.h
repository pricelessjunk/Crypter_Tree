#ifndef WIDGET_H
#define WIDGET_H

#include <iostream>
#include <memory>

#include <QWidget>
#include <QtWidgets/QListWidget>

#include "dir_utils.h"
#include "controller.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    std::unique_ptr<DirUtils> dir_utils_ptr;
    std::unique_ptr<Controller> controller_ptr;
    Fullpath cur_dir;
    Mode current_state;

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void setStatus(QString status);

private slots:
    void on_encryptDecryptButton_clicked();

    void on_btnEncryptSearch_clicked();

    void on_btnDecryptSearch_clicked();

private:
    Ui::Widget *ui;

    int load_paths(std::vector<Fullpath> paths, QString root = "");
};

#endif // WIDGET_H
