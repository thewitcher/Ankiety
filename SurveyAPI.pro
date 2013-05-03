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
    create-survey-dialog.cpp \
    Busines_classes/question.cpp \
    Busines_classes/open-question.cpp \
    Busines_classes/close-question.cpp \
    Busines_classes/available-answer.cpp \
    Busines_classes/key-word.cpp \
    Busines_classes/survey.cpp \
    Busines_classes/question-database.cpp \
    complete-survey-dialog.cpp \
    Busines_classes/survey-database.cpp \
    open-question-widget.cpp \
    close-question-widget.cpp

HEADERS  += mainwindow.h \
    add-question-dialog.h \
    create-survey-dialog.h \
    Busines_classes/question.h \
    Busines_classes/open-question.h \
    Busines_classes/close-question.h \
    Busines_classes/available-answer.h \
    Busines_classes/key-word.h \
    Busines_classes/survey.h \
    Busines_classes/question-database.h \
    complete-survey-dialog.h \
    Busines_classes/survey-database.h \
    open-question-widget.h \
    close-question-widget.h

FORMS    += mainwindow.ui \
    add-question-dialog.ui \
    create-survey-dialog.ui \
    complete-survey-dialog.ui
