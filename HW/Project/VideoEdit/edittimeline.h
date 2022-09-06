#ifndef EDITTIMELINE_H
#define EDITTIMELINE_H

#include <QWidget>
#include <QSlider>
#include <QStyle>
#include <QPainter>
#include <QScrollArea>
#include <QUrl>
#include <QAbstractButton>

class EditTimeLine : public QWidget
{
    Q_OBJECT
public:
    explicit EditTimeLine(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent* Size);

signals:

public slots:
    void add(QUrl url,qint64 duration);
    void clip();

private:
    QSlider *m_EditSlider;
    QScrollArea *m_scrollArea;
    QWidget *m_widget;
    QList<QUrl> m_clips;
    QList<QAbstractButton*> m_clipButtons;
};

#endif // EDITTIMELINE_H
