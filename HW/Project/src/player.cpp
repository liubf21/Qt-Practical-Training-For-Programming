#include "player.h"
#include "playlistmodel.h"
#include "markslider.h"
#include "edittimeline.h"
#include "dialog.h"
#include <string>

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
    openButton = new QPushButton(tr("Open..."));
    openButton->setAutoFillBackground(true);
    openButton->setPalette(p);
    connect(openButton, &QAbstractButton::clicked, this, &VideoPlayer::openFile);

//    设置导出按钮
    m_exportButton = new QPushButton(tr("Export"));
    m_exportButton->setEnabled(false);
    m_exportButton->setIcon(QIcon(":/res/res/export.png"));
    m_exportButton->setAutoFillBackground(true);
    m_exportButton->setPalette(p);
    connect(m_exportButton, &QAbstractButton::clicked, this, &VideoPlayer::exportvideo);

//    设置播放按钮
    m_playButton = new QPushButton;
    m_playButton->setEnabled(false);
    m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(m_playButton, &QAbstractButton::clicked,
            this, &VideoPlayer::play);

//    设置剪辑开始按钮  Slider在同一位置点击两次该按钮则为拆分
    m_cutButton = new QPushButton;
    m_cutButton->setEnabled(false);
    m_cutButton->setCheckable(true); // 设置为可选中
    m_cutButton->setIcon(QIcon(":/res/res/cut.png"));
    connect(m_cutButton, &QAbstractButton::clicked,
            this, &VideoPlayer::startCut);


//    设置剪辑停止按钮
    m_stopButton = new QPushButton;
    m_stopButton->setEnabled(false);
    m_stopButton->setIcon(QIcon(":/res/res/stop.png"));
    connect(m_stopButton, &QAbstractButton::clicked,
            this, &VideoPlayer::cutOperation);

//    设置加入主时间轴按钮
    m_joinButton = new QPushButton;
    m_joinButton->setEnabled(false);
    m_joinButton->setIcon(QIcon(":/res/res/join.png"));
    connect(m_joinButton, &QAbstractButton::clicked,
            this, &VideoPlayer::joinEdit);

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
    connect(m_editTimeLine, SIGNAL(playClips(int)), this, SLOT(playUrls(int))); // 播放主时间轴的视频
    connect(m_editTimeLine, SIGNAL(addUrl(QUrl)), this, SLOT(addUrlEdit(QUrl))); // 返回合并后的视频链接

//    布局

    QBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(m_positionSlider);
    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setContentsMargins(0, 0, 0, 0);
    controlLayout->addWidget(openButton);
    controlLayout->addWidget(m_exportButton);
    controlLayout->addStretch(1);
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
    Blayout->addLayout(layout,3);

    QBoxLayout *Wholelayout = new QVBoxLayout;
    Wholelayout->addLayout(Blayout,3);
    Wholelayout->addWidget(m_editTimeLine,1);
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
}

static bool isPlaylist(const QUrl &url) // Check for ".m3u" playlists.
{
    if (!url.isLocalFile())
        return false;
    const QFileInfo fileInfo(url.toLocalFile());
//    是否满足 存在且后缀为m3u ；compare比较字符串大小，相等才返回0
    return(fileInfo.exists() && !fileInfo.suffix().compare(QLatin1String("m3u"), Qt::CaseInsensitive));
}

void VideoPlayer::addToPlaylist(const QList<QUrl> &urls)
{
    for (auto &url: urls) {
        if (isPlaylist(url)) // 判断是否是播放列表
        {m_playlist->load(url);;}
        else if(!m_urls.count(url)) // 避免重复加入
        {m_playlist->addMedia(url);
        m_urls.append(url);}
    }
    m_playButton->setEnabled(true);
    m_cutButton->setEnabled(true);
    m_joinButton->setEnabled(true);
    m_exportButton->setEnabled(true);
}

