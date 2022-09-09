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
//    setCentralWidget(m_player);
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
    m_player-> setGeometry(0,20,W,H);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_add_picture_triggered()
{
    m_player->addPicture();
    // 出现一个窗口，输入文字信息和位置

}


void MainWindow::on_add_subtitles_triggered()
{
    m_player->addSubtitles();
}


void MainWindow::on_add_text_triggered()
{
    m_player->addText();

}



void MainWindow::on_add_fadein_triggered()
{
    m_player->addFade(1);
}


void MainWindow::on_add_fadeout_triggered()
{
    m_player->addFade(0);
}


void MainWindow::on_add_zoomin_triggered()
{
    m_player->addZoom(1);
}


void MainWindow::on_add_zoomout_triggered()
{
    m_player->addZoom(0);
}


void MainWindow::on_add_moveright_triggered()
{
    m_player->addMove(1);
}


void MainWindow::on_addmoveleft_triggered()
{
    m_player->addMove(0);
}

