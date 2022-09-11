#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QIntValidator>
#include <QUrl>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDebug>

QT_BEGIN_NAMESPACE
class QDialog;
class QIntValidator;
class QUrl;
class QFileDialog;
class QStandardPaths;
class QDebug;
QT_END_NAMESPACE
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    int H,W,X,Y,T=0;
    QString m_text;
    QUrl m_url;
    void addText(); // 加入文字的情况

private slots:
    void on_confirm_clicked();
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
    int checkMode=1; // 1为添加图片，0为添加文字

};

#endif // DIALOG_H
