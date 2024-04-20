#include "MainWindow.hpp"
#include "FileOpenDialog.hpp"

MyMainWindow::MyMainWindow() {
    label = new QLabel(this);
    label->resize(500, 100);
    label->setText("No file specified.");
    label->show();
}

MyMainWindow::~MyMainWindow() {
    if (label != nullptr) {
        delete label;
    }
}

void MyMainWindow::Execute() {
    QPushButton *button = new QPushButton(this);

    button->setText("Open file");
    QObject::connect(button, SIGNAL(clicked()), this, SLOT(clickedSlot()));
    button->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    layout->addWidget(button);

    setCentralWidget(centralWidget);
    setWindowTitle("Tteesstt");
    show();
}

void MyMainWindow::clickedSlot() {
    QFileDialogTester test;
    QString file = test.openFile();
    label->setText("You are trying to read file:  " + file);
}

