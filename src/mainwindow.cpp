#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "passwordswindow.h"
#include "FileOpenDialog.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->masterpasswordLineEdit->setEchoMode(QLineEdit::Password);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startButton_clicked()
{
    QString login = ui->usernameLineEdit->text(),
            password = ui->masterpasswordLineEdit->text();

    /* ToDo: нормальная проверка логина и пароля, открытие файла */
    if (login == "одмин" && password == "пороль") {
        hide();
        PasswordsWindow window;
        window.setModal(true);
        window.exec();
    }

    else {
        QMessageBox::critical(this, "Ты дурак", "Неверный логин или пароль");
    }
}


void MainWindow::on_OpenFileButton_clicked()
{
     FileOpenDialog openDialog;
     QString file = openDialog.openFile();
     ui->openFileLabel->setText(file);
}

