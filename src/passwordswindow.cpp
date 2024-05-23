#include "passwordswindow.h"
#include "ui_passwordswindow.h"
#include "FileOpenDialog.h"

PasswordsWindow::PasswordsWindow() :
    QDialog(nullptr),
    ui(new Ui::PasswordsWindow)
{
    ui->setupUi(this);
    QWidget *container = new QWidget;
    ui->passwordsScrollArea->setWidget(container);
    lay = new QGridLayout(container);
    createKeyboardShortcuts();
    while (masterPassword_.toStdString().empty())
            on_changeMasterPassword_clicked();
    ui->generatedPasswordLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    setWindowTitle("     ");
}

PasswordsWindow::PasswordsWindow(QString openedFile, QString masterPassword) :
    QDialog(nullptr),
    ui(new Ui::PasswordsWindow),
    openedFile_(openedFile),
    masterPassword_(masterPassword)
{
    ui->setupUi(this);
    QWidget *container = new QWidget;
    ui->passwordsScrollArea->setWidget(container);
    lay = new QGridLayout(container);
    createKeyboardShortcuts();
    ui->generatedPasswordLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    setWindowTitle("     ");

    std::fstream inputFile(openedFile_.toStdString(),  std::ios::in | std::ios::binary);
    std::string format, password;
    std::getline(inputFile, format);
    std::getline(inputFile, password);
    std::string encoded, tmp;
    while (inputFile >> tmp)
        encoded += tmp;

    std::cerr << encoded << '\n';
    encoded = base64_decode(encoded);
    std::cerr << encoded << '\n';
    std::string decrypted = decrypt(encoded, masterPassword_.toStdString());
    std::cerr << decrypted << '\n';
    std::map<name_of_group, group_of_passwords> passwords = decode(decrypted);
    for (auto& [groupName, groupText] : passwords) {
        std::string text = groupName + '\n';
        std::cerr << groupName << '\n';
        for (auto& [a, b] : groupText) {
            std::cerr << a << ' ' << b << '\n';
            text += b;
        }
        QTextEdit* tmp = new QTextEdit(this);
        lineEditsPtrs.push_back(tmp);
        lay->addWidget(tmp);
        lineEditsPtrs[lineEditsPtrs.size() - 1]->setText(QString::fromStdString(text));
        lineEditsPtrs[lineEditsPtrs.size() - 1]->show();
    }
}

PasswordsWindow::~PasswordsWindow()
{
    QMessageBox::StandardButton shouldSaveFile;
      shouldSaveFile = QMessageBox::question(this, "   ", "Сохранить файл?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (shouldSaveFile == QMessageBox::Yes)
        saveFile();

    delete ui;
}

void PasswordsWindow::on_addGroupButton_clicked()
{
    QTextEdit* tmp = new QTextEdit(this);
    lineEditsPtrs.push_back(tmp);
    lay->addWidget(tmp);
    lineEditsPtrs[lineEditsPtrs.size() - 1]->setText("Новая группа");
    lineEditsPtrs[lineEditsPtrs.size() - 1]->show();
}


void PasswordsWindow::on_changeMasterPassword_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(0, "   ", "Новый мастер-пароль:", QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
        masterPassword_ = text;
        return;
    }
    QMessageBox::information(this, "Ошибка", "Мастер-пароль не может быть пустым");
}


void PasswordsWindow::on_exportButton_clicked()
{
    saveFileAs();
}

void PasswordsWindow::createKeyboardShortcuts()
{
    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_D), this);
    QObject::connect(shortcut, &QShortcut::activated, this, &PasswordsWindow::deleteGroup);

    QShortcut *shortcut2 = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_E), this);
    QObject::connect(shortcut2, &QShortcut::activated, this, &PasswordsWindow::editGroup);
}

void PasswordsWindow::deleteGroup()
{
    for (std::vector<QTextEdit*>::iterator it = lineEditsPtrs.begin(); it != lineEditsPtrs.end(); ++it) {
        if ((*it)->hasFocus()) {
            delete *it;
            lineEditsPtrs.erase(it);
            return;
        }
    }
}

void PasswordsWindow::editGroup() {
    for (std::vector<QTextEdit*>::iterator it = lineEditsPtrs.begin(); it != lineEditsPtrs.end(); ++it) {
        if ((*it)->hasFocus()) {
            (*it)->setReadOnly((*it)->isReadOnly() ^ 1);
            return;
        }
    }
}

void PasswordsWindow::saveFile() {
    if (masterPassword_.toStdString().empty()) {
        on_changeMasterPassword_clicked();
    }

    if (openedFile_.toStdString().empty()) {
        saveFileAs();
        return;
    }

    std::map<std::string, std::map<std::string, std::string>> passwordGroups;
    for (auto& ptr : lineEditsPtrs) {
        std::string groupName;
        std::string groupText = ptr->toPlainText().toStdString();

        for (size_t i = 0; i < groupText.size(); ++i) {
            if (groupText[i] == '\n') {
                groupText = groupText.substr(i + 1);
                break;
            }
            groupName += groupText[i];
        }

        passwordGroups[groupName]["text"] = groupText;
    }

    std::string encrypted = encrypt(encode(passwordGroups), masterPassword_.toStdString());
    std::cerr << encode(passwordGroups) << ' ' << encrypted << ' ' << decrypt(encrypted, masterPassword_.toStdString()) << " aaa\n";
    std::ofstream file;
    file.open(openedFile_.toStdString(), std::ofstream::out | std::ios::binary | std::ofstream::trunc);
    file << "DMPFile\n";
    file << hash(masterPassword_.toStdString()) << '\n';
    std::cerr << encrypted << '\n';
    std::cerr << base64_encode(encrypted) << '\n';
    file << base64_encode(encrypted);
    file.close();
}

void PasswordsWindow::saveFileAs() {
    QFileDialog* fileDialog = new QFileDialog;
    fileDialog->setLabelText(QFileDialog::Accept, "Save");
    fileDialog->setLabelText(QFileDialog::Reject, "Cancel");
    auto file = fileDialog->getSaveFileName();
    delete fileDialog;
    if (file.toStdString().empty())
        return;
    openedFile_ = file;
    saveFile();
}

void PasswordsWindow::on_generatePasswordButton_clicked()
{
    size_t len = ui->passwordLengthcomboBox->currentText().toUInt();
    std::string generatedPassword;
    if (ui->radioButton_1->isChecked()) {
        generatedPassword = generateRandomPassword(type::only_int, len);
    }

    if (ui->radioButton_2->isChecked()) {
        generatedPassword = generateRandomPassword(type::all_letters, len);
    }

    if (ui->radioButton_3->isChecked()) {
        generatedPassword = generateRandomPassword(type::someone_letters, len);
    }

    ui->generatedPasswordLabel->setText("Сгенерированный пароль:\n" + QString::fromStdString(generatedPassword));
}


void PasswordsWindow::on_aboutButton_clicked()
{
    QMessageBox::information(
                this,
                "Как пользоваться приложением",
                "В левой части окна находятся группы с паролями. \
                 Чтобы удалить группу, кликните на неё и нажмите Ctrl-D.  \
                 Также возможно заблокировать изменение группы, для этого нажмите Ctrl-E. Для разблокировки опять нажмите Ctrl-E. \
                "
    );
}