// 右键菜单进行文件的重命名和删除
void VideoPlayer::show_contextmenu1(const QPoint& pos)
{
    //点击空白处将不会出现菜单
    if(!((m_playlistView->selectionModel()->selectedIndexes()).empty()))
    {
        QMenu *cmenu = new QMenu(m_playlistView);
        QAction *RenameAction = cmenu->addAction("重命名");
        QAction *DeleteAction = cmenu->addAction("删除");
        connect(RenameAction, SIGNAL(triggered(bool)), this, SLOT(menu_Rename()));
        connect(DeleteAction, SIGNAL(triggered(bool)), this, SLOT(menu_Delete()));
        cmenu->exec(QCursor::pos());//在当前鼠标位置显示
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
    // 操作文件时注意\ 和 / 的差异
    QUrl location = m_playlist->media(m_playlistView->selectionModel()->currentIndex().row()).request().url();
    m_playlist->removeMedia(m_playlistView->selectionModel()->currentIndex().row());
    m_urls.removeAll(location);
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
//    qDebug()<<m_playlist->currentMedia().request().url().toLocalFile();
//    获取当前播放视频的地址

}

// 跳转视频
void VideoPlayer::jump(const QModelIndex &index)
{
    m_mediaPlayer->setPlaylist(m_playlist);
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
//    Slider在同一位置点击两次该按钮则为拆分
    if(cutTime==currentTime&&m_cutButton->isChecked())
    {
        QProcess *clipProcess = new QProcess(this);
        QProcess *clipProcess_2 = new QProcess(this);
        connect(clipProcess_2,SIGNAL(finished(int)),this,SLOT(workOut(int)));
        QString program = "../src/ffmpeg.exe";
        QList<QUrl> url_list;
        QStringList arguments;
        QString inputPath = m_playlist->currentMedia().request().url().toLocalFile();
        QFile sourceFile(inputPath);
        if(!sourceFile.exists()){
            QMessageBox::information(this,"提示","找不到源文件");
            return;
        }
        int temp=1;
        QString outputPath = QFileInfo(sourceFile).absolutePath() +"/clip_"+QString::number(temp)+".mp4";
        while(QFile::exists(outputPath))
        {
            ++temp;
            outputPath = QFileInfo(sourceFile).absolutePath() +"/clip_"+QString::number(temp)+".mp4";
        }
        QString startTime = cutTime.toString("hh:mm:ss");
        arguments << "-i" << inputPath << "-r" << "25"<<"-ss"
                  <<"0"<< "-to" << startTime << outputPath;
        clipProcess->start(program, arguments);
        url_list.append(QUrl::fromLocalFile(outputPath));
        ++temp;
        outputPath = QFileInfo(sourceFile).absolutePath() +"/clip_"+QString::number(temp)+".mp4";
        arguments.clear();
        arguments << "-i" << inputPath << "-r" << "25"<<"-ss"
                  <<startTime<< "-t" << "9999" << outputPath;
        clipProcess_2->start(program, arguments);
        url_list.append(QUrl::fromLocalFile(outputPath));
        addToPlaylist(url_list);
    }
    else{
    m_positionSlider->VerifyDefaultValue(m_positionSlider->sliderPosition());
    cutTime=currentTime;
    m_stopButton->setEnabled(true);
    }
}

void VideoPlayer::cutOperation()
{
    QString program = "../src/ffmpeg.exe";
//    得到当前播放视频的文件位置的QUrl，再转为字符串
    QString inputPath = m_playlist->currentMedia().request().url().toLocalFile();
    QFile sourceFile(inputPath);
    if(!sourceFile.exists()){
        QMessageBox::information(this,"提示","找不到源文件");
        return;
    }
    int temp=1;
    QString outputPath = QFileInfo(sourceFile).absolutePath() +"/clip_"+QString::number(temp)+".mp4";
    while(QFile::exists(outputPath))
    {
        ++temp;
        outputPath = QFileInfo(sourceFile).absolutePath() +"/clip_"+QString::number(temp)+".mp4";
    }
    if(cutTime>currentTime)
    {
        QMessageBox::warning(this,"Warning","剪辑失败!");
        return;
    }
    QString startTime = cutTime.toString("hh:mm:ss");
    QString endTime= currentTime.toString("hh:mm:ss");
    QStringList arguments;
    arguments << "-i" << inputPath << "-r" << "25"<<"-ss";
    arguments <<startTime<< "-to" << endTime << outputPath;

    QProcess *clipProcess = new QProcess(this);
    connect(clipProcess,SIGNAL(finished(int)),this,SLOT(workOut(int)));
    clipProcess->start(program, arguments);
    QList<QUrl> url_list;
    url_list.append(QUrl::fromLocalFile(outputPath));
    addToPlaylist(url_list);

}

//    将选中视频加入主时间轴
void VideoPlayer::joinEdit()
{
    QUrl url=m_playlist->currentMedia().request().url();
    QString filename = QFileInfo(url.path()).fileName();
//    判断一下是否是图片,是图片则设置最短时间,并转为视频(tmp临时文件，程序结束删除)
    if(filename.right(4)==(".jpg") || filename.right(4)==(".bmp") || filename.right(4)==(".png"))
    {
        QString program = "../src/ffmpeg.exe";
        QString inputPath = url.toLocalFile();
        QFile sourceFile(inputPath);
        if(!sourceFile.exists()){
            QMessageBox::information(this,"提示","找不到源文件");
            return;
        }
        bool ok; // 接受对话框的返回值
        int t = QInputDialog::getInt(this, tr("Add an image"),"请设置图片持续时间：(s)",
                                             3,1,10,1, &ok);
        if(ok)
        {
            int temp=1;
            QString outputPath = QFileInfo(sourceFile).absolutePath() +"/tmp_"+QString::number(temp)+".mp4";
            while(QFile::exists(outputPath))
            {
                ++temp;
                outputPath = QFileInfo(sourceFile).absolutePath() +"/tmp_"+QString::number(temp)+".mp4";
            }
            QStringList arguments;
            arguments <<"-f"<<"image2"<<"-loop"<<"1"<< "-i" << inputPath<<"-vcodec"<<"libx264"<<"-pix_fmt"<<"yuv420p"<<
                        "-r" << "25"<<"-t"<<QString::number(t);
            arguments << outputPath;
            QProcess *clipProcess = new QProcess(this);
            connect(clipProcess,SIGNAL(finished(int)),this,SLOT(workOut(int)));
            clipProcess->start(program, arguments);
            url=QUrl::fromLocalFile(outputPath);
            m_duration=t;
        }else{
            return;
        }

    }
    m_editTimeLine->add(url,m_duration);
}

void VideoPlayer::playUrls(int i)
{
    QUrl url=m_editTimeLine->returnUrl(i);
    m_mediaPlayer->setMedia(url);
    if(!m_urls.count(url)) // 避免重复加入
    {m_playlist->addMedia(url);
    m_urls.append(url);}
//    m_mediaPlayer->play();
}

void VideoPlayer::addUrlEdit(QUrl url)
{
    QList<QUrl> url_list;
    url_list.append(url);
    addToPlaylist(url_list);
}

void VideoPlayer::addMaterial(int i)
{
    Dialog *dlg = new Dialog(this);
    dlg->show();
    if(!i)
    {
        dlg->show();
    }
    if(dlg->exec()==QDialog::Accepted){      
        QString program = "../src/ffmpeg.exe";
        QString inputPath =m_playlist->currentMedia().request().url().toLocalFile() ; // 视频路径
        QString vfstring;
        if(i){
            QString picPath=dlg->m_url.toLocalFile();
            //        必须插入单个\程序才能运行，但\单个操作为空，\\进行插入时又变成两个(原因是qDebug会将转义符输出
            picPath.insert(picPath.indexOf(":"),QString("\\"));
            vfstring="movie='"+picPath+"',scale="+QString::number(dlg->W)+":"+QString::number(dlg->H)
                    +"[mask];[in][mask]overlay="+QString::number(dlg->X)+":"+QString::number(dlg->Y);
            if(dlg->T){
                vfstring+=":enable='between (t,"+QString::number(m_positionSlider->sliderPosition())+","+
                        QString::number(m_positionSlider->sliderPosition()+dlg->T)+")'";
            }
            vfstring+="[out]";}
        else{
            vfstring="drawtext=fontfile=../src/msyh.ttc:fontcolor=white:fontsize=40:text='"+dlg->m_text+"':x="+
                    QString::number(dlg->X)+":y="+QString::number(dlg->Y);
            if(dlg->T){
                vfstring+=":enable='between (t,"+QString::number(m_duration)+","+
                        QString::number(m_duration+dlg->T)+")'";
            }
        }
        QFile sourceFile(inputPath);
        if(!sourceFile.exists()){
            QMessageBox::information(this,"提示","找不到源文件");
            return;
        }
        int temp=1;
        QString outputPath = QFileInfo(sourceFile).absolutePath() +"/tmp_"+QString::number(temp)+".mp4";
        while(QFile::exists(outputPath))
        {
            ++temp;
            outputPath = QFileInfo(sourceFile).absolutePath() +"/tmp_"+QString::number(temp)+".mp4";
        }
        QStringList arguments;
        arguments << "-i" <<inputPath
                  <<"-vf"<<vfstring<<"-y";
        arguments << outputPath;
        QProcess *clipProcess = new QProcess(this);
        connect(clipProcess,SIGNAL(finished(int)),this,SLOT(workOut(int)));
        clipProcess->start(program, arguments);
        QList<QUrl> url_list;
        url_list.append(QUrl::fromLocalFile(outputPath));
        addToPlaylist(url_list);
    }
}

void VideoPlayer::addSubtitles()
{
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setWindowTitle(tr("Open Subtitles"));
    fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).value(0, QDir::homePath()));
    if (fileDialog.exec() == QDialog::Accepted)
    {QList<QUrl> urls=fileDialog.selectedUrls();
        QString program = "../src/ffmpeg.exe";
        QString inputPath =m_playlist->currentMedia().request().url().toLocalFile() ; // 视频路径
        QString test=urls[0].toLocalFile();
        test.insert(test.indexOf(":"),QString("\\"));
        QString vfstring="subtitles='"+test+"'";
        QFile sourceFile(inputPath);
        if(!sourceFile.exists()){
            QMessageBox::information(this,"提示","找不到源文件");
            return;
        }
        int temp=1;
        QString outputPath = QFileInfo(sourceFile).absolutePath() +"/tmp_"+QString::number(temp)+".mp4";
        while(QFile::exists(outputPath))
        {
            ++temp;
            outputPath = QFileInfo(sourceFile).absolutePath() +"/tmp_"+QString::number(temp)+".mp4";
        }
        QStringList arguments;
        arguments << "-i" <<inputPath
                  <<"-vf"<<vfstring<<"-y";
        arguments << outputPath;
        QProcess *clipProcess = new QProcess(this);
        connect(clipProcess,SIGNAL(finished(int)),this,SLOT(workOut(int)));
        clipProcess->start(program, arguments);
        QList<QUrl> url_list;
        url_list.append(QUrl::fromLocalFile(outputPath));
        addToPlaylist(url_list);

    }
}

