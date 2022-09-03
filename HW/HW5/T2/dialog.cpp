#include "dialog.h"
#include "ui_dialog.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include <QRegExpValidator>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(10,10,10,80);
    QLineEdit *lineEdit[3];
    QString str[3]={tr("year"),tr("month"),tr("day")};
    QLabel *label;
    for(int i=0;i<3;i++)
    {
        label = new QLabel(str[i]);
        layout->addWidget(label);
        lineEdit[i]= new QLineEdit();
        layout->addWidget(lineEdit[i]);
    }
    lineEdit[1]->setValidator(new QRegExpValidator(QRegExp("(^1?[0-2])|[1-9]"),this));
    lineEdit[2]->setValidator(new QRegExpValidator(QRegExp("(3[0-1])|(^[1-2]?[0-9])|[1-9]"),this));

    if(this->exec()==QDialog::Accepted)
    {
        QString d[3];
        int x[3];
        for(int i=0;i<3;i++)
        {
            d[i]=lineEdit[i]->text();
            x[i]=d[i].toInt();
        }
        qDebug()<<d[0];
        if(check(x[0],x[1],x[2])){
        QMessageBox::information(this, "Date","The date you enter is "+d[0]+"/"+d[1]+"/"+d[2]);
        }else{
            QMessageBox::warning(this,"Warning","The data you enter is not legal");
        }
    }
}

bool Dialog::check(int y,int m,int d){
    if((m==4||m==6||m==9||m==11)&&d>30)
    {
        return false;
    }else if(m==2&&((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)&&d>29){
        return false;
    }else if(m==2&&d>28){
        return false;
    }else if(y<1||m<1||d<1){
        return false;}
    else{
        return true;
    }
}

Dialog::~Dialog()
{
    delete ui;
}
