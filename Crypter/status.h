#ifndef STATUS_H
#define STATUS_H

#include <QDialog>

namespace Ui {
class Status;
}

class Status : public QDialog
{
    Q_OBJECT

public:
    explicit Status(QWidget *parent = nullptr);
    ~Status();

private:
    Ui::Status *ui;
};

#endif // STATUS_H