void VideoPlayer::addFade(int in)
{
    // 先判断当前选中的是否是视频
    QString program = "../src/ffmpeg.exe";
    QString inputPath =m_playlist->currentMedia().request().url().toLocalFile() ; // 视频路径
    QFile sourceFile(inputPath);
    if(!sourceFile.exists()){
        QMessageBox::information(this,"提示","找不到源文件");
        return;
    }
    int temp=1;
    QString outputPath = QFileInfo(sourceFile).absolutePath() +"/fade_"+QString::number(temp)+".mp4";
    while(QFile::exists(outputPath))
    {
        ++temp;
        outputPath = QFileInfo(sourceFile).absolutePath() +"/fade_"+QString::number(temp)+".mp4";
    }
    QStringList arguments;
    arguments << "-i" <<inputPath<<"-y";
    if(in){
             arguments <<"-vf"<<"fade=in:0:50";
    }else{
        arguments <<"-vf"<<"fade=out:"+QString::number(m_duration) +"*25-50:50";
    }
    arguments << outputPath;
    QProcess *clipProcess = new QProcess(this);
    connect(clipProcess,SIGNAL(finished(int)),this,SLOT(workOut(int)));
    clipProcess->start(program, arguments);
    QList<QUrl> url_list;
    url_list.append(QUrl::fromLocalFile(outputPath));
    addToPlaylist(url_list);
}

