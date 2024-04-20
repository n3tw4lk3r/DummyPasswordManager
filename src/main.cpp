#include <QApplication>
#include <QMainWindow>
#include "MainWindow.hpp"


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MyMainWindow window;

    window.setWindowTitle(QString::fromUtf8("MainWindow"));
    window.resize(400, 400);
    window.Execute();

    return app.exec();
}
