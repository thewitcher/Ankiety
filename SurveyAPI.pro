#-------------------------------------------------
#
# Project created by QtCreator 2013-04-16T21:48:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SurveyAPI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    add-question-dialog.cpp \
    edit-word-dialog.cpp

HEADERS  += mainwindow.h \
    add-question-dialog.h \
    edit-word-dialog.h

FORMS    += mainwindow.ui \
    add-question-dialog.ui \
    editworddialog.ui
