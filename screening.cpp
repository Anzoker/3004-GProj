#include "screening.h"
#include "ui_screening.h"
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <QPalette>
#include <QSizePolicy>
#include <random>
#include "mainwindow.h"
#include "screening_confirm.h"

Screening::Screening(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Screening)
{
    //Setup
    this->setFixedSize(800, 400);

    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(time()));
    timer->start(1000);

    ui->battery_lvl->setStyleSheet("QProgressBar {"
                                   "text-align: right; }"
                                   "QProgressBar::chunk {background: rgb(247, 255, 0, 100%);}");
    time();
    ui->on_button->setDisabled(true);
    ui->menu2->hide();
    ui->default_2->setFlat(true);
    ui->default_2->setTitle("");
    ui->report->hide();

    ui->static_2->setFlat(true);
    ui->static_2->setTitle("");

    ui->battery_box->setFlat(true);
    ui->battery_box->setTitle("");

    ui->screen->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

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

Screening::~Screening()
{
    hide();
}

int Screening::batteryStatus(){
    if (battery <= 0){
        return 4;
    } else if (battery < 15){
        return 3;
    } else if (battery < 30){
        return 2;
    } else if (battery < 50){
        return 1;
    } else {
        return 0;
    }
}

void Screening::batteryHandler(){
    battery_cntr += 1;
    if (battery_cntr > (40 + getRand(-10, 10))){
        battery_cntr = 0;
        battery -= 1;
        ui->battery_lvl->valueChanged(battery);
        if(battery <= 0){
            on_off_button_clicked();
        } else if (battery < 15){
            ui->battery_lvl->setStyleSheet("QProgressBar {"
                                           "text-align: right; }"
                                           "QProgressBar::chunk {background: rgb(255, 0, 0, 100%);}");
        } else if (battery < 30){
            ui->battery_lvl->setStyleSheet("QProgressBar {"
                                           "text-align: right; }"
                                           "QProgressBar::chunk {background: rgb(255, 128, 0, 100%);}");
        } else if (battery < 50){
            ui->battery_lvl->setStyleSheet("QProgressBar {"
                                           "text-align: right; }"
                                           "QProgressBar::chunk {background: rgb(247, 255, 0, 100%);}");
        }
    }

    int status = batteryStatus();
    if (status == 1){
        ui->battery_msg->setText("Warning: Power Below 50%");
    } else if (status == 2){
        ui->battery_msg->setText("Caution: Power Below 30%");
    } else if (status == 3){
        ui->battery_msg->setText("Danger: Power Below 15%");
    } else if (status == 4){\
        //Should never happen, but edge case.
        //ui->battery_msg->setText("Out of power.");
    }
}

int Screening::getRand(int min, int max){
    unsigned int ms = static_cast<unsigned>(QDateTime::currentMSecsSinceEpoch());
    std::mt19937 gen(ms);
    std::uniform_int_distribution<> uid(min, max);
    return uid(gen);
}

void Screening::time()
{
    QTime clock = QTime::currentTime();
    QString clock_txt = clock.toString("hh : mm : ss");
    ui->clock->setText(clock_txt);
    batteryHandler();
}

void Screening::on_battery_lvl_valueChanged(int value)
{
    ui->battery_lvl->setValue(value);
    ui->battery_label->setText(QString::number(value) + "%");
}

void Screening::on_off_button_clicked()
{
    close();
}

void Screening::setBattery(int b, int cntr){
    battery = b;
    battery_cntr = cntr;
    on_battery_lvl_valueChanged(b);
}

void Screening::setPwr(int p){
    pwr_usage = p;
}

void Screening::on_return_2_clicked()
{
    hide();
    MainWindow *w = new MainWindow();
    w->setBattery(battery, battery_cntr);
    w->setPwr(pwr_usage);
    w->init();
    timer->stop();
    w->show();
}

void Screening::on_screen_clicked()
{
    ui->report->hide();
    screening_confirm test;
    test.setModal(true);
    connect(&test, &screening_confirm::valueChanged, this, &Screening::setValue);
    test.exec();
    if(answer == 1){
        scrn_test();
    } else {
        ui->report->setText("The device sensors were not place properly.  -- ERROR");
        ui->report->show();
        ui->screen->setDisabled(true);
        this->exec();
    }
}

void Screening::setValue(int i){
    answer = i;
}

void Screening::scrn_test(){
    ui->menu->hide();
    ui->progress->setRange(0, 100);
    ui->progress->setValue(0);
    ui->menu2->show();
    ui->return_2->setDisabled(true);
    counter = new QTimer(this);
    connect(counter, SIGNAL(timeout()), this, SLOT(cnt()));
    counter->start(200);
    this->exec();
}

void Screening::cnt()
{
    battery_cntr += getRand(0, 2);
    int val = ui->progress->value() + 4 + getRand(-1, 1);
    if (val > 100){
        val = 100;
    }
    ui->progress->setValue(val);
    if(ui->progress->value() >= 100){
        counter->stop();
        ui->menu2->hide();
        ui->menu->show();
        ui->return_2->setDisabled(false);
        float val2 = getRand(0, 160);
        if (val2 < 100){
            ui->report->setText("The reported ΔLt value is : " + QString::number(val2) + "." + QString::number((getRand(0, 100) / 10)) + "  -- PASSED");
        }else{
            ui->report->setText("The reported ΔLt value is : " + QString::number(val2) + "." + QString::number((getRand(0, 100) / 10)) + "  -- FAILED");
        }
        ui->report->show();
        ui->screen->setDisabled(true);
    }
}
