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
    ui->encryptButton->setChecked(true);

    load_paths(dir_utils_ptr->GetFiles(cur_dir, Mode::Encrypt, SearchMode::DIR_ONLY), cur_path);
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

void Widget::on_searchButton_clicked()
{
    QString cur_dir = ui->lineEdit->text();
    Fullpath cur_path =dir_utils_ptr->CreateRootFullPath(cur_dir);

    if(ui->encryptButton->isChecked()){
        load_paths(dir_utils_ptr->GetFiles(cur_path, Mode::Encrypt, SearchMode::DIR_ONLY), cur_dir);
    }else if (ui->decryptButton) {
        load_paths(dir_utils_ptr->GetFiles(cur_path, Mode::Decrypt, SearchMode::DIR_ONLY), cur_dir);
    }
}

void Widget::on_encryptDecryptButton_clicked()
{
    if(ui->listWidget->selectedItems().size()==0){
        return;
    }

    QString selected = ui->listWidget->selectedItems().front()->text();

    if(ui->encryptButton->isChecked()){
        ui->lblStatus->setText("Encrypting...");
        qApp->processEvents();
        controller_ptr->encrypt(selected, PWD);
        ui->lblStatus->setText("Encryption Completed.");
        qApp->processEvents();
    }else if (ui->decryptButton->isChecked()) {
        ui->lblStatus->setText("Decrypting...");
        //qApp->processEvents();
        controller_ptr->decrypt(selected, PWD);
        ui->lblStatus->setText("Decryption Completed.");
        //qApp->processEvents();
    }
}
