#ifndef PROGRAM_H
#define PROGRAM_H

#include <QDialog>

namespace Ui { class Program; }

class Program : public QDialog
{
    Q_OBJECT

public:
    explicit Program(QWidget *parent = nullptr);
    ~Program();
    // For simulating power consumption.
    int getRand(int min, int max); 
    int batteryStatus();
    void setBattery(int b, int cntr); // Modifies battery charge.
    void setPwr(int p); // For simulating frequency.
    void batteryHandler();
    
    void handler(int s);
    void program_test();
    void disable_prog();

public slots:
    void time();
    void setValue(int value);
    void setLength(int length);
    void cnt();

private slots:
    void on_battery_lvl_valueChanged(int value); // For simulating power consumption.
    // UI
    void on_off_button_clicked();
    void on_return_2_clicked();
    void on_b1_clicked();
    void on_b2_clicked();
    void on_b3_clicked();
    void on_b4_clicked();
    void on_b5_clicked();
    void on_b6_clicked();
    void on_b7_clicked();
    void on_b8_clicked();

private:
    Ui::Program *ui;
    QTimer *timer;
    QTimer *counter;
    // For simulating power consumption.
    int battery;
    int battery_cntr = 0;
    int pwr_usage = 0; // For determining frequency.
    int answer = 0;
    int length = 0;
};

#endif // PROGRAM_H