void VideoPlayer::addZoom(int in)
{
    // 先判断当前选中的是否是图片，注意png转jpg的图片可能无法使用
    QString program = "../src/ffmpeg.exe";
    QString inputPath =m_playlist->currentMedia().request().url().toLocalFile() ; // 视频路径
    QFile sourceFile(inputPath);
    if(!sourceFile.exists()){
        QMessageBox::information(this,"提示","找不到源文件");
        return;
    }
    int temp=1;
    QString outputPath = QFileInfo(sourceFile).absolutePath() +"/zoom_"+QString::number(temp)+".mp4";
    while(QFile::exists(outputPath))
    {
        ++temp;
        outputPath = QFileInfo(sourceFile).absolutePath() +"/zoom_"+QString::number(temp)+".mp4";
    }
    QStringList arguments;
    arguments << "-i" <<inputPath<<"-y";
    if(in){

             arguments <<"-vf"<<"zoompan=x='iw/2*(1-1/zoom)':y='ih/2*(1-1/zoom)':"
                                "z='min(zoom+0.002,1.2)':d=25*3";
    }else{
        arguments <<"-vf"<<"zoompan=x='iw/2*(1-1/zoom)':y='ih/2*(1-1/zoom)':"
                           "z='if(eq(on,1),1.2,zoom-0.002)':d=25*3";
    }
    arguments <<"-c:v"<<"libx264"<<"-t"<<"3"<<outputPath;
    QProcess *clipProcess = new QProcess(this);
    connect(clipProcess,SIGNAL(finished(int)),this,SLOT(workOut(int)));
    clipProcess->start(program, arguments);
    QList<QUrl> url_list;
    url_list.append(QUrl::fromLocalFile(outputPath));
    addToPlaylist(url_list);

}

