#include "mainwindow.h"
#include <fstream>
#include <QDateTime>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowCloseButtonHint);
//    QScreen *screen = QGuiApplication::primaryScreen();
//    QRect  screenGeometry = screen->geometry();
//    int height = screenGeometry.height();
//    int width = screenGeometry.width();
//    w.resize(width,height);
    w.showFullScreen();
    return a.exec();
}
