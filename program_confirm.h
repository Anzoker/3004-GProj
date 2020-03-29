#ifndef PROGRAM_CONFIRM_H
#define PROGRAM_CONFIRM_H

#include <QDialog>

namespace Ui {
class program_confirm;
}

class program_confirm : public QDialog
{
    Q_OBJECT

public:
    explicit program_confirm(QWidget *parent = nullptr);
    void setText(int s);
    ~program_confirm();

private slots:
    void on_pushButton_2_clicked();
    void on_yes_clicked();

private:
    Ui::program_confirm *ui;

signals:
    void valueChanged(int newValue);
};

#endif // SCREENING_CONFIRM_H
