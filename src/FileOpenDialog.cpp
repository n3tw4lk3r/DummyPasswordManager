#include "FileOpenDialog.h"

QString FileOpenDialog::openFile()
{
    QString filename =  QFileDialog::getOpenFileName(
        this,
        "Open Document",
        QString("passwords.dpm"),
        "DummyPasswordManager files (*.dpm)");

    if (!filename.isNull()) {
        return filename;
    }

    return "Файл не выбран";
}
