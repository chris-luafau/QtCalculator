#include "calculator.h"
#include "ui_calculator.h"

double calc_val = 0.0;
double mem_val = 0.0;
bool div_trigger = false;           // Keeping track of the last operation
bool mult_trigger = false;
bool add_trigger = false;
bool sub_trigger = false;

Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->Display->setText("0.0");                        // Setting the text for the Display widget.
    QPushButton *num_buttons[10];                       // An array that will hold all our digit buttons
    for (int i = 0; i < 10; ++i) {
        QString button_name = "Button" + QString::number(i);                    // Formatting this way since that is how we named the buttons in the ui.
        num_buttons[i] = Calculator::findChild<QPushButton *>(button_name);     // Searches Calculator for the button with name (button_name).
        connect(num_buttons[i], SIGNAL(released()), this, SLOT(NumPressed()));  // Connects each button the the NumPressed function we created.
    }
    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButtonPressed()));
    connect(ui->Clear, SIGNAL(released()), this, SLOT(Clear()));
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeSign()));
    connect(ui->MemAdd, SIGNAL(released()), this, SLOT(MemPlusPressed()));
    connect(ui->MemClear, SIGNAL(released()), this, SLOT(MemSubPressed()));
    connect(ui->MemGet, SIGNAL(released()), this, SLOT(DisplayMem()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed() {
    QPushButton *button = static_cast<QPushButton *>(sender());                     // sender() returns a pointer to the button that was pressed.
    QString button_value = button->text();                                          // Obtain value of button that was pressed.
    QString display_value = ui->Display->text();                                    // Obtain current value in the Display widget.
    if ((display_value.toDouble() == 0) || (display_value.toDouble() == 0.0)) {     // Change 0 to user input
        ui->Display->setText(button_value);
    } else {                                                                        // Concatenate new input with old input
        QString new_value = display_value + button_value;
        double dbl_new_value = new_value.toDouble();
        ui->Display->setText(QString::number(dbl_new_value, 'g', 16));              // After 16 digits, we want to start using exponents.
    }
}

void Calculator::MathButtonPressed() {
    QPushButton *button = static_cast<QPushButton *>(sender());
    QString display_value = ui->Display->text();                                    // Obtain value of Display widget as a QString
    calc_val = display_value.toDouble();                                            // Convert QString to a double
    QString button_value = button->text();
    div_trigger = false;                                                       // Resetting the flags every time the function is called
    mult_trigger = false;
    add_trigger = false;
    sub_trigger = false;
    if (QString::compare(button_value, "/", Qt::CaseInsensitive) == 0) {
        div_trigger = true;
    } else if (QString::compare(button_value, "*", Qt::CaseInsensitive) == 0){
        mult_trigger = true;
    } else if (QString::compare(button_value, "+", Qt::CaseInsensitive) == 0) {
        add_trigger = true;
    } else {
        sub_trigger = true;
    }
    ui->Display->setText("");                   // Reset the display
}

void Calculator::EqualButtonPressed() {
    double solution = 0.0;
    QString display_value = ui->Display->text();
    double display_val = display_value.toDouble();
    if (add_trigger || sub_trigger || mult_trigger || div_trigger) {                // Check to make sure a math button was pressed
        if (add_trigger) {
            solution = calc_val + display_val;
        } else if (sub_trigger) {
            solution = calc_val - display_val;
        } else if (mult_trigger) {
            solution = calc_val * display_val;
        } else {
            solution = calc_val / display_val;
        }
    }
    ui->Display->setText(QString::number(solution));
}

void Calculator::ChangeSign() {
    QString display_value = ui->Display->text();
    QRegExp reg("[-]?[0-9.]*");
    if (reg.exactMatch(display_value)) {
        double display_val = display_value.toDouble();
        double display_val_sign = -1 * display_val;
        ui->Display->setText(QString::number(display_val_sign));
    }
}

void Calculator::Clear() {
    ui->Display->setText("0.0");
    calc_val = 0.0;
    div_trigger = false;
    mult_trigger = false;
    add_trigger = false;
    sub_trigger = false;
}

void Calculator::MemPlusPressed() {
    QString display_value = ui->Display->text();
    mem_val += display_value.toDouble();
}

void Calculator::MemSubPressed() {
    QString display_value = ui->Display->text();
    mem_val -= display_value.toDouble();
}

void Calculator::DisplayMem() {
    ui->Display->setText(QString::number(mem_val));
}
