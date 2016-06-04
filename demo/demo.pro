#-------------------------------------------------
#
# Project created by QtCreator 2016-06-03T18:55:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demo
TEMPLATE = app


SOURCES += main.cpp \
    base/basedialog.cpp \
    base/paramdata.cpp \
    base/systembase.cpp \
    component/imagelabel.cpp \
    component/inputedit.cpp \
    parameter/filelistdialog.cpp \
    parameter/keyboarddialog.cpp \
    parameter/numberdialog.cpp \
    parameter/paramdialog.cpp \
    process/processdialog.cpp \
    maindialog.cpp \
    qextserialport/posix_qextserialport.cpp \
    qextserialport/qextserialbase.cpp

HEADERS  += \
    base/basedialog.h \
    base/paramdata.h \
    base/systembase.h \
    component/imagelabel.h \
    component/inputedit.h \
    parameter/filelistdialog.h \
    parameter/keyboarddialog.h \
    parameter/numberdialog.h \
    parameter/paramdialog.h \
    process/processdialog.h \
    maindialog.h \
    qextserialport/posix_qextserialport.h \
    qextserialport/qextserialbase.h

FORMS    += \
    maindialog.ui \
    base/basedialog.ui \
    parameter/filelistdialog.ui \
    parameter/keyboarddialog.ui \
    parameter/numberdialog.ui \
    parameter/paramdialog.ui \
    process/processdialog.ui

RESOURCES += \
    ../resource/resrc.qrc
