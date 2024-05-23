#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "passwordswindow.h"
#include "FileOpenDialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->masterpasswordLineEdit->setEchoMode(QLineEdit::Password);
    setWindowTitle("     ");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startButton_clicked()
{
    QString file = ui->openFileLabel->text(),
            password = ui->masterpasswordLineEdit->text();

    std::cout << file.toStdString() << '\n';
    if (file == "Файл не выбран") {
        QMessageBox::critical(this, "Ошибка", "Файл не выбран");
        return;
    }

    std::string fileMasterPassword;
    try {
        std::fstream inputFile(file.toStdString());
        std::string fileFormatString;

        std::getline(inputFile, fileFormatString);
        if (fileFormatString != "DMPFile") {
            throw std::runtime_error("File corrupted");
        }
        inputFile >> fileMasterPassword;

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", "Файл поврежден");
        return;
    }

    // хэшировать введенный пароль
    if (hash(password.toStdString()) == fileMasterPassword) {
        std::cout << "Password correct\n";
        hide();
        PasswordsWindow window(file, password);
        window.setModal(true);
        window.exec();
        return;
    }

    QMessageBox::critical(this, "Ошибка", "Введен неверный мастер-пароль");
}


void MainWindow::on_OpenFileButton_clicked()
{
     FileOpenDialog openDialog;
     QString file = openDialog.openFile();
     ui->openFileLabel->setText(file);
}



void MainWindow::on_newFileButton_clicked()
{
    hide();
    PasswordsWindow window;
    window.setModal(true);
    window.exec();
}

