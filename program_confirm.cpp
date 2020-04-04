#include "program_confirm.h"
#include "ui_program_confirm.h"

program_confirm::program_confirm(QWidget *parent):
    QDialog(parent),
    ui(new Ui::program_confirm)
{
    ui->setupUi(this);
}

program_confirm::~program_confirm()
{
    delete ui;
}

void program_confirm::on_pushButton_2_clicked() // Button for "no".
{
    emit valueChanged(0); // A slot listens for this signal. When "program" restarts it 
    close();
}

void program_confirm::on_yes_clicked()
{
    emit valueChanged(1); // A slot listens for this signal.
    close();
}

// Text displayed to user, dependent on which of the eight programs is selected.
void program_confirm::setText(int s) {
    if (s == 1) {
        ui->label->setText("Place the sensors on the \naffected area.\nAre the sensors properly attached?");
    } else if (s == 2) {
        ui->label->setText("Place the sensors near the area that \nis currently painful.\nAre the sensors properly attached?");
    } else if (s == 3) {
        ui->label->setText("Place the sensors near the throat \narea.\nAre the sensors properly attached?");
    } else if (s == 4) {
        ui->label->setText("Place the sensors on your head near \nthe area where it is painful.\nAre the sensors properly attached?");
    } else if (s == 5) {
        ui->label->setText("Place the sensors on your throat or \nnose depending on where \nthe pain is.\nAre the sensors properly attached?");
    } else if (s == 6) {
        ui->label->setText("Place the sensors on your chest area \njust below your neck.\nAre the sensors properly attached?");
    } else if (s == 7) {
        ui->label->setText("Place the sensors on the \ntraumatized area.\nAre the sensors properly attached?");
    } else if (s == 8) {
        ui->label->setText("Place the sensors on the \naffected joints.\n Are the sensors properly attached?");
    }
}
