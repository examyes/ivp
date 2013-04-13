TEMPLATE = app
TARGET = ivp

QT += multimedia multimediawidgets

HEADERS = \
    MainWindow.h \
    MetaInfo.h \
    Overlay.h \
    VideoPlayer.h \
    MetaEntry.h \
    MetaItem.h \
    SideBar.h

SOURCES = \
    MainWindow.cpp \
    MetaInfo.cpp \
    SideBar.cpp \
    main.cpp \
    MetaEntry.cpp \
    MetaItem.cpp \
    VideoPlayer.cpp

QT += widgets
QT += xml
