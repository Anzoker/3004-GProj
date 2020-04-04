#ifndef SCREENING_H
#define SCREENING_H

#include <QDialog>

namespace Ui { class Screening; }

class Screening : public QDialog
{
    Q_OBJECT

public:
    explicit Screening(QWidget *parent = nullptr);
    ~Screening();
    // For simulating power consumption.
    int getRand(int min, int max);
    int batteryStatus();
    void setBattery(int b, int cntr);
    void setPwr(int p);
    void batteryHandler();

public slots:
    void time();
    void cnt();
    void setValue(int value);

private slots:
    void on_battery_lvl_valueChanged(int value); // For simulating power consumption.
    // UI.
    void on_off_button_clicked();
    void on_return_2_clicked();
    void on_screen_clicked();

private:
    Ui::Screening *ui;
    void scrn_test();
    QTimer *timer;
    QTimer *counter;
    // For simulating power consumption.
    int battery;
    int answer = 0;
    int battery_cntr = 0;
    int pwr_usage = 0;
};

#endif // Screening_H

