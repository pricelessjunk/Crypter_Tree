#include "activitypage.h"
#include "ui_activitypage.h"

ActivityPage::ActivityPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ActivityPage)
{
    ui->setupUi(this);
    dir_utils_ptr = std::unique_ptr<DirUtils>(new DirUtils());
    controller_ptr = std::unique_ptr<Controller>(new Controller());
    path_crypter_ptr = std::unique_ptr<PathCrypter>(new PathCrypter());
    //QString cur_path = "D:\\User\\Desktop\\test"; //dir_utils_ptr->GetCurrentWorkingDir()
    QString cur_path = "/home/vedicmonk/test"; //dir_utils_ptr->GetCurrentWorkingDir()
    cur_dir = dir_utils_ptr->CreateRootFullPath(cur_path);

    ui->searchBoxLineEdit->setText(dir_utils_ptr->GetAbsolutePath(cur_dir));
    load_paths(dir_utils_ptr->GetFiles(cur_dir, Mode::Encrypt, SearchMode::DIR_ONLY), cur_path);
    current_state = Mode::Encrypt;

    ui->lblProcess->setMovie(qmovie_ptr.get());
    qmovie_ptr->start();
    ui->lblProcess->setVisible(false);
}

ActivityPage::~ActivityPage()
{
    delete ui;
}

int ActivityPage::load_paths(std::vector<Fullpath> paths, QString root){
    ui->listWidget->clear();

    if(!dir_utils_ptr->DoesDirectoryExist(root)){
        return 1;
    }

    if(root.compare("")!=0){
        ui->listWidget->addItem(root);
    }

    for(std::vector<Fullpath>::iterator it = paths.begin(); it!= paths.end(); ++it){
        Fullpath fullpath = (*it);
        ui->listWidget->addItem(dir_utils_ptr->GetAbsolutePath(fullpath));
    }

    return 0;
}

int ActivityPage::load_translations(std::vector<Fullpath>& paths, QString& root){

    if(root.compare("")!=0){
        ui->listWidget_decoded->addItem(root);
    }

    for(std::vector<Fullpath>::iterator it = paths.begin(); it!= paths.end(); it++){
        Fullpath fullpath = (*it);
        Fullpath decodedPath = path_crypter_ptr->GetDecodedPath(fullpath, PWD);
        ui->listWidget_decoded->addItem(dir_utils_ptr->GetAbsolutePath(decodedPath));

    }

    return 0;
}

void ActivityPage::on_encryptDecryptButton_clicked()
{
    if(ui->listWidget->selectedItems().size()==0){
        return;
    }

    showLoadingAnimation(true);
    QString selected = ui->listWidget->selectedItems().front()->text();
    QString base = ui->searchBoxLineEdit->text();
    QString deepLink  = "";

    // Change to QFileInfo later
    if(selected != base){
        deepLink = selected.right(selected.length() - base.length() - 1);
    }

    if(current_state == Mode::Encrypt){
        setStatus("Encrypting...");
        controller_ptr->encrypt(PWD, base, deepLink);
        setStatus("Encryption Completed.");
    }else if (current_state == Mode::Decrypt) {
        setStatus("Decrypting...");
        controller_ptr->decrypt(PWD, base, deepLink);
        setStatus("Decryption Completed.");
    }
    showLoadingAnimation(false);
}

void ActivityPage::on_btnEncryptSearch_clicked()
{
    showLoadingAnimation(true);
    QString cur_path_str = ui->searchBoxLineEdit->text();
    ui->listWidget_decoded->clear();

    int ret_code = load_paths(dir_utils_ptr->GetFiles(cur_path_str, Mode::Encrypt, SearchMode::DIR_ONLY), cur_path_str);

    if(ret_code==0){
        current_state = Mode::Encrypt;
        setStatus("Loaded. In mode Encrypt.");
    }else if(ret_code==1){
        setStatus("Directory not found.");
    }
    showLoadingAnimation(false);
}

void ActivityPage::on_btnDecryptSearch_clicked()
{
    showLoadingAnimation(true);
    QString cur_path_str = ui->searchBoxLineEdit->text();
    ui->listWidget_decoded->clear();

    std::vector<Fullpath> foundFiles = dir_utils_ptr->GetFiles(cur_path_str, Mode::Decrypt, SearchMode::DIR_ONLY);
    int ret_code = load_paths(foundFiles, cur_path_str);

    if(ret_code==0){
        current_state = Mode::Decrypt;
        load_translations(foundFiles, cur_path_str);
        setStatus("Loaded. In mode Decrypt.");
    }else if(ret_code==1){
        setStatus("Directory not found.");
    }

    showLoadingAnimation(false);
}

void ActivityPage::setStatus(QString status){
    ui->lblStatus->setText(status);
    qApp->processEvents();
}

void ActivityPage::showLoadingAnimation(bool loading){
    ui->lblProcess->setVisible(loading);
}
