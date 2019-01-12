#-------------------------------------------------
#
# Project created by QtCreator 2018-11-26T17:43:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

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
    Enemy.cpp \
    Spell.cpp \
    UIController.cpp \
    MainWindow.cpp \
    AboutWindow.cpp \
    ChooseWindow.cpp \
    MainWindow.cpp \
    LoadingScreen.cpp

HEADERS  += \
    Player.h \
    Character.h \
    Map.h \
    Engine.h \
    Camera.h \
    Animator.h \
    AnimatedItem.h \
    Enemy.h \
    Spell.h \
    UIController.h \
    MainWindow.h \
    AboutWindow.h \
    ChooseWindow.h \
    MainWindow.h \
    LoadingScreen.h

FORMS    += \
    MainWindow.ui \
    AboutWindow.ui \
    ChooseWindow.ui \
    MainWindow.ui \
    LoadingScreen.ui

RESOURCES += \
    assets.qrc

DISTFILES +=
