#pragma once

#include <QApplication>
#include <QFileDialog>

class FileOpenDialog : public QWidget
{
public:
    QString openFile();
};