#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include <QtCore/QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_player = new VideoPlayer(this);

//    const QRect availableGeometry = QApplication::desktop()->availableGeometry(&m_player);
//    int H=this->height(),W=this->width();
//    m_player-> setGeometry(W/3,20,W/3*2,H/3*2);
    m_player -> show();
//    connect(this,&MainWindow::)
}
void MainWindow::resizeEvent(QResizeEvent* Size)
{
//    m_player->resize(size()); //是采用size()还是frameGeometry.size()根据自己的需求。
    int H=this->height(),W=this->width();
    m_player-> setGeometry(0,20,W,H/3*2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

