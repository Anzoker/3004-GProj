#include "program.h"
#include "ui_program.h"
#include "program_confirm.h"
#include "program_length.h"
#include "mainwindow.h"
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <QPalette>
#include <QSizePolicy>
#include <random>

Program::Program(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Program)
{
    // UI setup.

    this->setFixedSize(800, 430); // Window.
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(time()));
    timer->start(1000);
    // Battery charge visual indicator.
    ui->battery_lvl->setStyleSheet("QProgressBar {"
                                   "text-align: right; }"
                                   "QProgressBar::chunk {background: rgb(247, 255, 0, 100%);}");
    time();
    ui->default_2->setFlat(true);
    ui->default_2->setTitle("");
    ui->static_2->setFlat(true);
    ui->static_2->setTitle("");
    // Battery charge visual indicator.
    ui->battery_box->setFlat(true);
    ui->battery_box->setTitle("");
    ui->b1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->b2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->b3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->b4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->b5->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->b6->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->b7->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->b8->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // Battery charge visual indicator.
    ui->battery_lvl->setAlignment(Qt::AlignRight);
    ui->battery_lvl->resize(231, 41);
    ui->on_button->setDisabled(true);
    ui->battery_lvl->setStyleSheet("QProgressBar {"
                                   "text-align: right; }"
                                   "QProgressBar::chunk {background: rgb(0, 255, 60, 100%);}");
    ui->on_button->setFlat(false);
    ui->off_button->setFlat(false);
    ui->Master->setTitle("");
    ui->battery_lvl->show();
    ui->menu->show();
    ui->clock->show();
    ui->menu2->hide();
    ui->progress->setValue(0);
    ui->report->hide();

}

Program::~Program() { delete ui; }

// Battery charge levels.
int Program::batteryStatus() {
    if (battery <= 0){
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

void Program::batteryHandler() {
    battery_cntr += 1;
    if (battery_cntr > (40 + getRand(-10, 10))) { // Simulating power consumption.
        battery_cntr = 0;
        battery -= 1;
        ui->battery_lvl->valueChanged(battery); // Sets value.
        if (battery <= 0) {
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
int Program::getRand(int min, int max) {
    unsigned int ms = static_cast<unsigned>(QDateTime::currentMSecsSinceEpoch());
    std::mt19937 gen(ms);
    std::uniform_int_distribution<> uid(min, max);
    return uid(gen);
}

// For simulating power consumption and tracking program duration.
void Program::time() {
    QTime clock = QTime::currentTime();
    QString clock_txt = clock.toString("hh : mm : ss");
    ui->clock->setText(clock_txt);
    batteryHandler();
}

// For simulating power consumption.
void Program::on_battery_lvl_valueChanged(int value) {
    ui->battery_lvl->setValue(value);
    ui->battery_label->setText(QString::number(value) + "%"); // Displays battery charge percentage.
}

void Program::on_off_button_clicked() { close(); }

// Updating battery charge.
void Program::setBattery(int b, int cntr) {
    battery = b;
    battery_cntr = cntr;
    on_battery_lvl_valueChanged(b);
}

// Determining frequency.
void Program::setPwr(int p) {
    pwr_usage = p;
    if(pwr_usage == 0){ // If user fails to select a frequency.
        ui->b1->setDisabled(true);
        ui->b2->setDisabled(true);
        ui->b3->setDisabled(true);
        ui->b4->setDisabled(true);
        ui->b5->setDisabled(true);
        ui->b6->setDisabled(true);
        ui->b7->setDisabled(true);
        ui->b8->setDisabled(true);
        ui->report->show();
        ui->report->setText("No Frequency Selected  -- ERROR");
    }
}

void Program::setValue(int i) { answer = i; }

void Program::setLength(int i) { length = i; }

// User selects "return" to go back to the main menu.
void Program::on_return_2_clicked() {
    hide();
    MainWindow *w = new MainWindow();
    w->setBattery(battery, battery_cntr);
    w->setPwr(pwr_usage);
    w->init();
    timer->stop();
    w->show();
}

void Program::on_b1_clicked() { handler(1); }

void Program::on_b2_clicked() { handler(2); }

void Program::on_b3_clicked() { handler(3); }

void Program::on_b4_clicked() { handler(4); }

void Program::on_b5_clicked() { handler(5); }

void Program::on_b6_clicked() { handler(6); }

void Program::on_b7_clicked() { handler(7); }

void Program::on_b8_clicked() { handler(8); }

// Confirming sensors were attached.
void Program::handler(int s) {
    program_confirm test;
    test.setModal(true); // Window state.
    connect(&test, &program_confirm::valueChanged, this, &Program::setValue);
    test.setText(s);
    test.exec();
    if(answer == 1) { // If the sensors were properly attached.
        program_test();
    } else {
        disable_prog();
        ui->report->setText("The device sensors were not place properly.  -- ERROR");
        ui->report->show();
        this->exec();
    }
}

// Executing the program.
void Program::program_test() {
    program_length test;
    test.setModal(true); // Window state.
    connect(&test, &program_length::valueChanged, this, &Program::setLength);
    test.exec();
    length = length * 60; // Minutes -> seconds.
    counter = new QTimer(this);
    connect(counter, SIGNAL(timeout()), this, SLOT(cnt()));
    ui->progress->setRange(0, length);
    
    // Beginning treatment.
    QString pwr;
    if(pwr_usage == 1){
        pwr = " 10Hz ";
    }else if(pwr_usage == 2){
        pwr = " 20Hz ";
    }else if(pwr_usage == 3){
        pwr = " 60Hz ";
    }else if(pwr_usage == 4){
        pwr = " 125Hz ";
    }else if(pwr_usage == 5){
        pwr = " 200Hz ";
    }
    
    // Displaying the duration of the program.
    QString duration;
    if(length/60 == 1) {
        duration = " 1 Minute ";
    }else if(length/60 == 10) {
        duration = " 10 Minutes ";
    }else if(length/60 == 30) {
        duration = " 30 Minutes ";
    }else if(length/60 == 60) {
        duration = " 1 Hour ";
    }

    ui->msg->setText("Treatment Underway at" + pwr + "for" + duration + ".");
    ui->menu->hide();  // Changing UI.
    ui->menu2->show();
    ui->return_2->setDisabled(true);
    counter->start(1000); // Beginning treatment.
    this->exec();
}

// Finishing treatment.
void Program::cnt() {
    battery_cntr += getRand(1 + pwr_usage, 5 + pwr_usage);  // For simulating power consumption.
    int val = ui->progress->value() + 1;
    if (val >= length){
        val = length;
    }
    ui->progress->setValue(val);
    if(ui->progress->value() >= length) { // If treatment finishes.
        counter->stop();
        ui->menu2->hide(); // Changing UI.
        ui->menu->show();
        ui->return_2->setDisabled(false);
        disable_prog();
        ui->report->setText("Successful Treatment.");
        ui->report->show();
    }
}

void Program::disable_prog() {
    int temp = pwr_usage;
    setPwr(0);
    setPwr(temp);
}
