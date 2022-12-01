#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "BaseConverter.h"
#include <QTimer>
#include <QTime>
#include <QDateTime>
#include <iostream>
#include <ctime>
#include <chrono>
#include <cmath>
#include <QCryptographicHash>

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

void MainWindow::start_clock()
{
    ui->setupUi(this);
    QTimer *t = new QTimer(this);
    t->setInterval(1000);
    connect(t, &QTimer::timeout, [&]() {
        QString time1 = QTime::currentTime().toString();
        ui->clock->setText(time1);
    });
    t->start();
    get_override_pwd();
}


int MainWindow::get_override_pwd()
{
    struct std::tm a = {0,0,0,5,0,70}; // Monday, January 5th 1970 at 00:00:00
    const BaseConverter& hex2dec = BaseConverter::HexToDecimalConverter();
    std::time_t x = std::mktime(&a);
    std::time_t y = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    double difference = std::difftime(y, x) / (60 * 60 * 24 * 7);
    QString weeks = QString::fromStdString(std::to_string(int(std::round(difference))));
    QString salt = "09e1cda686f8a1b1";
    QByteArray hash = QCryptographicHash::hash((weeks+salt).toUtf8(), QCryptographicHash::Sha256);
    std::string hex_string = (hash.toHex(0)).toStdString();
    for (auto & c: hex_string) c = toupper(c);
    std::string decimal_string = hex2dec.Convert(hex_string.substr(hex_string.size()-16,hex_string.size()));
    decimal_string = decimal_string.substr(decimal_string.size()-6,decimal_string.size());
    int override_pwd = std::stoi(decimal_string);
    return override_pwd;
}
