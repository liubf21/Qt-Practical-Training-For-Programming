#include "player.h"
#include "playlistmodel.h"
#include "markslider.h"
#include "edittimeline.h"

VideoPlayer::VideoPlayer(QWidget *parent)
    : QWidget(parent)
{
    QPalette p = palette();
    p.setColor(QPalette::WindowText, Qt::white);
    setPalette(p);

//    播放器设置
    m_mediaPlayer = new QMediaPlayer(this, QMediaPlayer::VideoSurface);
    m_videoWidget = new QVideoWidget(this);
    m_mediaPlayer->setVideoOutput(m_videoWidget);

    connect(m_mediaPlayer, &QMediaPlayer::stateChanged,
            this, &VideoPlayer::mediaStateChanged);
    connect(m_mediaPlayer, &QMediaPlayer::positionChanged, this, &VideoPlayer::positionChanged);
    connect(m_mediaPlayer, &QMediaPlayer::durationChanged, this, &VideoPlayer::durationChanged);
    connect(m_mediaPlayer, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error),
            this, &VideoPlayer::handleError);

//    设置播放列表
    m_playlist = new QMediaPlaylist();
    m_mediaPlayer->setPlaylist(m_playlist);
    m_playlistModel = new PlaylistModel(this);
    m_playlistModel->setPlaylist(m_playlist);

    m_playlistView = new QListView(this);
    m_playlistView->setModel(m_playlistModel); // 设置模型
    m_playlistView->setCurrentIndex(m_playlistModel->index(m_playlist->currentIndex(), 0));
//    m_playlistView->setEnabled(false);

    m_playlistView->setContextMenuPolicy(Qt::CustomContextMenu); // 右键菜单
    connect(m_playlistView, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(show_contextmenu1(const QPoint&)));

    connect(m_playlist, &QMediaPlaylist::currentIndexChanged, this, &VideoPlayer::playlistPositionChanged);
    connect(m_playlistView, &QAbstractItemView::activated, this, &VideoPlayer::jump);

//    打开文件
    QAbstractButton *openButton = new QPushButton(tr("Open..."));
    connect(openButton, &QAbstractButton::clicked, this, &VideoPlayer::openFile);
    openButton->setAutoFillBackground(true);
    openButton->setPalette(p);

//    设置播放按钮
    m_playButton = new QPushButton;
    m_playButton->setEnabled(false);
    m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
//    m_playButton->setAutoFillBackground(true);
//    m_playButton->setPalette(p);

    connect(m_playButton, &QAbstractButton::clicked,
            this, &VideoPlayer::play);

//    设置剪辑按钮
    m_cutButton = new QPushButton;
    m_cutButton->setEnabled(false);
    m_cutButton->setIcon(QIcon(":/res/cut.png"));
//    m_cutButton->setIconSize(QSize(20,20));
//    m_cutButton->setAutoFillBackground(true);
//    m_cutButton->setPalette(p);
    connect(m_cutButton, &QAbstractButton::clicked,
            this, &VideoPlayer::startCut);


//    设置剪辑停止按钮
    m_stopButton = new QPushButton;
    m_stopButton->setEnabled(false);
    m_stopButton->setIcon(QIcon(":/res/stop.png"));
    connect(m_stopButton, &QAbstractButton::clicked,
            this, &VideoPlayer::cutOperation);

//    设置加入主时间轴按钮
    m_joinButton = new QPushButton;
    m_joinButton->setEnabled(false);
    m_joinButton->setIcon(QIcon(":/res/join.png"));
    connect(m_joinButton, &QAbstractButton::clicked,
            this, &VideoPlayer::joinEdit);

//    剪辑时间
//    StartTimeEdit = new QTimeEdit;
//    StartTimeEdit->setDisplayFormat("HH:mm:ss");
//    EndTimeEdit = new QTimeEdit;
//    EndTimeEdit->setDisplayFormat("HH:mm:ss");

//    播放时拖动的时间条
    m_positionSlider = new MarkSlider(Qt::Horizontal,this);
    m_positionSlider->setRange(0, m_mediaPlayer->duration() / 1000);
    m_positionSlider->setValue(50);
    connect(m_positionSlider, &QAbstractSlider::sliderMoved,
            this, &VideoPlayer::setPosition);
