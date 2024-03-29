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
    ui->listWidget_decoded->setVisible(false);

    setIndicatorEncrypt(true);

    ui->lblProcess->setMovie(qmovie_ptr.get());
    qmovie_ptr->start();
    ui->lblProcess->setVisible(false);
}

ActivityPage::~ActivityPage()
{
    delete ui;
}

int ActivityPage::load_paths(std::vector<Fullpath> paths, QString root){
    if(!dir_utils_ptr->DoesDirectoryExist(root)){
        return 1;
    }

    if(root.compare("")!=0 && !paths.empty()){
        ui->listWidget->addItem(root);
    }

    for(std::vector<Fullpath>::iterator it = paths.begin(); it!= paths.end(); ++it){
        Fullpath fullpath = (*it);
        ui->listWidget->addItem(dir_utils_ptr->GetAbsolutePath(fullpath));
    }

    return 0;
}

int ActivityPage::load_translations(std::vector<Fullpath>& paths, QString& root){
    if(!dir_utils_ptr->DoesDirectoryExist(root)){
        return 1;
    }

    if(root.compare("")!=0 && !paths.empty()){
        ui->listWidget_decoded->addItem(root);
    }

    for(std::vector<Fullpath>::iterator it = paths.begin(); it!= paths.end(); it++){
        Fullpath fullpath = (*it);
        Fullpath decodedPath = path_crypter_ptr->GetDecodedPath(fullpath, runtimeConfigs.value(KEY_PASSWORD));
        ui->listWidget_decoded->addItem(dir_utils_ptr->GetAbsolutePath(decodedPath));

    }

    return 0;
}

void ActivityPage::on_encryptDecryptButton_clicked()
{
    if(ui->listWidget->count() == 0){
        setStatus(STATUS_LIST_IS_EMPTY);
        return;
    }

    if(ui->listWidget->selectedItems().size()==0){
        setStatus(STATUS_NO_ITEM_SELECTED);
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
        setStatus(STATUS_ENCRYPTING);
        controller_ptr->process(Mode::Encrypt, runtimeConfigs.value(KEY_PASSWORD), base, deepLink);
        setStatus(STATUS_ENCRYPTION_COMPLETED);
    }else if (current_state == Mode::Decrypt) {
        setStatus(STATUS_DECRYPTING);
        controller_ptr->process(Mode::Decrypt, runtimeConfigs.value(KEY_PASSWORD), base, deepLink);
        setStatus(STATUS_DECRYPTION_COMPLETED);
    }
    showLoadingAnimation(false);
}

void ActivityPage::on_btnEncryptSearch_clicked()
{
    showLoadingAnimation(true);
    QString cur_path_str = ui->searchBoxLineEdit->text();
    ui->listWidget->clear();
    ui->listWidget_decoded->clear();

    int ret_code = load_paths(dir_utils_ptr->GetFiles(cur_path_str, Mode::Encrypt, SearchMode::DIR_ONLY), cur_path_str);

    if(ret_code==0){
        preparePageEncrypt();
        setStatus(STATUS_LOADED);
    }else if(ret_code==1){
        setStatus(STATUS_NO_SUCH_DIRECTORY);
    }
    showLoadingAnimation(false);
}

void ActivityPage::on_btnDecryptSearch_clicked()
{
    showLoadingAnimation(true);
    QString cur_path_str = ui->searchBoxLineEdit->text();
    ui->listWidget->clear();
    ui->listWidget_decoded->clear();

    std::vector<Fullpath> foundFiles = dir_utils_ptr->GetFiles(cur_path_str, Mode::Decrypt, SearchMode::DIR_ONLY);
    int ret_code = load_paths(foundFiles, cur_path_str);

    if(ret_code==0){
        preparePageDecrypt(foundFiles, cur_path_str);
        setStatus(STATUS_LOADED);
    }else if(ret_code==1){
        setStatus(STATUS_NO_SUCH_DIRECTORY);
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


void ActivityPage::loadRuntimes(QMap<QString,QString>& input){
    runtimeConfigs.swap(input);
}


void ActivityPage::on_listWidget_decoded_itemSelectionChanged()
{
    ui->listWidget->setCurrentRow(ui->listWidget_decoded->currentRow());
}


void ActivityPage::on_listWidget_itemSelectionChanged()
{
    ui->listWidget_decoded->setCurrentRow(ui->listWidget->currentRow());
}

void ActivityPage::on_deleteButton_clicked()
{
    if(ui->listWidget->selectedItems().size()==0){
        setStatus(STATUS_LIST_IS_EMPTY);
        return;
    }

    QString selected = ui->listWidget->selectedItems().front()->text();
    QString selected_decoded_in_brackets = current_state == Mode::Decrypt? "(" + ui->listWidget_decoded->selectedItems().front()->text() + ")" : "";

    if(selected == ui->searchBoxLineEdit->text()){
        QMessageBox::critical(this, "Error", "Cannot delete root path");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete", "Delete " + selected + " ? " + selected_decoded_in_brackets, QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        dir_utils_ptr->DeleteFolder(selected);
        qDebug() << "Deleted " + selected << " " << selected_decoded_in_brackets;

        if(current_state == Mode::Encrypt){
            on_btnEncryptSearch_clicked();
        }else{
            on_btnDecryptSearch_clicked();
        }
    }
}

void ActivityPage::setIndicatorEncrypt(bool isEncrypt) const{
    if(isEncrypt){
        ui->lblIndicator_Encrypt->setStyleSheet("QLabel { background-color : green; color : white; }");
        ui->lblIndicator_Decrypt->setStyleSheet("QLabel { background-color : silver; color : white; }");
    }else{
        ui->lblIndicator_Encrypt->setStyleSheet("QLabel { background-color : silver; color : white; }");
        ui->lblIndicator_Decrypt->setStyleSheet("QLabel { background-color : green; color : white; }");
    }
}

void ActivityPage::on_btnBrowse_clicked()
{
    QString pathName = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                         "/home",
                                                         QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);

    ui->searchBoxLineEdit->setText(pathName);
}

void ActivityPage::preparePageEncrypt()
{
    current_state = Mode::Encrypt;
    ui->encryptDecryptButton->setText(ENCRYPT);
    ui->listWidget_decoded->setVisible(false);
    ui->btnMakeFolder->setEnabled(false);
    setIndicatorEncrypt(true);
}

void ActivityPage::preparePageDecrypt(std::vector<Fullpath> foundFiles, QString cur_path_str)
{
    current_state = Mode::Decrypt;
    load_translations(foundFiles, cur_path_str);
    ui->encryptDecryptButton->setText(DECRYPT);
    ui->listWidget_decoded->setVisible(true);
    ui->btnMakeFolder->setEnabled(true);
    setIndicatorEncrypt(false);
}


void ActivityPage::on_btnMakeFolder_clicked()
{
    QString root = ui->searchBoxLineEdit->text();
    QString selected = ui->listWidget_decoded->selectedItems().front()->text();
    dir_utils_ptr->CheckAndCreateDirectory(dir_utils_ptr->GetFullPathFolder(selected , root));
}
