#include "edittimeline.h"
#include <QPushButton>

// 主时间轴，实现视频的添加，剪切，拼接，交换次序等
// 添加图片文字，并设置时间
// 外面用ScrollArea，里面用Slider和Button
// player->setMedia(QUrl::fromLocalFile("./Music/test.mp3"));
EditTimeLine::EditTimeLine(QWidget *parent)
    : QWidget{parent}
{
    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setBackgroundRole(QPalette::Shadow);
    //scrollArea->setWidgetResizable(true);   //小部件适应QScrollArea自动改变大小
    //scrollArea->setAlignment(Qt::AlignCenter);    //居中对齐
    //添加滚动条
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);//设置垂直滚动条，属性设置为当在需要的时候显示
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);//设置水平滚动条，属性设置为当需要的时候显示
     //注意要点在设置滚动条的时候碰到一个小bug，就是在你要设置滚动条的时候要留出一点位置给水平滚动条，不然无法显示
    m_widget = new QWidget;
    m_scrollArea->setWidget(m_widget);
    m_widget->setFixedSize(1000,600);

    m_EditSlider = new QSlider(Qt::Horizontal,m_widget); // 水平方向
//    m_scrollArea->setWidget(m_EditSlider);
    m_EditSlider->setFixedSize(600,50);
    m_EditSlider->setRange(0,1000);
//    m_EditSlider->setTickPosition(QSlider::TicksBothSides);
//    pSlider->setMinimum(nMin);  // 最小值
//    pSlider->setMaximum(nMax);  // 最大值
//    QPalette p = palette();
//    p.setColor(QPalette::Button, Qt::white);
//    m_EditSlider->setPalette(p);
//    m_EditSlider->setStyleSheet("color:light");
//    m_EditSlider->setAutoFillBackground(true);
//    m_EditSlider->setPalette(Qt::white);
//    m_EditSlider->setCo
    m_EditSlider->setSingleStep(10); // 步长
    // pSlider->setTickInterval(40);  // 设置刻度间隔
    m_EditSlider->setTickPosition(QSlider::TicksAbove);  //刻度在上方

    m_EditSlider->setValue(100);
    m_EditSlider->show();

//    m_positionSlider->setRange(0, m_mediaPlayer->duration() / 1000);
//    m_positionSlider->setValue(50);
//    connect(m_positionSlider, &QAbstractSlider::sliderMoved,
//            this, &VideoPlayer::setPosition);
}

void EditTimeLine::resizeEvent(QResizeEvent* Size)
{
    m_EditSlider->setFixedSize(this->width()+100,50);
    m_scrollArea->setFixedSize(this->width(),this->height());
}

void EditTimeLine::add(QUrl url,qint64 duration)
{
    m_clips.append(url);
    m_clipButtons.append(new QPushButton(m_widget));
//    m_scrollArea->setWidget(m_clipButtons.last());
//    m_clipButtons.last()->setGeometry(100,100,30,50);
}
void EditTimeLine::clip()
{

}
