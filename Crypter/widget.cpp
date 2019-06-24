#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    dir_utils_ptr = std::unique_ptr<DirUtils>(new DirUtils());
    controller_ptr = std::unique_ptr<Controller>(new Controller());
    QString cur_path = "D:\\User\\Desktop\\test"; //dir_utils_ptr->GetCurrentWorkingDir()
    cur_dir = dir_utils_ptr->CreateRootFullPath(cur_path);

    ui->lineEdit->setText(dir_utils_ptr->GetAbsolutePath(cur_dir));
    load_paths(dir_utils_ptr->GetFiles(cur_dir, Mode::Encrypt, SearchMode::DIR_ONLY), cur_path);
    current_state = Mode::Encrypt;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::load_paths(std::vector<Fullpath> paths, QString root){
    ui->listWidget->clear();
    if(root.compare("")!=0){
        ui->listWidget->addItem(root);
    }

    for(std::vector<Fullpath>::iterator it = paths.begin(); it!= paths.end(); it++){
        Fullpath fullpath = (*it);
        ui->listWidget->addItem(dir_utils_ptr->GetAbsolutePath(fullpath));
    }
}

void Widget::on_encryptDecryptButton_clicked()
{
    if(ui->listWidget->selectedItems().size()==0){
        return;
    }

    QString selected = ui->listWidget->selectedItems().front()->text();

    if(current_state == Mode::Encrypt){
        setStatus("Encrypting...");
        controller_ptr->encrypt(selected, PWD);
        setStatus("Encryption Completed.");
    }else if (current_state == Mode::Decrypt) {
        setStatus("Decrypting...");
        controller_ptr->decrypt(selected, PWD);
        setStatus("Decryption Completed.");
    }
}

void Widget::on_btnEncryptSearch_clicked()
{
    QString cur_path_str = ui->lineEdit->text();
    load_paths(dir_utils_ptr->GetFiles(cur_path_str, Mode::Encrypt, SearchMode::DIR_ONLY), cur_path_str);
    current_state = Mode::Encrypt;
    setStatus("Loaded. In mode Encrypt.");
}

void Widget::on_btnDecryptSearch_clicked()
{
    QString cur_path_str = ui->lineEdit->text();
    load_paths(dir_utils_ptr->GetFiles(cur_path_str, Mode::Decrypt, SearchMode::DIR_ONLY), cur_path_str);
    current_state = Mode::Decrypt;
    setStatus("Loaded. In mode Decrypt.");
}

void Widget::setStatus(QString status){
    ui->lblStatus->setText(status);
    qApp->processEvents();
}
