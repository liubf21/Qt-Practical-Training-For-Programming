#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
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

class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    VideoPlayer(QWidget *parent = nullptr);
    ~VideoPlayer();

    void setUrl(const QUrl &url);
    void addToPlaylist(const QList<QUrl> &urls);

public slots:
    void openFile();
    void play();
    void jump(const QModelIndex &index);
    void playlistPositionChanged(int currentItem);

private slots:
    void mediaStateChanged(QMediaPlayer::State state);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void setPosition(int position);
    void handleError();

private:
    void updateDurationInfo(qint64 currentInfo);
    void startCut();
    void cutOperation();

    QMediaPlayer* m_mediaPlayer = nullptr; // 视频播放器
    QMediaPlaylist *m_playlist = nullptr; // 播放列表（素材）
    QVideoWidget *m_videoWidget = nullptr; // 播放窗口
    QAbstractButton *m_playButton = nullptr; // 播放按钮
    QAbstractButton *m_cutButton = nullptr; // 剪辑开始按钮
    QAbstractButton *m_stopButton = nullptr; // 剪辑停止按钮
    QTimeEdit *StartTimeEdit; // 剪辑开始时间
    QTimeEdit *EndTimeEdit; // 剪辑结束时间
    MarkSlider *m_positionSlider = nullptr; // 播放时间滑动按钮
    QLabel *m_errorLabel = nullptr;
    QLabel *m_labelDuration = nullptr;
    qint64 m_duration; // 视频总时长
    QTime currentTime;
//    QString tStr; // 字符串形式的当前时间

    PlaylistModel *m_playlistModel = nullptr; // 播放列表模型
    QAbstractItemView *m_playlistView = nullptr; // 播放列表视图
};

#endif // PLAYER_H
