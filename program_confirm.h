#ifndef PROGRAM_CONFIRM_H
#define PROGRAM_CONFIRM_H

#include <QDialog>

namespace Ui {
class Program_Confirm;
}

class Program_Confirm : public QDialog
{
    Q_OBJECT

public:
    explicit Program_Confirm(QWidget *parent = nullptr);
    ~Program_Confirm();
    void setText(int s); // Displays text to user after a program is selected.

private slots:
    void on_pushButton_2_clicked(); // Button for "no".
    void on_yes_clicked();

private:
    Ui::Program_Confirm *ui;

signals:
    void valueChanged(int newValue); // "Program" checks for the value emitted by this signal.
};

#endif // PROGRAM_CONFIRM_H
