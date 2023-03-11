#include "mainwindow.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    a.setWindowIcon(QIcon(":/urlparser.png"));
    w.setWindowTitle("urlparser");
    w.show();

    return a.exec();
}
