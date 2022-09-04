#include <QApplication>
#include <QSlider>
#include <QVBoxLayout>
#include <QtGui>
#include <QStyle>
#include <QMainWindow>

class DefaultValueSlider : public QSlider {
  Q_OBJECT

 public:
  DefaultValueSlider(Qt::Orientation orientation, QWidget *parent = NULL)
    : QSlider(orientation, parent),
      default_value_(-1) {
    connect(this, SIGNAL(valueChanged(int)), SLOT(VerifyDefaultValue(int)));
  }

 protected:
  void paintEvent(QPaintEvent *ev) {
    int position = QStyle::sliderPositionFromValue(minimum(),
                                                   maximum(),
                                                   default_value_,
                                                   width());
    QPainter painter(this);
    painter.drawLine(position, 0, position, height());
    QSlider::paintEvent(ev);
  }

 private slots:
  void VerifyDefaultValue(int value){
    if (default_value_ == -1) {
      default_value_ = value;
      update();
    }
  }

 private:
  int default_value_;
};

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  DefaultValueSlider *slider = new DefaultValueSlider(Qt::Horizontal);
  slider->setValue(30);

  QWidget *w = new QWidget;
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(slider);
  layout->addStretch(1);
  w->setLayout(layout);

  QMainWindow window;
  window.setCentralWidget(w);
  window.show();

  return app.exec();
}