//    显示播放时间
    m_labelDuration = new QLabel(this);
    m_labelDuration->setPalette(p);

    m_errorLabel = new QLabel(this);
    m_errorLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

//    主时间轴
    m_editTimeLine = new EditTimeLine(this);
    m_editTimeLine->show();
//    QSlider * m_EditSlider = new QSlider(Qt::Horizontal,this);
//    m_EditSlider->setRange(0,1000);
//    m_EditSlider->setValue(100);
//    m_EditSlider->show();
//    m_editTimeLine->setFixedSize(1000,50);

//    布局

    QBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(m_positionSlider);
//    hLayout->addWidget(m_labelDuration);
    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setContentsMargins(0, 0, 0, 0);
    controlLayout->addWidget(openButton);
    controlLayout->addStretch(1);
//    controlLayout->addWidget(StartTimeEdit);
    controlLayout->addWidget(m_labelDuration);
    controlLayout->addWidget(m_playButton);
    controlLayout->addWidget(m_cutButton);
    controlLayout->addWidget(m_stopButton);
    controlLayout->addWidget(m_joinButton);
    QBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_videoWidget,2);
    layout->addLayout(hLayout);
    layout->addLayout(controlLayout);
    layout->addWidget(m_errorLabel);

    QBoxLayout *Blayout = new QHBoxLayout;
    Blayout->addWidget(m_playlistView,1);
    Blayout->addLayout(layout,2);

    QBoxLayout *Wholelayout = new QVBoxLayout;
    Wholelayout->addLayout(Blayout,3);
//    Wholelayout->addWidget(m_EditSlider,1);
//    m_editTimeLine->setFixedSize(this->size()*1/4);
    Wholelayout->addWidget(m_editTimeLine,1);
//    Wholelayout->addWidget(new QPushButton());
//    setLayout(layout);
    setLayout(Wholelayout);
}

VideoPlayer::~VideoPlayer()
{
}

void VideoPlayer::openFile()
{
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setWindowTitle(tr("Open Movie"));
    QStringList supportedMimeTypes = m_mediaPlayer->supportedMimeTypes();
    if (!supportedMimeTypes.isEmpty())
        fileDialog.setMimeTypeFilters(supportedMimeTypes);
    fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).value(0, QDir::homePath()));
    if (fileDialog.exec() == QDialog::Accepted)
        addToPlaylist(fileDialog.selectedUrls()); // 添加选中文件的路径
//        setUrl(fileDialog.selectedUrls().constFirst());
}

// 单文件播放时使用
void VideoPlayer::setUrl(const QUrl &url)
{
    m_errorLabel->setText(QString());
    setWindowFilePath(url.isLocalFile() ? url.toLocalFile() : QString());
    m_mediaPlayer->setMedia(url);
    m_playButton->setEnabled(true);
}

static bool isPlaylist(const QUrl &url) // Check for ".m3u" playlists.
{
    if (!url.isLocalFile())
        return false;
    const QFileInfo fileInfo(url.toLocalFile());
//    qDebug()<<url.toLocalFile();
//    是否满足 存在且后缀为m3u ；compare比较字符串大小，相等才返回0
    return(fileInfo.exists() && !fileInfo.suffix().compare(QLatin1String("m3u"), Qt::CaseInsensitive));
}

void VideoPlayer::addToPlaylist(const QList<QUrl> &urls)
{
    for (auto &url: urls) {
//        qDebug()<<m_urls.count(url);
        if (isPlaylist(url)) // 判断是否是播放列表
        {m_playlist->load(url);;}
        else if(!m_urls.count(url)) // 避免重复加入
        {m_playlist->addMedia(url);
        m_urls.append(url);}
    }
    m_playButton->setEnabled(true);
    m_cutButton->setEnabled(true);
    m_joinButton->setEnabled(true);
}

