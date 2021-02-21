
QT += core gui multimedia multimediawidgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = multinavigator
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

DESTDIR = $${PWD}/bin

SOURCES += \
        main.cpp \
        gui/mainwindow.cpp \
    gui/centralwidget.cpp \
    database/database.cpp \
    options/options.cpp \
    database/tagtable.cpp \
    database/filetable.cpp \
    database/filetagtable.cpp \
    database/dirtable.cpp \
    database/table.cpp \
    options/useroptions.cpp \
    options/textvalue.cpp \
    gui/taglistwidget/filetaggroupwidget.cpp \
    backend/appglobal.cpp \
    gui/taglistwidget/playlisttaggroupwidget.cpp \
    gui/widgets/listviewwidget.cpp \
    gui/taglistwidget/taglistgroupwidget.cpp \
    gui/playlistwidget.cpp \
    backend/playlistmodel.cpp \
    gui/controlwidget.cpp \
    gui/progressbarcontroller.cpp \
    gui/videowidget.cpp \
    gui/playlistmanager.cpp \
    database/types/dir.cpp \
    database/types/file.cpp \
    database/types/tag.cpp \
    database/types/filetag.cpp \
    database/types/playlist.cpp \
    database/types/fileplaylist.cpp \
    database/playlisttable.cpp \
    database/fileplaylisttable.cpp \
    gui/scanoptionswidget.cpp \
    backend/dictionary.cpp \
    gui/taglistwidget/edittaglistwidget.cpp \
    gui/taggroup/edittaggrouplistwidget.cpp \
    gui/taggroup/edittaggroupwidget.cpp \
    gui/tagwidget/edittagwidget.cpp \
    gui/tagwidget/playtagwidget.cpp \
    gui/tagwidget/filetagwidget.cpp \
    gui/edittagdialog.cpp \
    database/types/taggroup.cpp \
    database/types/taggrouptag.cpp \
    database/taggrouptable.cpp \
    database/taggrouptagtable.cpp \
    gui/edittaggrouptab.cpp \
    gui/edittagtab.cpp

HEADERS += \
        gui/mainwindow.h \
    gui/centralwidget.h \
    gui/videowidget.h \
    database/database.h \
    options/options.h \
    database/table.h \
    database/tagtable.h \
    database/filetable.h \
    database/filetagtable.h \
    database/types/file.h \
    database/types/filetag.h \
    database/types/tag.h \
    database/dirtable.h \
    database/types/dir.h \
    options/useroptions.h \
    options/textvalue.h \
    gui/taglistwidget/filetaggroupwidget.h \
    backend/appglobal.h \
    gui/taglistwidget/playlisttaggroupwidget.h \
    gui/widgets/listviewwidget.h \
    gui/taglistwidget/taglistgroupwidget.h \
    gui/playlistwidget.h \
    backend/playlistmodel.h \
    gui/controlwidget.h \
    gui/progressbarcontroller.h \
    gui/playlistmanager.h \
    database/types/playlist.h \
    database/types/fileplaylist.h \
    database/playlisttable.h \
    database/fileplaylisttable.h \
    gui/scanoptionswidget.h \
    backend/dictionary.h \
    gui/taglistwidget/edittaglistwidget.h \
    gui/taggroup/edittaggrouplistwidget.h \
    gui/taggroup/edittaggroupwidget.h \
    gui/tagwidget/edittagwidget.h \
    gui/tagwidget/playtagwidget.h \
    gui/tagwidget/filetagwidget.h \
    gui/edittagdialog.h \
    database/types/taggroup.h \
    database/types/taggrouptag.h \
    database/taggrouptable.h \
    database/taggrouptagtable.h \
    gui/taglistwidget/taglistwidget.h \
    gui/widgets/idwidget.h \
    gui/edittaggrouptab.h \
    gui/edittagtab.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
