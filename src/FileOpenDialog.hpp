#pragma once

#include <QApplication>
#include <QFileDialog>

class QFileDialogTester : public QWidget {
public:
    QString openFile();
};