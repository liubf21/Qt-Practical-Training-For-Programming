#include "edittimeline.h"
#include <QMessageBox>

// 主时间轴，实现视频的添加，剪切，拼接，交换次序等
// 添加图片文字，并设置时间
// 外面用ScrollArea，里面用Slider和Button
// player->setMedia(QUrl::fromLocalFile("./Music/test.mp3"));
EditTimeLine::EditTimeLine(QWidget *parent)
    : QWidget{parent}
{
    m_removeButton = new QPushButton(this);
    m_removeButton->setEnabled(false);
    m_removeButton->setIcon(QIcon(":/res/remove.png"));
    m_removeButton->setGeometry(0,10,40,40);
    connect(m_removeButton, &QAbstractButton::clicked,
            this, &EditTimeLine::remove);

    m_mergeButton = new QPushButton(this);
    m_mergeButton->setEnabled(false);
    m_mergeButton->setIcon(QIcon(":/res/merge.png"));
    m_mergeButton->setGeometry(0,60,40,40);
    connect(m_mergeButton, &QAbstractButton::clicked,
            this, &EditTimeLine::merge);

    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setGeometry(40,10,100,100);
    m_scrollArea->setBackgroundRole(QPalette::Shadow);
    //scrollArea->setWidgetResizable(true);   //小部件适应QScrollArea自动改变大小
    //scrollArea->setAlignment(Qt::AlignCenter);    //居中对齐
    //添加滚动条
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);//设置垂直滚动条，属性设置为当在需要的时候显示
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);//设置水平滚动条，属性设置为当需要的时候显示
     //注意要点在设置滚动条的时候碰到一个小bug，就是在你要设置滚动条的时候要留出一点位置给水平滚动条，不然无法显示
    m_widget = new QWidget;
    m_scrollArea->setWidget(m_widget);
//    m_widget->setFixedSize(1500,600);

    m_EditSlider = new QSlider(Qt::Horizontal,m_widget); // 水平方向
//    m_scrollArea->setWidget(m_EditSlider);
//    m_EditSlider->setFixedSize(600,50);
    m_EditSlider->setRange(0,200); // 300s
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

    m_signalMapper = new QSignalMapper(this);
    connect(m_signalMapper, SIGNAL(mapped(int)), this, SIGNAL(playClips(int)));




//    QBoxLayout *leftlayout = new QVBoxLayout;
//    leftlayout->addWidget(m_removeButton);
//    leftlayout->addWidget(m_mergeButton);
//    leftlayout->addStretch();
//    QBoxLayout *layout = new QHBoxLayout;
//    layout->addLayout(leftlayout);
//    layout->addStretch(3);
//    layout->addWidget(m_scrollArea,2);
//    setLayout(layout());
}

void EditTimeLine::resizeEvent(QResizeEvent* Size) // 保证缩放后控件成比例
{
//    QWidget::resizeEvent(Size);
    int width = 5;
    for(auto x:m_clipButtons)
    {
        int n_width=x->width()*this->width()/m_EditSlider->width();
        x->setGeometry(width,40,n_width,30);
        width+=n_width;
    }
    m_EditSlider->setFixedSize(this->width(),50);
    m_scrollArea->setFixedSize(this->width()-50,this->height());
    m_widget->setFixedSize(this->width()+100,this->height());

}

void EditTimeLine::add(QUrl url,qint64 duration)    // 传入视频链接和时长
{
    m_clips.append(url);
    m_clipsDuration.append(duration);
    QString name=QFileInfo(url.path()).fileName();
//    m_scrollArea->setWidget(m_clipButtons.last());
    int width=5;
    for(auto x:m_clipButtons)
    {
        width+=x->width();
    }
    m_clipButtons.append(new QPushButton(m_widget));
    m_clipButtons.last()->setGeometry(width,40,duration*this->width()/200,30); // button的长度要与刻度对应
    m_clipButtons.last()->setAutoFillBackground(true);
    m_clipButtons.last()->setPalette(Qt::white);
    m_clipButtons.last()->setText(name);
    m_clipButtons.last()->setCheckable(true); // 设置为可选中
    m_clipButtons.last()->setAutoExclusive(true); // 设置排他性
    m_clipButtons.last()->show();

    connect(m_clipButtons.last(), SIGNAL(clicked()),m_signalMapper, SLOT(map()));
    qDebug()<<m_clipButtons.size();
    m_signalMapper->setMapping(m_clipButtons.last(), m_clipButtons.size()); // 注意此处，编号0则映射为1
    m_removeButton->setEnabled(true);
    m_mergeButton->setEnabled(true);

//    按键显示文件名，点击播放该片段(返回一个signal,由player接收，播放相应的url)，可往后叠加
//    能够前移和后移
}

