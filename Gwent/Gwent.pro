#-------------------------------------------------
#
# Project created by QtCreator 2017-08-29T21:04:18
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Gwent
TEMPLATE = app

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
    mainwindow.cpp \
    welcomeinterface.cpp \
    gameclient.cpp \
    mytcpsocket.cpp \
    homeinterface.cpp \
    player.cpp \
    editdeckinterface.cpp \
    cards/card.cpp \
    cards/deck.cpp \
    cards/cardlabelchoosedeck.cpp \
    cards/showcardsalldecks.cpp \
    cards/showcardsindeck.cpp \
    cards/cardlabeleditcards.cpp \
    waitbattleinterface.cpp \
    chooseforbattleinterface.cpp \
    battleinterface.cpp \
    scorelabel.cpp \
    cards/showbattlecard.cpp \
    cards/cardlabelinbattle.cpp \
    cards/placeholder.cpp \
    gameoverinterface.cpp

HEADERS += \
        mainwindow.h \
    welcomeinterface.h \
    gameclient.h \
    mytcpsocket.h \
    homeinterface.h \
    player.h \
    editdeckinterface.h \
    cards/card.h \
    cards/deck.h \
    cards/cardlabelchoosdeck.h \
    cards/showcardsalldecks.h \
    cards/showcardsindeck.h \
    cards/cardlabeleditcards.h \
    waitbattleinterface.h \
    chooseforbattleinterface.h \
    battleinterface.h \
    scorelabel.h \
    cards/showbattlecard.h \
    cards/cardlabelinbattle.h \
    cards/placeholder.h \
    gameoverinterface.h

FORMS += \
        mainwindow.ui

DISTFILES +=

RESOURCES += \
    res.qrc \
    cardimages2.qrc \
    cardimages.qrc
