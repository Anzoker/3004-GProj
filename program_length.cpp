#include "program_length.h"
#include "ui_program_length.h"

program_length::program_length(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::program_length)
{
    ui->setupUi(this);
    ui->t1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->t2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->t3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->t4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

program_length::~program_length()
{
    delete ui;
}

void program_length::on_t1_clicked()
{
    emit valueChanged(1);
    close();
}

void program_length::on_t2_clicked()
{
    emit valueChanged(10);
    close();
}

void program_length::on_t3_clicked()
{
    emit valueChanged(30);
    close();
}

void program_length::on_t4_clicked()
{
    emit valueChanged(60);
    close();
}
