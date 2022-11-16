#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    start_clock();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start_clock(){
    ui->setupUi(this);
    QTimer *t = new QTimer(this);
    t->setInterval(1000);
    connect(t, &QTimer::timeout, [&]() {
       QString time1 = QTime::currentTime().toString();
       ui->clock->setText(time1);
    });
    t->start();
}

