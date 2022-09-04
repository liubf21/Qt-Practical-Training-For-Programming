#include "player.h"

#include "playlistmodel.h"
#include "markslider.h"


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
    m_playlistView->setModel(m_playlistModel);
    m_playlistView->setCurrentIndex(m_playlistModel->index(m_playlist->currentIndex(), 0));
//    m_playlistView->setEnabled(false);

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

//    剪辑时间
    StartTimeEdit = new QTimeEdit;
    StartTimeEdit->setDisplayFormat("HH:mm:ss");
    EndTimeEdit = new QTimeEdit;
    EndTimeEdit->setDisplayFormat("HH:mm:ss");

    connect(m_stopButton, &QAbstractButton::clicked,
            this, &VideoPlayer::cutOperation);

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

//    布局

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(m_positionSlider);
    hLayout->addWidget(m_labelDuration);
    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setContentsMargins(0, 0, 0, 0);
    controlLayout->addWidget(openButton);
    controlLayout->addStretch(1);
    controlLayout->addWidget(StartTimeEdit);
    controlLayout->addWidget(EndTimeEdit);
    controlLayout->addWidget(m_playButton);
    controlLayout->addWidget(m_cutButton);
    controlLayout->addWidget(m_stopButton);
    QBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_videoWidget,2);
    layout->addLayout(hLayout);
    layout->addLayout(controlLayout);
    layout->addWidget(m_errorLabel);

    QBoxLayout *Blayout = new QHBoxLayout;
    Blayout->addWidget(m_playlistView,1);
    Blayout->addLayout(layout,2);

//    setLayout(layout);
    setLayout(Blayout);
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
    return fileInfo.exists() && !fileInfo.suffix().compare(QLatin1String("m3u"), Qt::CaseInsensitive);
}

void VideoPlayer::addToPlaylist(const QList<QUrl> &urls)
{
    for (auto &url: urls) {
        if (isPlaylist(url))
            m_playlist->load(url);
        else
            m_playlist->addMedia(url);
    }
    m_playButton->setEnabled(true);
    m_cutButton->setEnabled(true);
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
    StartTimeEdit->setTime(currentTime);
    m_stopButton->setEnabled(true);
}

void VideoPlayer::cutOperation()
{
    QString program = "D:\\program\\ffmpeg-2022-08-25-git-9bf9d42d01-essentials_build\\bin\\ffmpeg.exe";
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

    QString startTime = StartTimeEdit->time().toString("hh:mm:ss");
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
