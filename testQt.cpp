#include <QApplication>
#include <QLabel>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QLabel* label = new QLabel();
    label->setText("Hello world!");
    label->show();

    int status = app.exec();
    delete label; // в Qt родители автоматически удаляют детей
                  // но если родителя нет, надо удалить вручную, иначе утечка

    return status;
}