QUrl EditTimeLine::returnUrl(int i)
{
    return m_clips[i-1];
}

void EditTimeLine::clip()
{

}

void EditTimeLine::merge()
{
    QString program = "D:\\program\\ffmpeg-2022-08-25-git-9bf9d42d01-essentials_build\\bin\\ffmpeg.exe";
    QFile file("filelist.txt");
    file.open( QIODevice::WriteOnly | QIODevice::Text ); // 新建文件,或直接覆盖已有文件
    QTextStream in(&file);
    QString inputPath="concat:";
    for(auto x:m_clips)
    {
        inputPath+=x.toLocalFile();
        if(x!=m_clips.last())
            inputPath+="|";
        in<<"file "<<"'"<<x.toLocalFile()<<"'\n";
    }
    QFile sourceFile(m_clips[0].toLocalFile());
    int temp=1;
    QString outputPath = QFileInfo(sourceFile).absolutePath() +"/clip_"+QString::number(temp)+".mp4";
    while(QFile::exists(outputPath))
    {
        ++temp;
        outputPath = QFileInfo(sourceFile).absolutePath() +"/clip_"+QString::number(temp)+".mp4";
    }
//    qDebug()<<"input:"<<inputPath<<"output:"<<outputPath;
    QStringList arguments;
//    arguments << "-i" << inputPath << "-c copy" << "-y"<< outputPath;
    arguments <<"-f"<<"concat"<<"-safe"<<"0"<<"-i"<<"filelist.txt"
             <<"-c"<<"copy"<<"-y"<<outputPath;
//    qDebug()<<arguments;
    QProcess *clipProcess = new QProcess(this);
    connect(clipProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        [=](int exitCode, QProcess::ExitStatus exitStatus){
        if(exitCode){
            QMessageBox::information(this,"提示","视频处理失败！");
        }else{
            QMessageBox::information(this,"提示","视频处理已完成！");
        }});
    clipProcess->start(program, arguments);
    file.close();
    m_clips.clear();
    for(auto x:m_clipButtons)
        x->deleteLater();
    m_clipButtons.clear();
    m_clipsDuration.clear();
    emit addUrl(QUrl::fromLocalFile(outputPath));

//    QList<QUrl> url_list;
//    url_list.append(QUrl::fromLocalFile(outputPath));
//    addToPlaylist(url_list);
}

void EditTimeLine::remove(int i)
{
    for(int i=0;i<m_clips.count();i++){
        if(m_clipButtons[i]->isChecked()){
            qDebug()<<"remove"<<i;
            disconnect(m_clipButtons[i], SIGNAL(clicked()),m_signalMapper, SLOT(map()));
            m_clipButtons[i]->deleteLater();
            m_clipButtons.removeAt(i);
            m_clips.removeAt(i);
            m_clipsDuration.removeAt(i);
            // 需要把后面部件的重新绑定
            qDebug()<<m_clips.count();
            for(int j=i;j<m_clips.count();j++)
            {   qDebug()<<"num"<<j<<m_clips[j];
                m_signalMapper->removeMappings(m_clipButtons[j]);
                m_signalMapper->setMapping(m_clipButtons[j], j+1);}
            // 重新排布
            int width = 5;
            for(auto x:m_clipButtons)
            {
                int n_width=x->width()*this->width()/m_EditSlider->width();
                x->setGeometry(width,40,n_width,30);
                width+=n_width;
            }
            return;
        }
    }
}
