#multimediawidgets 对应<QCameraViewfinder>等
#multimedia        对应<QCamera>, <QCameraImageCapture>,<QAbstractVideoSurface>等
QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
UI_DIR=./UI
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
win32-msvc* {
    QMAKE_CXXFLAGS += /source-charset:utf-8 /execution-charset:utf-8
}
SOURCES += \
    dialog.cpp \
    edittimeline.cpp \
    main.cpp \
    mainwindow.cpp \
    markslider.cpp \
    player.cpp \
    playlistmodel.cpp

HEADERS += \
    dialog.h \
    edittimeline.h \
    mainwindow.h \
    markslider.h \
    player.h \
    playlistmodel.h

FORMS += \
    dialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
RC_ICONS = myico.ico

RESOURCES += \
    myimages.qrc
