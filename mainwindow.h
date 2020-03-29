#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "frequency.h"
#include "settings.h"
#include "screening.h"
#include "program.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int getRand(int min, int max);
    int batteryStatus();
    void batteryHandler();

public slots:
    void time();

private slots:

    void on_battery_lvl_valueChanged(int value);

    void on_off_button_clicked();

    void on_on_button_clicked();

    void on_program_clicked();

    void on_frequency_clicked();

    void on_screening_clicked();

    void on_settings_clicked();

private:
    Ui::MainWindow *ui;
    Settings *sett;
    Program  *prog;
    Frequency *freq;
    Screening *screen;
    int battery = 100;
    int battery_cntr = 0;
    int pwr_usage = 0;
    bool status = false;
    QTimer *timer;
};
#endif // MAINWINDOW_H
