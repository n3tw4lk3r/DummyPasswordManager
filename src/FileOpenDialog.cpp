#include "FileOpenDialog.h"

QString FileOpenDialog::openFile()
{
    QString filename =  QFileDialog::getOpenFileName(
        this,
        "Open Document",
        QDir::currentPath(),
        "Document files (*.txt)");

    if (!filename.isNull()) {
        return "Открыт файл: " + filename;
    }

    return "Файл не указан";
}

// FileOpenDialog test;
// QString file = test.openFile();
// ui->label->setText(file);