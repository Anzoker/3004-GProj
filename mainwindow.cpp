#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QDebug>
#include <QPalette>
#include <QSizePolicy>
#include <random>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // UI setup.

    this->setFixedSize(800, 400); // Window.
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(time()));
    timer->start(1000);
    ui->default_2->setFlat(true);
    ui->default_2->setTitle("");
    ui->static_2->setFlat(true);
    ui->static_2->setTitle("");
    // Size of buttons.
    ui->settings->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->frequency->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->screening->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->program->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
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
    // Default state is off.
    ui->battery_lvl->hide();
    ui->menu_txt->hide();
    ui->clock->hide();
    ui->menu->hide();
}

MainWindow::~MainWindow() { delete ui; }

// Battery charge levels.
int MainWindow::batteryStatus() {
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
void MainWindow::batteryHandler() {
    if (status) {
         battery_cntr += 1;
    }
    if (battery_cntr > (40 + getRand(-10, 10)) and status) { // Simulating battery drain.
        battery_cntr = 0;
        battery -= 1;
        ui->battery_lvl->valueChanged(battery); // Setting value.
        if (battery <= 0) {
            on_off_button_clicked();
        } else if (battery < 6) {
            ui->program->setDisabled(true);
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
int MainWindow::getRand(int min, int max) {
    unsigned int ms = static_cast<unsigned>(QDateTime::currentMSecsSinceEpoch());
    std::mt19937 gen(ms);
    std::uniform_int_distribution<> uid(min, max);
    return uid(gen);
}

// For simulating power consumption and tracking program duration.
void MainWindow::time() {
    QTime clock = QTime::currentTime();
    QString clock_txt = clock.toString("hh : mm : ss");
    ui->clock->setText(clock_txt);
    batteryHandler();
}

// For simulating power consumption.
void MainWindow::on_battery_lvl_valueChanged(int value) {
    ui->battery_lvl->setValue(value);
    ui->battery_label->setText(QString::number(value) + "%");
}

// Button for "off".
void MainWindow::on_off_button_clicked() {
    close();
    status = false;
}

// Button for "on".
void MainWindow::on_on_button_clicked() {
    ui->battery_lvl->valueChanged(100);
    init();
}

/*///////////////////////////////////////////////////////
 *                          Menu
 * ////////////////////////////////////////////////////*/

// Button for "program".
void MainWindow::on_program_clicked() {
    hide();
    prog = new Program(this);
    prog->setBattery(battery, battery_cntr);
    prog->setPwr(pwr_usage);
    timer->stop();
    prog->show();
}

// Button for "frequency".
void MainWindow::on_frequency_clicked() {
    hide();
    freq = new Frequency(this);
    freq->setBattery(battery, battery_cntr);
    freq->setPwr(pwr_usage);
    timer->stop();
    freq->show();
}

// Button for "screening".
void MainWindow::on_screening_clicked() {
    hide();
    screen = new Screening(this);
    screen->setBattery(battery, battery_cntr);
    screen->setPwr(pwr_usage);
    timer->stop();
    screen->show();

}

/*///////////////////////////////////////////////////////
 *                         Setters
 * ////////////////////////////////////////////////////*/

// Updating battery charge.
void MainWindow::setBattery(int b, int cntr) {
    battery = b;
    battery_cntr = cntr;
    on_battery_lvl_valueChanged(b);
}

void MainWindow::setPwr(int p) { pwr_usage = p; }

// UI.
void MainWindow::init() {
    ui->battery_lvl->show();
    ui->menu->show();
    ui->menu_txt->show();
    ui->on_button->setDisabled(true);
    ui->clock->show();
    time();
    status = true;
}
