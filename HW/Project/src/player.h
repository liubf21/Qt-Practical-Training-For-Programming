#ifndef PLAYER_H
#define PLAYER_H

#include <QtWidgets>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>

QT_BEGIN_NAMESPACE
class QAbstractItemView;
class QAbstractButton;
class QTimeEdit;
class QTime;
class QSlider;
class QLabel;
class QUrl;
QT_END_NAMESPACE
class PlaylistModel;
class MarkSlider;
class EditTimeLine;

class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    VideoPlayer(QWidget *parent = nullptr);
    ~VideoPlayer();

    void addToPlaylist(const QList<QUrl> &urls);

public slots:
    void openFile(); // 打开文件
    void play(); // 视频播放
    void jump(const QModelIndex &index); // 视频跳转
    void playlistPositionChanged(int currentItem); // 播放列表位置改变
    void playUrls(int);
    void addUrlEdit(QUrl);
    void addMaterial(int i);  // 增加贴图或文字水印素材,i=1为贴图
    void addSubtitles(); // 导入字幕
    void addFade(int in); // 淡入淡出特效，对视频操作，in=1为淡入，0为淡出
    void addZoom(int in);   // 放大缩小特效，只有图片能操作
    void addMove(int in);   // 移动特效，只有图片能操作

private slots:
    void mediaStateChanged(QMediaPlayer::State state); // 播放状态改变
    void positionChanged(qint64 position); // 播放位置改变
    void durationChanged(qint64 duration); // 视频时长改变
    void setPosition(int position); // 设置位置
    void handleError(); // 处理错误
    void show_contextmenu1(const QPoint& pos); // 列表右键操作
    void menu_Rename(); // 列表右键重命名
    void menu_Delete(); // 列表右键删除
    void startCut(); // 开始剪辑
    void cutOperation(); // 剪辑操作
    void joinEdit(); // 加入时间轴
    void workOut(int); // 视频处理完成
    void exportvideo(); // 导出视频


private:
    void updateDurationInfo(qint64 currentInfo);

    QMediaPlayer* m_mediaPlayer = nullptr; // 视频播放器

    QVideoWidget *m_videoWidget = nullptr; // 播放窗口
    QAbstractButton *openButton = nullptr; // 打开文件按钮
    QAbstractButton *m_playButton = nullptr; // 播放按钮
    QAbstractButton *m_cutButton = nullptr; // 剪辑开始按钮
    QAbstractButton *m_stopButton = nullptr; // 剪辑停止按钮
    QAbstractButton *m_joinButton = nullptr; // 加入时间轴按钮
    QAbstractButton *m_exportButton = nullptr; // 导出按钮
    MarkSlider *m_positionSlider = nullptr; // 播放时间滑动按钮
    QLabel *m_errorLabel = nullptr;
    QLabel *m_labelDuration = nullptr;
    qint64 m_duration; // 视频总时长
    QTime cutTime; // 剪辑开始时间
    QTime currentTime; // 当前时间

    QMediaPlaylist *m_playlist = nullptr; // 播放列表（素材）
    PlaylistModel *m_playlistModel = nullptr; // 播放列表模型
    QAbstractItemView *m_playlistView = nullptr; // 播放列表视图
    QList<QUrl> m_urls;

    EditTimeLine *m_editTimeLine = nullptr;
};

#endif // PLAYER_H
