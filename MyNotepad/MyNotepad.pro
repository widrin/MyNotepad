#-------------------------------------------------
#
# Project created by QtCreator 2016-01-06T14:19:19
#
#-------------------------------------------------

QT       += core gui\
         multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyNotepad
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    about.cpp

HEADERS  += mainwindow.h \
    about.h

FORMS    += mainwindow.ui \
    about.ui

qtHaveModule(printsupport): QT += printsupport

RESOURCES += \
    icon.qrc \
    sound.qrc

RC_ICONS = "icon/write.ico"
