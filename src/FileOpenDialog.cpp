#include "FileOpenDialog.hpp"

QString QFileDialogTester::openFile() {
    QString filename =  QFileDialog::getOpenFileName(
        this,
        "Open Document",
        QDir::currentPath(),
        "Document files (*.txt)");

    if (!filename.isNull()) {
        return filename;
    }

    return "-1";
}
