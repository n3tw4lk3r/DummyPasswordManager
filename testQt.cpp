#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    // QWidget window;

    QLabel *label = new QLabel();
    label->setText("Hello world!");
    label->show();

    return app.exec();
}