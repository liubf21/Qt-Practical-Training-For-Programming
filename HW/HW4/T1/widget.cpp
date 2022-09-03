#include "widget.h"
#include "ui_widget.h"
#include <QSignalMapper>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QSignalMapper *m = new QSignalMapper(this);
//    s = "0";
    connect(ui->pushButton, SIGNAL(clicked()),m, SLOT(map()));
    m->setMapping(ui->pushButton, 0);
    connect(ui->pushButton_1, SIGNAL(clicked()),m, SLOT(map()));
    m->setMapping(ui->pushButton_1, 1);
    connect(ui->pushButton_2, SIGNAL(clicked()),m, SLOT(map()));
    m->setMapping(ui->pushButton_2, 2);
    connect(ui->pushButton_3, SIGNAL(clicked()),m, SLOT(map()));
    m->setMapping(ui->pushButton_3, 3);
    connect(ui->pushButton_4, SIGNAL(clicked()),m, SLOT(map()));
    m->setMapping(ui->pushButton_4, 4);
    connect(ui->pushButton_5, SIGNAL(clicked()),m, SLOT(map()));
    m->setMapping(ui->pushButton_5, 5);
    connect(ui->pushButton_6, SIGNAL(clicked()),m, SLOT(map()));
    m->setMapping(ui->pushButton_6, 6);
    connect(ui->pushButton_7, SIGNAL(clicked()),m, SLOT(map()));
    m->setMapping(ui->pushButton_7, 7);
    connect(ui->pushButton_8, SIGNAL(clicked()),m, SLOT(map()));
    m->setMapping(ui->pushButton_8, 8);
    connect(ui->pushButton_9, SIGNAL(clicked()),m, SLOT(map()));
    m->setMapping(ui->pushButton_9, 9);
    connect(m, SIGNAL(mapped(int)), this, SLOT(keyPressed(int)));
    connect(ui->display,SIGNAL(clicked()),this,SLOT(showNum()));
    connect(ui->clear,SIGNAL(clicked()),this,SLOT(clearNum()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressed(int i){

    qDebug()<<i;
    s += QString::number(i); // 数字转字符串
    qDebug()<<endl<< s;

}

void Widget::showNum()
{
    ui->lineEdit->setText(s); // 将字符串显示
}

void Widget::clearNum()
{
    s.clear();
    ui->lineEdit->setText(s);
}