// 右键菜单进行文件的重命名和删除
void VideoPlayer::show_contextmenu1(const QPoint& pos)
{
//     if(cmenu)//保证同时只存在一个menu，及时释放内存
//     {
//     delete cmenu;
//     cmenu = NULL;
//     }
    //点击空白处将不会出现菜单
    if(!((m_playlistView->selectionModel()->selectedIndexes()).empty()))
    {

        qDebug()<<"show_contextmenu1";
        QMenu *cmenu = new QMenu(m_playlistView);
        QAction *RenameAction = cmenu->addAction(QString::fromLocal8Bit("重命名"));
        QAction *DeleteAction = cmenu->addAction(QString::fromLocal8Bit("删除"));
        connect(RenameAction, SIGNAL(triggered(bool)), this, SLOT(menu_Rename()));
        connect(DeleteAction, SIGNAL(triggered(bool)), this, SLOT(menu_Delete()));
        cmenu->exec(QCursor::pos());//在当前鼠标位置显示
        //cmenu->exec(pos)是在viewport显示
//        qDebug()<<m_playlistView->selectionModel()->currentIndex().row(); // 通过currentIndex进行重命名和删除
        //把选中的清除
        m_playlistView->selectionModel()->clear();
    }
}
void VideoPlayer::menu_Rename()
{
    bool ok; // 接受对话框的返回值
    QString text = QInputDialog::getText(this, tr("Rename"),
                                         tr("New filename:"), QLineEdit::Normal/*QLineEdit::Password*/,
                                         "temp", &ok);
    if (ok && !text.isEmpty())
        QMessageBox::information(NULL,"notice",text);
    QUrl location = m_playlist->media(m_playlistView->selectionModel()->currentIndex().row()).request().url();
    m_playlist->removeMedia(m_playlistView->selectionModel()->currentIndex().row());
    m_urls.removeAll(location);
    QFile file(location.toLocalFile());
    QFileInfo fileInfo(location.toLocalFile());
    QString filePath = fileInfo.absolutePath()+"/"+text+"."+fileInfo.suffix();
//    qDebug()<<filePath;
    if(! file.rename(filePath)) // 若此处使用相对路径，会导致文件不在原来的位置
    {
        qDebug() << "rename error:" << file.errorString();
    }
    QList<QUrl> url_list;
    url_list.append(QUrl::fromLocalFile(filePath));
    addToPlaylist(url_list);
}
void VideoPlayer::menu_Delete()
{
    // 操作文件时主要\ 和 / 的差异
//    qDebug()<<m_playlistView->selectionModel()->currentIndex().row();
    QUrl location = m_playlist->media(m_playlistView->selectionModel()->currentIndex().row()).request().url();
    m_playlist->removeMedia(m_playlistView->selectionModel()->currentIndex().row());
    m_urls.removeAll(location);
//    qDebug()<<location.toLocalFile();
//    qDebug()<<location.path();
//    QFile::setPermissions(location.path(),QFile::ReadOther | QFile::WriteOther);
    QFile file(location.toLocalFile());
    file.close();
    if(! file.remove())
    {
        qDebug() << "remove error:" << file.errorString();
    }

}


void VideoPlayer::play()
{
    switch (m_mediaPlayer->state()) {
    case QMediaPlayer::PlayingState:
        m_mediaPlayer->pause();
        break;
    default:
        m_mediaPlayer->play();
        break;
    }
    qDebug()<<m_playlist->currentMedia().request().url().toLocalFile();
//    获取当前播放视频的地址，以下两种为被弃用的方式
//    qDebug()<<m_playlist->currentMedia().canonicalUrl().toString();
//    qDebug()<<m_mediaPlayer->media().resources().first().url().path();
}

// 跳转视频
void VideoPlayer::jump(const QModelIndex &index)
{
    if (index.isValid()) {
        m_playlist->setCurrentIndex(index.row());
        m_mediaPlayer->play();
    }
    m_playButton->setEnabled(true);
}

void VideoPlayer::playlistPositionChanged(int currentItem)
{
    m_playlistView->setCurrentIndex(m_playlistModel->index(currentItem, 0));
}

void VideoPlayer::mediaStateChanged(QMediaPlayer::State state)
{
    switch(state) {
    case QMediaPlayer::PlayingState:
        m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        break;
    default:
        m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        break;
    }
}

void VideoPlayer::positionChanged(qint64 position)
{
//    positionChanged是播放器持续时间的更改（播放器当前时间变化时触发）
//    position是毫秒
    if (!m_positionSlider->isSliderDown()) // 使滑块从按下到松开的过程才能触发信号
        m_positionSlider->setValue(position/1000);
    updateDurationInfo(position / 1000);

}

