#ifndef SCREENING_CONFIRM_H
#define SCREENING_CONFIRM_H

#include <QDialog>

namespace Ui {
class screening_confirm;
}

class screening_confirm : public QDialog
{
    Q_OBJECT

public:
    explicit screening_confirm(QWidget *parent = nullptr);
    ~screening_confirm();

private slots:
    void on_pushButton_2_clicked();

    void on_yes_clicked();

private:
    Ui::screening_confirm *ui;

signals:
    void valueChanged(int newValue);
};

#endif // SCREENING_CONFIRM_H
