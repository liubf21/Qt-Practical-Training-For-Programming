#include "dialog.h"
#include "ui_dialog.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QIntValidator* IntValidator = new QIntValidator;
    IntValidator->setRange(-1, 1000);//可以改成（-255,255），这样就是负数
    ui->WEdit_2->setValidator(IntValidator);
    ui->WEdit_2->setPlaceholderText("0-1000");//背景提示用户输入范围
    ui->HEdit_2->setValidator(IntValidator);
    ui->HEdit_2->setPlaceholderText("0-1000");
    IntValidator->setRange(49, 1000);
    ui->WEdit->setValidator(IntValidator);
    ui->WEdit->setPlaceholderText("50-1000");
    ui->HEdit->setValidator(IntValidator);
    ui->HEdit->setPlaceholderText("50-1000");
    ui->TimeEdit->setValidator(IntValidator);
    ui->TimeEdit->setPlaceholderText("0-300");
    ui->textEdit->hide();

}

Dialog::~Dialog()
{
    delete ui;
}



void Dialog::on_confirm_clicked()
{
    X=ui->WEdit_2->text().toInt();
    Y=ui->HEdit_2->text().toInt();
    if(!ui->radioButton->isChecked())
    {
        T=ui->TimeEdit->text().toInt();
    }
    if(checkMode)
    {
        W=ui->WEdit->text().toInt();
        H=ui->HEdit->text().toInt();
        if(H>49&&H<1001&&W>49&&W<1001&&X>-1&&X<1001&&Y>-1&&Y<1001)
        {
            accept();
        }else{
            reject();
        }
    }else{
        m_text=ui->textEdit->toPlainText();
        if(X>-1&&X<1001&&Y>-1&&Y<1001)
        {
            accept();
        }else{
            reject();
        }
    }
}


void Dialog::on_pushButton_clicked()
{
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setWindowTitle(tr("Open Picture"));
    QStringList mimeTypeFilters({"image/jpeg", // will show "JPEG image (*.jpeg *.jpg *.jpe)
                                 "image/png",  // will show "PNG image (*.png)"
                                 "image/bmp"
                                });

    fileDialog.setMimeTypeFilters(mimeTypeFilters);
    fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).value(0, QDir::homePath()));

    if (fileDialog.exec() == QDialog::Accepted)
    {QList<QUrl> urls=fileDialog.selectedUrls();
        qDebug()<<urls[0].toLocalFile();
        m_url=urls[0];
        QPixmap pixmap =(urls[0].toLocalFile()); // 添加选中文件的路径
        ui->Picture_label->setPixmap(pixmap.scaled(ui->Picture_label->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    }
}

void Dialog::addText()
{
    ui->textEdit->show();
    ui->pushButton->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->WEdit->hide();
    ui->HEdit->hide();
    checkMode=0;
}
