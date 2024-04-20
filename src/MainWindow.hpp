#pragma once

#include <QPushButton>
#include <QMessageBox>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextObject>

class MyMainWindow: public QMainWindow {
    Q_OBJECT

public:
    MyMainWindow();
    ~MyMainWindow();
    void Execute();

private:
    QLabel* label = nullptr;

public slots:
    void clickedSlot();
};
