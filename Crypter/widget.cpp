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

int Widget::load_paths(std::vector<Fullpath> paths, QString root){
    ui->listWidget->clear();

    if(!dir_utils_ptr->DoesDirectoryExist(root)){
        return 1;
    }

    if(root.compare("")!=0){
        ui->listWidget->addItem(root);
    }

    for(std::vector<Fullpath>::iterator it = paths.begin(); it!= paths.end(); it++){
        Fullpath fullpath = (*it);
        ui->listWidget->addItem(dir_utils_ptr->GetAbsolutePath(fullpath));
    }

    return 0;
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
    int ret_code = load_paths(dir_utils_ptr->GetFiles(cur_path_str, Mode::Encrypt, SearchMode::DIR_ONLY), cur_path_str);

    if(ret_code==0){
        current_state = Mode::Encrypt;
        setStatus("Loaded. In mode Encrypt.");
    }else if(ret_code==1){
        setStatus("Directory not found.");
    }
}

void Widget::on_btnDecryptSearch_clicked()
{
    QString cur_path_str = ui->lineEdit->text();
    int ret_code = load_paths(dir_utils_ptr->GetFiles(cur_path_str, Mode::Decrypt, SearchMode::DIR_ONLY), cur_path_str);

    if(ret_code==0){
        current_state = Mode::Decrypt;
        setStatus("Loaded. In mode Decrypt.");
    }else if(ret_code==1){
        setStatus("Directory not found.");
    }
}

void Widget::setStatus(QString status){
    ui->lblStatus->setText(status);
    qApp->processEvents();
}
