#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->celsiusLcd->setDigitCount(4);
    ui->fahrenheitLcd->setDigitCount(4);
    tempconverter=new TempConverter(10);
    connect(ui->celsiusDial, SIGNAL(valueChanged(int)), tempconverter, SLOT(setTempCelsius(int)));
    connect(ui->celsiusDial, SIGNAL(valueChanged(int)), ui->celsiusLcd, SLOT(display(int)));
    connect(tempconverter, SIGNAL(tempCelsiusChanged(int)), ui->celsiusDial, SLOT(setValue(int)));
    connect(ui->fahrenheitDial, SIGNAL(valueChanged(int)), tempconverter, SLOT(setTempFahrenheit(int)));
    connect(ui->fahrenheitDial, SIGNAL(valueChanged(int)), ui->fahrenheitLcd, SLOT(display(int)));
    connect(tempconverter, SIGNAL(tempFahrenheitChanged(int)), ui->fahrenheitDial, SLOT(setValue(int)));
}

Dialog::~Dialog()
{
    delete ui;
}

