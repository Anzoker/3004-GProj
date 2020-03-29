#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();
    int getRand(int min, int max);
    int batteryStatus();
    void setBattery(int b, int cntr);
    void setPwr(int p);
    void batteryHandler();

public slots:
    void time();

private slots:
    void on_battery_lvl_valueChanged(int value);
    void on_off_button_clicked();

private:
    Ui::Settings *ui;
    QTimer *timer;
    int battery;
    int battery_cntr = 0;
    int pwr_usage = 0;
};

#endif // Settings_H

