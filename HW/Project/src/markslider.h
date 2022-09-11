#ifndef MARKSLIDER_H
#define MARKSLIDER_H

//#include <QtWidgets>
#include <QSlider>
#include <QStyle>
#include <QPainter>

QT_BEGIN_NAMESPACE
class QSlider;
class QStyle;
class QPainter;
QT_END_NAMESPACE

class MarkSlider : public QSlider
{
  Q_OBJECT

 public:
  MarkSlider(Qt::Orientation orientation, QWidget *parent = NULL);
  void VerifyDefaultValue(int value);

 protected:
  void paintEvent(QPaintEvent *ev);

 private:
  int default_value_;
};
#endif // MARKSLIDER_H
