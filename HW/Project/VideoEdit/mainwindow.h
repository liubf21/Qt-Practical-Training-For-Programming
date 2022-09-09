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

private slots:
    void on_add_picture_triggered();

    void on_add_subtitles_triggered();

    void on_add_text_triggered();

    void on_add_fadein_triggered();

    void on_add_fadeout_triggered();

    void on_add_zoomin_triggered();

    void on_add_zoomout_triggered();

    void on_add_moveright_triggered();

    void on_addmoveleft_triggered();

private:
    Ui::MainWindow *ui;
    VideoPlayer *m_player;
};
#endif // MAINWINDOW_H
