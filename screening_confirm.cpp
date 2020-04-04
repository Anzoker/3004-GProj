#include "screening_confirm.h"
#include "ui_screening_confirm.h"

screening_confirm::screening_confirm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::screening_confirm)

{ ui->setupUi(this); }

screening_confirm::~screening_confirm() { delete ui; }

// Button for "no".
void screening_confirm::on_pushButton_2_clicked() {
    emit valueChanged(0);
    close();
}

void screening_confirm::on_yes_clicked() {
    emit valueChanged(1);
    close();
}
