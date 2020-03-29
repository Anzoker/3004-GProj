#ifndef FREQUENCY_H
#define FREQUENCY_H

#include <QDialog>

namespace Ui {
class Frequency;
}

class Frequency : public QDialog
{
    Q_OBJECT

public:
    explicit Frequency(QWidget *parent = nullptr);
    ~Frequency();
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
    Ui::Frequency *ui;
    QTimer *timer;
    int battery;
    int battery_cntr = 0;
    int pwr_usage = 0;
};

#endif // FREQUENCY_H
