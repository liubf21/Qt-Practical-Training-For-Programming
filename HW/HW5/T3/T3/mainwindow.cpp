#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for(int i=0;i<5;i++)
    {
        pic[i]=QImage(add+QString::number(i)+".png");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    painter = new QPainter(this);
    painter->drawImage(QRect(10, 50,780,520),pic[k]);

}

void MainWindow::on_pushButton_clicked()
{
    k++;
    if(k==5)k=0;
    update();
}

