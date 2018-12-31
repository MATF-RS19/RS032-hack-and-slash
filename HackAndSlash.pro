#-------------------------------------------------
#
# Project created by QtCreator 2018-11-26T17:43:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HackAndSlashDemo
TEMPLATE = app


SOURCES += main.cpp \
    Player.cpp \
    Character.cpp \
    Map.cpp \
    Engine.cpp \
    Camera.cpp \
    Animator.cpp \
    AnimatedItem.cpp \
    Enemy.cpp

HEADERS  += \
    Player.h \
    Character.h \
    Map.h \
    Engine.h \
    Camera.h \
    Animator.h \
    AnimatedItem.h \
    Enemy.h

FORMS    +=

RESOURCES += \
    assets.qrc
