#ifndef PROGRAM_H
#define PROGRAM_H

#include <QDialog>

namespace Ui {
class Program;
}

class Program : public QDialog
{
    Q_OBJECT

public:
    explicit Program(QWidget *parent = nullptr);
    ~Program();
    int getRand(int min, int max);
    int batteryStatus();
    void setBattery(int b, int cntr);
    void batteryHandler();

public slots:
    void time();

private slots:
    void on_battery_lvl_valueChanged(int value);
    void on_off_button_clicked();

private:
    Ui::Program *ui;
    QTimer *timer;
    int battery;
    int battery_cntr = 0;
    int pwr_usage = 0;
};

#endif // Program_H

