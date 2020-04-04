#ifndef PROGRAM_LENGTH_H
#define PROGRAM_LENGTH_H

#include <QDialog>

namespace Ui { class program_length; }

class program_length : public QDialog
{
    Q_OBJECT

public:
    explicit program_length(QWidget *parent = nullptr);
    ~program_length();

private:
    Ui::program_length *ui;

signals:
    void valueChanged(int newValue);

// Buttons for choosing the duration of the program (1, 10, 30, or 60 minutes).
private slots:
    void on_t1_clicked();
    void on_t2_clicked();
    void on_t3_clicked();
    void on_t4_clicked();
};

#endif // PROGRAM_LENGTH_H
