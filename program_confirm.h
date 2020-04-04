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
    ~program_confirm();
    void setText(int s); // Displays text to user after a program is selected.

private slots:
    void on_pushButton_2_clicked(); // Button for "no".
    void on_yes_clicked();

private:
    Ui::program_confirm *ui;

signals:
    void valueChanged(int newValue); // "Program" checks for the value emitted by this signal.
};

#endif // PROGRAM_CONFIRM_H
