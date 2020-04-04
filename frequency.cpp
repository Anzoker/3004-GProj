#include "frequency.h"
#include "ui_frequency.h"
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <QPalette>
#include <QSizePolicy>
#include <random>
#include "mainwindow.h"

Frequency::Frequency(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Frequency)
{
    // Setup.

    this->setFixedSize(800, 400); // Window.
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(time()));
    timer->start(1000);
    // Battery charge visual indicator.
    ui->battery_lvl->setStyleSheet("QProgressBar {"
                                   "text-align: right; }"
                                   "QProgressBar::chunk {background: rgb(247, 255, 0, 100%);}");
    time();
    ui->on_button->setDisabled(true);
    ui->default_2->setFlat(true);
    ui->default_2->setTitle("");
    ui->static_2->setFlat(true);
    ui->static_2->setTitle("");
    ui->hz1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->hz2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->hz3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->hz4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->hz5->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // Battery charge visual indicator.
    ui->battery_box->setFlat(true);
    ui->battery_box->setTitle("");
    ui->battery_lvl->setAlignment(Qt::AlignRight);
    ui->battery_lvl->resize(231, 41);
    ui->battery_lvl->setStyleSheet("QProgressBar {"
                                   "text-align: right; }"
                                   "QProgressBar::chunk {background: rgb(0, 255, 60, 100%);}");
    ui->on_button->setFlat(false);
    ui->off_button->setFlat(false);
    ui->Master->setTitle("");
    ui->battery_lvl->show();
    ui->menu->show();
    ui->clock->show();
}

Frequency::~Frequency() { delete ui; }

// Battery charge levels.
int Frequency::batteryStatus() {
    if (battery <= 0) {
        return 4;
    } else if (battery < 15) {
        return 3;
    } else if (battery < 30) {
        return 2;
    } else if (battery < 50) {
        return 1;
    } else {
        return 0;
    }
}

// For simulating power consumption.
void Frequency::batteryHandler() {
    battery_cntr += 1;
    if (battery_cntr > (40 + getRand(-10, 10))) { // Simulating battery drain.
        battery_cntr = 0;
        battery -= 1;
        ui->battery_lvl->valueChanged(battery); // Setting value.
        if(battery <= 0) {
            on_off_button_clicked();
        } else if (battery < 15) { // Displaying battery charge visual indicator.
            ui->battery_lvl->setStyleSheet("QProgressBar {"
                                           "text-align: right; }"
                                           "QProgressBar::chunk {background: rgb(255, 0, 0, 100%);}");
        } else if (battery < 30) {
            ui->battery_lvl->setStyleSheet("QProgressBar {"
                                           "text-align: right; }"
                                           "QProgressBar::chunk {background: rgb(255, 128, 0, 100%);}");
        } else if (battery < 50) {
            ui->battery_lvl->setStyleSheet("QProgressBar {"
                                           "text-align: right; }"
                                           "QProgressBar::chunk {background: rgb(247, 255, 0, 100%);}");
        }
    }

    // Displays battery charge warnings.
    int status = batteryStatus();
    if (status == 1) {
        ui->battery_msg->setText("Warning: Power Below 50%");
    } else if (status == 2) {
        ui->battery_msg->setText("Caution: Power Below 30%");
    } else if (status == 3) {
        ui->battery_msg->setText("Danger: Power Below 15%");
    }
}

// Random is used in simulating power consumption.
int Frequency::getRand(int min, int max) {
    unsigned int ms = static_cast<unsigned>(QDateTime::currentMSecsSinceEpoch());
    std::mt19937 gen(ms);
    std::uniform_int_distribution<> uid(min, max);
    return uid(gen);
}

// For simulating power consumption and tracking program duration.
void Frequency::time() {
    QTime clock = QTime::currentTime();
    QString clock_txt = clock.toString("hh : mm : ss");
    ui->clock->setText(clock_txt);
    batteryHandler();
}

// For simulating power consumption.
void Frequency::on_battery_lvl_valueChanged(int value) {
    ui->battery_lvl->setValue(value);
    ui->battery_label->setText(QString::number(value) + "%");
}

void Frequency::on_off_button_clicked() { close(); }

// Updating battery charge.
void Frequency::setBattery(int b, int cntr) {
    battery = b;
    battery_cntr = cntr;
    on_battery_lvl_valueChanged(b);
}

// User selects "return" to go back to the main menu.
void Frequency::on_return_2_clicked() {
    hide();
    MainWindow *w = new MainWindow();
    w->setBattery(battery, battery_cntr);
    w->setPwr(pwr_usage);
    w->init();
    timer->stop();
    w->show();
}

// Buttons for choosing frequency.
void Frequency::on_hz1_clicked() {
    enabler();
    ui->hz1->setDisabled(true);
    pwr_usage = 1;
}

void Frequency::on_hz2_clicked() {
    enabler();
    ui->hz2->setDisabled(true);
    pwr_usage = 2;
}

void Frequency::on_hz3_clicked() {
    enabler();
    ui->hz3->setDisabled(true);
    pwr_usage = 3;
}

void Frequency::on_hz4_clicked() {
    enabler();
    ui->hz4->setDisabled(true);
    pwr_usage = 4;
}

void Frequency::on_hz5_clicked()
{
    enabler();
    ui->hz5->setDisabled(true);
    pwr_usage = 5;
}

// UI
void Frequency::enabler(){
    ui->hz1->setDisabled(false);
    ui->hz2->setDisabled(false);
    ui->hz3->setDisabled(false);
    ui->hz4->setDisabled(false);
    ui->hz5->setDisabled(false);
}

// For choosing frequency.
void Frequency::setPwr(int p){
    pwr_usage = p;
    if(p == 1){
        on_hz1_clicked();
    } else if (p == 2){
        on_hz2_clicked();
    } else if (p == 3){
        on_hz3_clicked();
    } else if (p == 4){
        on_hz4_clicked();
    } else if (p == 5){
        on_hz5_clicked();
    }
}