void VideoPlayer::addMove(int in)
{
    // 先判断当前选中的是否是图片
    QString program = "../src/ffmpeg.exe";
    QString inputPath =m_playlist->currentMedia().request().url().toLocalFile() ; // 视频路径
    QFile sourceFile(inputPath);
    if(!sourceFile.exists()){
        QMessageBox::information(this,"提示","找不到源文件");
        return;
    }
    int temp=1;
    QString outputPath = QFileInfo(sourceFile).absolutePath() +"/move_"+QString::number(temp)+".mp4";
    while(QFile::exists(outputPath))
    {
        ++temp;
        outputPath = QFileInfo(sourceFile).absolutePath() +"/move_"+QString::number(temp)+".mp4";
    }
    QStringList arguments;
    arguments << "-i" <<inputPath<<"-y";
    if(in){

             arguments <<"-vf"<<"zoompan=x='(100+(on/25*4)*(400-100))*(1-1/zoom)':"
                                "y='(50+(on/25*4)*(300-50))*(1-1/zoom)':z='1.5':d=25*3";
    }else{
        arguments <<"-vf"<<"zoompan=x='(2000+(on/25*4)*(100-200))*(1-1/zoom)':"
                           "y='(1800+(on/25*4)*(50-180))*(1-1/zoom)':z='1.5':d=25*3";
    }
    arguments <<"-c:v"<<"libx264"<<"-t"<<"3"<<outputPath;
    QProcess *clipProcess = new QProcess(this);
    connect(clipProcess,SIGNAL(finished(int)),this,SLOT(workOut(int)));
    clipProcess->start(program, arguments);
    QList<QUrl> url_list;
    url_list.append(QUrl::fromLocalFile(outputPath));
    addToPlaylist(url_list);

}

