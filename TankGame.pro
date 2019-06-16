#-------------------------------------------------
#
# Project created by QtCreator 2019-06-12T15:24:01
#
#-------------------------------------------------


QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TankGame
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    dialog.cpp \
    dialog_1.cpp \
    Bullet.cpp \
    EnemyTank.cpp \
    PlayerTank.cpp \
    Tank.cpp

HEADERS += mainwindow.h \
    dialog.h \
    dialog_1.h \
    Bullet.h \
    EnemyTank.h \
    PlayerTank.h \
    Tank.h

FORMS += mainwindow.ui \
    dialog.ui \
    dialog_1.ui

RESOURCES += \
    Image.qrc
RC_FILE = myapp.rc
