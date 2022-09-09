#ifndef EDITTIMELINE_H
#define EDITTIMELINE_H

#include <QWidget>
#include <QSlider>
#include <QStyle>
#include <QPainter>
#include <QScrollArea>
#include <QUrl>
#include <QAbstractButton>
#include <QPushButton>
#include <QFileInfo>
#include <QBoxLayout>
#include <QSignalMapper>
#include <QDebug>
#include <QProcess>

class EditTimeLine : public QWidget
{
    Q_OBJECT
public:
    explicit EditTimeLine(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent* Size);
    QUrl returnUrl(int);

signals:
    void playClips(int);
    void addUrl(QUrl);

public slots:
    void add(QUrl url,qint64 duration);
    void clip();
    void merge();
    void remove(int i);

private:
    QSlider *m_EditSlider;
    QScrollArea *m_scrollArea;
    QWidget *m_widget;
    QList<QUrl> m_clips;
    QList<QAbstractButton*> m_clipButtons;
    QList<qint64> m_clipsDuration;
    QSignalMapper *m_signalMapper;


    QAbstractButton *m_removeButton = nullptr; // 移除按钮
    QAbstractButton *m_mergeButton = nullptr; // 合并按钮

};

#endif // EDITTIMELINE_H
