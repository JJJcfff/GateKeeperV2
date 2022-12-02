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
#include <QMovie>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    start_clock();
    start_swipe_animation();
    hideOverrideInput();
    ui->EmergencyOverridInput->setEchoMode(QLineEdit::Password);
    ui->EmergencyOverridInput->setClearButtonEnabled(true);
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
        ui->clock->setAlignment(Qt::AlignCenter);
    });
    t->start();
}

void MainWindow::start_swipe_animation()
{
    QMovie* swipe = new QMovie(":/image/resource/image/cardswipe.gif");
    if (swipe->isValid())
    {
        ui->cardswipeanimation->setScaledContents(true);
        ui->cardswipeanimation->setMovie(swipe);
        swipe->start();
    }
}


QString MainWindow::get_override_pwd()
{
    struct std::tm a = {0,0,0,5,0,70}; // Monday, January 5th 1970 at 00:00:00
    const BaseConverter& hex2dec = BaseConverter::HexToDecimalConverter();
    std::time_t x = std::mktime(&a);
    std::time_t y = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    double difference = std::difftime(y, x) / (60 * 60 * 24 * 7);
    QString weeks = QString::fromStdString(std::to_string(int(std::floor(difference))));
    QString salt = "09e1cda686f8a1b1";
    QByteArray hash = QCryptographicHash::hash((weeks+salt).toUtf8(), QCryptographicHash::Sha256);
    std::string hex_string = (hash.toHex(0)).toStdString();
    for (auto & c: hex_string) c = toupper(c);
    std::string decimal_string = hex2dec.Convert(hex_string.substr(hex_string.size()-16,hex_string.size()));
    decimal_string = decimal_string.substr(decimal_string.size()-6,decimal_string.size());
    int override_pwd = std::stoi(decimal_string);
    return QString::number(override_pwd);
}

void MainWindow::hide_jcard_buttons()
{
    ui->JcardEnter_textBox->hide();
    ui->enterJcardHint_Label->hide();
    ui->cardswipeanimation->hide();
    ui->swipeJcard_button->hide();
}

void MainWindow::show_jcard_buttons()
{
    ui->JcardEnter_textBox->show();
    ui->enterJcardHint_Label->show();
    ui->cardswipeanimation->show();
    ui->swipeJcard_button->show();
}

void MainWindow::on_EmergenryOveride_button_clicked()
{
    hide_jcard_buttons();
    showOverrideInput();
    overridepassword = get_override_pwd();
}

void MainWindow::showOverrideInput()
{
    ui->overrideInput->show();
}

void MainWindow::hideOverrideInput()
{
    ui->overrideInput->hide();
}

void MainWindow::on_modify_budget_button_clicked()
{

}


void MainWindow::on_EmergencyOverridInput_returnPressed()
{
    qDebug() << overridepassword << ui->EmergencyOverridInput->text();

    if (ui->EmergencyOverridInput->text()==overridepassword)
    {
        hideOverrideInput();
        show_jcard_buttons();
    }
    ui->EmergencyOverridInput->clear();
}

