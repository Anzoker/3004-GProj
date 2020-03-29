#ifndef SCREENING_H
#define SCREENING_H

#include <QDialog>

namespace Ui {
class Screening;
}

class Screening : public QDialog
{
    Q_OBJECT

public:
    explicit Screening(QWidget *parent = nullptr);
    ~Screening();
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
    Ui::Screening *ui;
    QTimer *timer;
    int battery;
    int battery_cntr = 0;
    int pwr_usage = 0;
};

#endif // Screening_H

