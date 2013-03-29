TEMPLATE = app
TARGET = videowidget

QT += multimedia multimediawidgets

HEADERS = \
    videoplayer.h \
    sidebar.h \
    mainwindow.h

SOURCES = \
    main.cpp \
    videoplayer.cpp \
    sidebar.cpp \
    mainwindow.cpp

target.path = $$[QT_INSTALL_EXAMPLES]/multimediawidgets/videowidget
INSTALLS += target

QT+=widgets
