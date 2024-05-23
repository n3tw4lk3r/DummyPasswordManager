#ifndef PASSWORDSWINDOW_H
#define PASSWORDSWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QGridLayout>
#include <QTextEdit>
#include <QShortcut>
#include <QInputDialog>
#include <QMessageBox>
#include <iomanip>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "crypto.h"
#include "passwordEncoder.h"

namespace Ui {
class PasswordsWindow;
}

class PasswordsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordsWindow();
    explicit PasswordsWindow(QString openedFile, QString masterPassword);
    ~PasswordsWindow();

private slots:
    void on_addGroupButton_clicked();
    void on_changeMasterPassword_clicked();
    void on_exportButton_clicked();

    void on_generatePasswordButton_clicked();

    void on_aboutButton_clicked();

private:
    Ui::PasswordsWindow *ui;
    std::vector<QTextEdit*> lineEditsPtrs;
    QGridLayout* lay;
    QString openedFile_, masterPassword_;
    void saveFile();
    void saveFileAs();
    void createKeyboardShortcuts();
    void deleteGroup();
    void editGroup();
};

#endif // PASSWORDSWINDOW_H
