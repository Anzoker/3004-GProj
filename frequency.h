#ifndef FREQUENCY_H
#define FREQUENCY_H

#include <QDialog>

namespace Ui { class Frequency; }

class Frequency : public QDialog
{
    Q_OBJECT

public:
    explicit Frequency(QWidget *parent = nullptr);
    ~Frequency();
    // For simulating power consumption.
    int getRand(int min, int max);
    int batteryStatus();
    void setBattery(int b, int cntr);
    void setPwr(int p);
    void batteryHandler();

public slots:
    void time();

private slots:
    void on_battery_lvl_valueChanged(int value); // For simulating power consumption.
    // UI.
    void on_off_button_clicked();
    void enabler();
    void on_return_2_clicked();
    void on_hz1_clicked();
    void on_hz2_clicked();
    void on_hz3_clicked();
    void on_hz4_clicked();
    void on_hz5_clicked();

private:
    Ui::Frequency *ui;
    QTimer *timer;
    // For simulating power consumption.
    int battery;
    int battery_cntr = 0;
    int pwr_usage = 0;
};

#endif // FREQUENCY_H
