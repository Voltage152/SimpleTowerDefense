#-------------------------------------------------
#
# Project created by QtCreator 2022-05-02T13:53:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simpleTowerDefence
TEMPLATE = app
RC_ICONS = ico.ico

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainWidget.cpp \
    waypoint.cpp \
    position.cpp \
    unit.cpp \
    map.cpp \
    startwidget.cpp \
    enemy.cpp \
    road.cpp \
    carrier.cpp

HEADERS += \
        mainWidget.h \
    waypoint.h \
    position.h \
    unit.h \
    map.h \
    startwidget.h \
    enemy.h \
    collide.h \
    road.h \
    carrier.h

FORMS += \
        widget.ui \
    startwidget.ui

RESOURCES += \
    units.qrc \
    enemies.qrc \
    interface.qrc
