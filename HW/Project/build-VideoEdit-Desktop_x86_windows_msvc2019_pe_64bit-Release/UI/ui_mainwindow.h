/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *add_picture;
    QAction *add_text;
    QAction *add_subtitles;
    QAction *add_fadein;
    QAction *add_fadeout;
    QAction *add_zoomin;
    QAction *add_zoomout;
    QAction *add_moveright;
    QAction *addmoveleft;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_4;
    QMenu *menu_5;
    QMenu *menu_6;
    QMenu *menu_3;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("#MainWindow{background-image: url(:/res/res/hd-wallpaper.jpg);}"));
        add_picture = new QAction(MainWindow);
        add_picture->setObjectName(QString::fromUtf8("add_picture"));
        add_text = new QAction(MainWindow);
        add_text->setObjectName(QString::fromUtf8("add_text"));
        add_subtitles = new QAction(MainWindow);
        add_subtitles->setObjectName(QString::fromUtf8("add_subtitles"));
        add_fadein = new QAction(MainWindow);
        add_fadein->setObjectName(QString::fromUtf8("add_fadein"));
        add_fadeout = new QAction(MainWindow);
        add_fadeout->setObjectName(QString::fromUtf8("add_fadeout"));
        add_zoomin = new QAction(MainWindow);
        add_zoomin->setObjectName(QString::fromUtf8("add_zoomin"));
        add_zoomout = new QAction(MainWindow);
        add_zoomout->setObjectName(QString::fromUtf8("add_zoomout"));
        add_moveright = new QAction(MainWindow);
        add_moveright->setObjectName(QString::fromUtf8("add_moveright"));
        addmoveleft = new QAction(MainWindow);
        addmoveleft->setObjectName(QString::fromUtf8("addmoveleft"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 17));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_4 = new QMenu(menu_2);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        menu_5 = new QMenu(menu_2);
        menu_5->setObjectName(QString::fromUtf8("menu_5"));
        menu_6 = new QMenu(menu_2);
        menu_6->setObjectName(QString::fromUtf8("menu_6"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menu->addAction(add_picture);
        menu->addAction(add_text);
        menu_2->addAction(menu_4->menuAction());
        menu_2->addAction(menu_5->menuAction());
        menu_2->addAction(menu_6->menuAction());
        menu_4->addAction(add_fadein);
        menu_4->addAction(add_fadeout);
        menu_5->addSeparator();
        menu_5->addAction(add_zoomin);
        menu_5->addAction(add_zoomout);
        menu_6->addAction(add_moveright);
        menu_6->addAction(addmoveleft);
        menu_3->addAction(add_subtitles);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        add_picture->setText(QCoreApplication::translate("MainWindow", "\346\217\222\345\205\245\345\233\276\347\211\207(\346\210\226\350\247\206\351\242\221)", nullptr));
        add_text->setText(QCoreApplication::translate("MainWindow", "\346\217\222\345\205\245\346\226\207\345\255\227", nullptr));
        add_subtitles->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\205\245", nullptr));
        add_fadein->setText(QCoreApplication::translate("MainWindow", "\346\267\241\345\205\245", nullptr));
        add_fadeout->setText(QCoreApplication::translate("MainWindow", "\346\267\241\345\207\272", nullptr));
        add_zoomin->setText(QCoreApplication::translate("MainWindow", "\346\224\276\345\244\247 ", nullptr));
        add_zoomout->setText(QCoreApplication::translate("MainWindow", "\347\274\251\345\260\217", nullptr));
        add_moveright->setText(QCoreApplication::translate("MainWindow", "\345\217\263\347\247\273", nullptr));
        addmoveleft->setText(QCoreApplication::translate("MainWindow", "\345\267\246\347\247\273", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\347\264\240\346\235\220", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\347\211\271\346\225\210", nullptr));
        menu_4->setTitle(QCoreApplication::translate("MainWindow", "(Videos)\346\267\241\345\205\245\346\267\241\345\207\272\346\225\210\346\236\234", nullptr));
        menu_5->setTitle(QCoreApplication::translate("MainWindow", "(Pictures)\347\274\251\346\224\276\346\225\210\346\236\234", nullptr));
        menu_6->setTitle(QCoreApplication::translate("MainWindow", "(Pictures)\347\247\273\345\212\250\346\225\210\346\236\234", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\345\255\227\345\271\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
