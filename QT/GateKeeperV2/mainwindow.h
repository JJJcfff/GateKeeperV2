#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void start_clock();
    int get_override_pwd();

    void on_EmergenryOveride_button_clicked();

    void on_modify_budget_button_clicked();

    void hide_jcard_buttons();

    void show_jcard_buttons();

private:
    Ui::MainWindow *ui;
};
#define mainwindow ((MainWindow*)parent_handle)
#endif // MAINWINDOW_H
