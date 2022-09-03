#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->lineEdit, &QLineEdit::returnPressed,this,&MainWindow::showString);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showString()
{
    s+=ui->lineEdit->text();
    s+="\n";
    ui->lineEdit->clear();
    ui->textEdit->setText(s);
}
