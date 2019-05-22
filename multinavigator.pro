#-------------------------------------------------
#
# Project created by QtCreator 2019-05-06T17:10:48
#
#-------------------------------------------------

QT += core gui multimedia multimediawidgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = librarian
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        gui/mainwindow.cpp \
    gui/centralwidget.cpp \
    gui/filterwidget/filterwidget.cpp \
    database/database.cpp \
    options/options.cpp \
    database/tagtable.cpp \
    database/filetable.cpp \
    database/filetagtable.cpp \
    database/file.cpp \
    database/filetag.cpp \
    database/tag.cpp \
    database/dirtable.cpp \
    database/dir.cpp \
    database/table.cpp \
    database/record.cpp \
    options/useroptions.cpp \
    options/textvalue.cpp \
    gui/filterwidget/tagwidget.cpp \
    gui/filterwidget/resizewidget.cpp \


HEADERS += \
        gui/mainwindow.h \
    gui/centralwidget.h \
    gui/filterwidget/filterwidget.h \
    gui/videowidget.h \
    database/database.h \
    options/options.h \
    database/table.h \
    database/tagtable.h \
    database/filetable.h \
    database/filetagtable.h \
    database/file.h \
    database/filetag.h \
    database/tag.h \
    database/dirtable.h \
    database/dir.h \
    database/record.h \
    options/useroptions.h \
    options/textvalue.h \
    gui/filterwidget/tagwidget.h \
    gui/filterwidget/resizewidget.h \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
