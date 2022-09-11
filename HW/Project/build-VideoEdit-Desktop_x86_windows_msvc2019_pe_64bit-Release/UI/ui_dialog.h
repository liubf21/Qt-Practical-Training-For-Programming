/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QPushButton *cancel1;
    QPushButton *confirm;
    QLineEdit *HEdit;
    QLabel *label;
    QLabel *label_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QLabel *label_3;
    QLineEdit *WEdit;
    QLineEdit *TimeEdit;
    QPushButton *pushButton;
    QLabel *Picture_label;
    QLineEdit *WEdit_2;
    QLineEdit *HEdit_2;
    QLabel *label_4;
    QLabel *label_5;
    QTextEdit *textEdit;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(600, 480);
        cancel1 = new QPushButton(Dialog);
        cancel1->setObjectName(QString::fromUtf8("cancel1"));
        cancel1->setGeometry(QRect(150, 430, 93, 29));
        confirm = new QPushButton(Dialog);
        confirm->setObjectName(QString::fromUtf8("confirm"));
        confirm->setGeometry(QRect(330, 430, 93, 29));
        HEdit = new QLineEdit(Dialog);
        HEdit->setObjectName(QString::fromUtf8("HEdit"));
        HEdit->setGeometry(QRect(50, 380, 91, 25));
        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 380, 71, 31));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 340, 71, 31));
        radioButton = new QRadioButton(Dialog);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(340, 340, 91, 41));
        radioButton_2 = new QRadioButton(Dialog);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(410, 340, 231, 41));
        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(410, 300, 141, 31));
        QFont font;
        font.setPointSize(10);
        label_3->setFont(font);
        WEdit = new QLineEdit(Dialog);
        WEdit->setObjectName(QString::fromUtf8("WEdit"));
        WEdit->setGeometry(QRect(50, 340, 91, 25));
        TimeEdit = new QLineEdit(Dialog);
        TimeEdit->setObjectName(QString::fromUtf8("TimeEdit"));
        TimeEdit->setGeometry(QRect(390, 390, 131, 25));
        pushButton = new QPushButton(Dialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(80, 290, 121, 31));
        Picture_label = new QLabel(Dialog);
        Picture_label->setObjectName(QString::fromUtf8("Picture_label"));
        Picture_label->setGeometry(QRect(0, 0, 600, 280));
        WEdit_2 = new QLineEdit(Dialog);
        WEdit_2->setObjectName(QString::fromUtf8("WEdit_2"));
        WEdit_2->setGeometry(QRect(220, 340, 91, 25));
        HEdit_2 = new QLineEdit(Dialog);
        HEdit_2->setObjectName(QString::fromUtf8("HEdit_2"));
        HEdit_2->setGeometry(QRect(220, 380, 91, 25));
        label_4 = new QLabel(Dialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(150, 340, 71, 31));
        label_5 = new QLabel(Dialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(150, 380, 71, 31));
        textEdit = new QTextEdit(Dialog);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(0, 110, 600, 100));
        QFont font1;
        font1.setPointSize(12);
        textEdit->setFont(font1);

        retranslateUi(Dialog);
        QObject::connect(cancel1, SIGNAL(clicked()), Dialog, SLOT(close()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        cancel1->setText(QCoreApplication::translate("Dialog", "\345\217\226\346\266\210", nullptr));
        confirm->setText(QCoreApplication::translate("Dialog", "\347\241\256\350\256\244", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "\351\253\230\345\272\246", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog", "\345\256\275\345\272\246", nullptr));
        radioButton->setText(QCoreApplication::translate("Dialog", "\345\205\250\347\250\213", nullptr));
        radioButton_2->setText(QCoreApplication::translate("Dialog", "\344\273\216\345\275\223\345\211\215\346\227\266\351\227\264\345\274\200\345\247\213(s)", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog", "\346\214\201\347\273\255\346\227\266\351\227\264", nullptr));
        pushButton->setText(QCoreApplication::translate("Dialog", "\351\200\211\346\213\251\345\233\276\347\211\207", nullptr));
        Picture_label->setText(QCoreApplication::translate("Dialog", "\345\233\276\347\211\207", nullptr));
        label_4->setText(QCoreApplication::translate("Dialog", "\346\250\252\345\235\220\346\240\207", nullptr));
        label_5->setText(QCoreApplication::translate("Dialog", "\347\272\265\345\235\220\346\240\207", nullptr));
        textEdit->setHtml(QCoreApplication::translate("Dialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:9pt;\"><br /></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