void VideoPlayer::workOut(int i)
{
    if(i){
        QMessageBox::information(this,"提示","视频处理失败！");
    }else{
        QMessageBox::information(this,"提示","视频处理已完成！");
    }
}

void VideoPlayer::exportvideo()
{
    // 可导出不同格式、码率、分辨率的视频，使用combobox和dialogbutton
    QDialog *export_dialog= new QDialog;
    export_dialog->setFixedSize(600,480);
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,export_dialog);
    connect(buttonBox, &QDialogButtonBox::accepted, export_dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, export_dialog, &QDialog::reject);
    export_dialog->show();
    buttonBox->show();
    buttonBox->setGeometry(100,400,400,100);
    QComboBox *comboBox[3];
    QLabel *label[3];
    for(int i=1;i<=3;i++)
    {
        comboBox[i-1]=new QComboBox(export_dialog);
        comboBox[i-1]->setGeometry(300,100*i,200,60);
        comboBox[i-1]->show();
        label[i-1]=new QLabel(export_dialog);
        label[i-1]->setGeometry(100,100*i,200,60);
        label[i-1]->show();
    }
    label[0]->setText("设置导出格式");
    label[1]->setText("设置分辨率");
    label[2]->setText("设置码率");
    QStringList params;
    params<<"avi"<<"mkv"<<"mp4"<<"flv"<<"gif";
    comboBox[0]->addItems(params); // 将这些数据加入到comboBox中
    comboBox[0]->setCurrentIndex(2); // 设置默认选中项
    params.clear();
    params<<"480p"<<"720p"<<"1080p";
    comboBox[1]->addItems(params); // 将这些数据加入到comboBox中
    comboBox[1]->setCurrentIndex(1); // 设置默认选中项
    params.clear();
    params<<"1M"<<"3M"<<"5M";
    comboBox[2]->addItems(params); // 将这些数据加入到comboBox中
    comboBox[2]->setCurrentIndex(1); // 设置默认选中项
    if(export_dialog->exec()==QDialog::Accepted){
        QString suffix=comboBox[0]->currentText(),Resolution,Bitrate[2];

        switch(comboBox[1]->currentIndex()){
        case 0:Resolution="scale=480:";break;
        case 1:Resolution="scale=720:-1";break;
        case 2:Resolution="scale=1080:-1";break;
        }
        switch(comboBox[2]->currentIndex()){
        case 0:Bitrate[0]="1000k";Bitrate[1]="1500k";break;
        case 1:Bitrate[0]="2000k";Bitrate[1]="2500k";break;
        case 2:Bitrate[0]="5000k";Bitrate[1]="6000k";break;
        }

        QString program = "../src/ffmpeg.exe";
        QString inputPath =m_playlist->currentMedia().request().url().toLocalFile() ; // 视频路径
        QFile sourceFile(inputPath);
        if(!sourceFile.exists()){
            QMessageBox::information(this,"提示","找不到源文件");
            return;
        }
        int temp=1;
        QString outputPath = QFileInfo(sourceFile).absolutePath() +"/change_"+QString::number(temp)+"."+suffix;
        while(QFile::exists(outputPath))
        {
            ++temp;
            outputPath = QFileInfo(sourceFile).absolutePath() +"/change_"+QString::number(temp)+"."+suffix;
        }
        QStringList arguments;
        arguments << "-i" <<inputPath<<"-y";
        arguments <<"-b:v"<<Bitrate[0]<<"-maxrate"<<Bitrate[1]<<"-bufsize"<<"2000k"<< "-vf" <<Resolution
                 <<"-vf"<<"pad=ceil(iw/2)*2:ceil(ih/2)*2"<<outputPath;
        QProcess *clipProcess = new QProcess(this);
        connect(clipProcess,SIGNAL(finished(int)),this,SLOT(workOut(int)));
        clipProcess->start(program, arguments);
        QList<QUrl> url_list;
        url_list.append(QUrl::fromLocalFile(outputPath));
        addToPlaylist(url_list);
    }
}
