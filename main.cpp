#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    qApp->setStyle(QStyleFactory::create("Fusion"));
    w.show();
    return a.exec();
}
