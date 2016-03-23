#-------------------------------------------------
#
# Project created by QtCreator
#
#-------------------------------------------------

QT   += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataVisualizer
TEMPLATE = app


INCLUDEPATH += C:\Users\x86\Desktop\DataVisualizer\simpleDS
INCLUDEPATH += C:\Users\x86\Desktop\DataVisualizer\v2

SOURCES += main.cpp\
    mainwindow.cpp \
    visualizer.cpp \
    imgview.cpp \
    graph.cpp \
    simpleDS/bheap.cpp \
    simpleDS/queue.cpp \
    simpleDS/stack.cpp \
    graph_list.cpp \
    check.cpp \
    DG.cpp \
    showqianzhi.cpp

HEADERS  += mainwindow.h \
    simpleDS/bheap.h \
    simpleDS/queue.h \
    simpleDS/stack.h \
    visualizer.h \
    imgview.h \
    graph.h \
    graph_list.h \
    check.h \
    t2gv.h \
    DG.h \
    showqianzhi.h \
    shuzu.h

FORMS    += mainwindow.ui \
    imgview.ui \
    graph.ui \
    simpleDS/bheap.ui \
    simpleDS/queue.ui \
    simpleDS/stack.ui \
    check.ui \
    showqianzhi.ui

OTHER_FILES +=

RESOURCES += Res.qrc

RC_FILE = my.rc





