#multimediawidgets 对应<QCameraViewfinder>等
#multimedia        对应<QCamera>, <QCameraImageCapture>,<QAbstractVideoSurface>等
QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    player.cpp \
    playlistmodel.cpp

HEADERS += \
    mainwindow.h \
    player.h \
    playlistmodel.h

FORMS += \
    mainwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
RC_ICONS = myico.ico

RESOURCES += \
    myimages.qrc \
    myimages.qrc