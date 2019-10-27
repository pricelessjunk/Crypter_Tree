#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::load_paths(std::vector<Fullpath> paths, QString root){
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

int MainWindow::load_translations(std::vector<Fullpath>& paths, QString& root){

    if(root.compare("")!=0){
        ui->listWidget_decoded->addItem(root);
    }

    for(std::vector<Fullpath>::iterator it = paths.begin(); it!= paths.end(); it++){
        Fullpath fullpath = (*it);
        Fullpath decodedPath = path_crypter_ptr->GetDecodedPath(fullpath, runtimeConfigs.value(KEY_PASSWORD));
        ui->listWidget_decoded->addItem(dir_utils_ptr->GetAbsolutePath(decodedPath));

    }

    return 0;
}

void MainWindow::on_encryptDecryptButton_clicked()
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
        controller_ptr->encrypt(runtimeConfigs.value(KEY_PASSWORD), base, deepLink);
        setStatus("Encryption Completed.");
    }else if (current_state == Mode::Decrypt) {
        setStatus("Decrypting...");
        controller_ptr->decrypt(runtimeConfigs.value(KEY_PASSWORD), base, deepLink);
        setStatus("Decryption Completed.");
    }
    showLoadingAnimation(false);
}

void MainWindow::on_btnEncryptSearch_clicked()
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

void MainWindow::on_btnDecryptSearch_clicked()
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

void MainWindow::setStatus(QString status){
    ui->lblStatus->setText(status);
    qApp->processEvents();
}

void MainWindow::showLoadingAnimation(bool loading){
    ui->lblProcess->setVisible(loading);
}

void MainWindow::loadRuntimes(QMap<QString,QString>& input){
    runtimeConfigs.swap(input);
}


void MainWindow::on_listWidget_decoded_itemSelectionChanged()
{
    ui->listWidget->setCurrentRow(ui->listWidget_decoded->currentRow());
}


void MainWindow::on_listWidget_itemSelectionChanged()
{
    ui->listWidget_decoded->setCurrentRow(ui->listWidget->currentRow());
}

void MainWindow::on_deleteButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Test", "Quit?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
        QApplication::quit();
    } else {
        qDebug() << "Yes was *not* clicked";
    }
}