void VideoPlayer::durationChanged(qint64 duration)
{
//    durationChanged是播放器总时间的更改（时长发生变化时触发）
    m_duration = duration / 1000;
    m_positionSlider->setRange(0, m_duration);
}

void VideoPlayer::setPosition(int position)
{
    // 设置视频位置 ！注意时间
    m_mediaPlayer->setPosition(position*1000);
}

void VideoPlayer::handleError()
{
    // 处理错误
    m_playButton->setEnabled(false);
    const QString errorString = m_mediaPlayer->errorString();
    QString message = "Error: ";
    if (errorString.isEmpty())
        message += " #" + QString::number(int(m_mediaPlayer->error()));
    else
        message += errorString;
    m_errorLabel->setText(message);
}

void VideoPlayer::updateDurationInfo(qint64 currentInfo)
{
    // 更新播放时间
    QString tStr;
    if (currentInfo || m_duration) {
        currentTime=QTime((currentInfo / 3600) % 60, (currentInfo / 60) % 60,
            currentInfo % 60, (currentInfo * 1000) % 1000);
        QTime totalTime((m_duration / 3600) % 60, (m_duration / 60) % 60,
            m_duration % 60, (m_duration * 1000) % 1000);
        QString format = "mm:ss";
        if (m_duration > 3600)
            format = "hh:mm:ss";
        tStr = currentTime.toString(format) + " / " + totalTime.toString(format);
    }
    //记录（传递）时间，用于在剪辑开始和结束的设置
    m_labelDuration->setText(tStr);
}

//    调用FFmpeg进行视频剪辑操作，需要的参数有输入文件地址，开始时间，结束时间（由两个按钮记录），输出文件地址
//    把输出文件加入视频列表

void VideoPlayer::startCut()
{
    qDebug()<<"!!!";
//    m_positionSlider->setTickPosition(m_positionSlider->tickPosition());
    m_positionSlider->VerifyDefaultValue(m_positionSlider->sliderPosition());
//    StartTimeEdit->setTime(currentTime);
    cutTime=currentTime;
    m_stopButton->setEnabled(true);
}

void VideoPlayer::cutOperation()
{
    QString program = "D:\\program\\ffmpeg-2022-08-25-git-9bf9d42d01-essentials_build\\bin\\ffmpeg.exe";
//    得到当前播放视频的文件位置的QUrl，再转为字符串
    QString inputPath = m_playlist->currentMedia().request().url().toLocalFile();
    QFile sourceFile(inputPath);
    if(!sourceFile.exists()){
        QMessageBox::information(this,QString::fromUtf8("提示"),QString::fromUtf8("找不到源文件"));
        return;
    }
    int temp=1;
    QString outputPath = QFileInfo(sourceFile).absolutePath() +"/clip_"+QString::number(temp)+".mp4";
    while(QFile::exists(outputPath))
    {
        ++temp;
        outputPath = QFileInfo(sourceFile).absolutePath() +"/clip_"+QString::number(temp)+".mp4";
    }
    QFile destFile(outputPath);
    if(cutTime>currentTime)
    {
        QMessageBox::warning(this,"Warning",QString::fromLocal8Bit("剪辑失败!"));
        return;
    }
    QString startTime = cutTime.toString("hh:mm:ss");
//    QString endTime= EndTimeEdit->time().toString("hh:mm:ss");
    QString endTime= currentTime.toString("hh:mm:ss");
    QStringList arguments;
    arguments << "-i" << inputPath << "-r" << "25"<<"-ss";
    arguments <<startTime<< "-to" << endTime << outputPath;

    QProcess *clipProcess = new QProcess(this);
//    connect(clipProcess,SIGNAL(finished(int)),this,SLOT(clipVideoFinished(int)));

    clipProcess->start(program, arguments);
    QList<QUrl> url_list;
    url_list.append(QUrl::fromLocalFile(outputPath));
    addToPlaylist(url_list);

}

//    将选中视频加入主时间轴
void VideoPlayer::joinEdit()
{
    m_editTimeLine->add(m_playlist->currentMedia().request().url(),m_duration);
}
