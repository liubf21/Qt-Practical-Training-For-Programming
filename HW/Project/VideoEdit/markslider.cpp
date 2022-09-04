#include "markslider.h"
MarkSlider::MarkSlider(Qt::Orientation orientation, QWidget *parent)
  : QSlider(orientation, parent),
    default_value_(-1) {
//  connect(this, SIGNAL(valueChanged(int)), SLOT(VerifyDefaultValue(int)));
}

void MarkSlider::paintEvent(QPaintEvent *ev) {
  int position = QStyle::sliderPositionFromValue(minimum(),
                                                 maximum(),
                                                 default_value_,
                                                 width());
  QPainter painter(this);
  painter.setPen(QPen(QColor(0, 160, 230), 2));
//  painter.setBrush(QColor(255, 160, 90));
  painter.drawLine(position, 0, position, height());
  QSlider::paintEvent(ev);
}

void MarkSlider::VerifyDefaultValue(int value){
    default_value_ = value;
    update();
}
