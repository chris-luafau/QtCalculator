#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

namespace Ui {
class Calculator;
}

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;

private slots:                      // this slots will be executed whenever a signal is submitted
    void NumPressed();
    void MathButtonPressed();
    void EqualButtonPressed();
    void ChangeSign();
    void Clear();
    void MemPlusPressed();
    void MemSubPressed();
    void DisplayMem();
};

#endif // CALCULATOR_H
