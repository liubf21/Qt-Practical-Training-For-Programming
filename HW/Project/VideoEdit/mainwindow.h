#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <player.h>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void resizeEvent(QResizeEvent* size);

private:
    Ui::MainWindow *ui;
    VideoPlayer *m_player;
};
#endif // MAINWINDOW_H
