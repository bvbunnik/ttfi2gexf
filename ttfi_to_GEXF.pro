#-------------------------------------------------
#
# Project created by QtCreator 2017-10-16T15:31:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ttfi_to_GEXF
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    Csv.cpp \
    libgexf/attributeiter.cpp \
    libgexf/attvalueiter.cpp \
    libgexf/conv.cpp \
    libgexf/data.cpp \
    libgexf/directedgraph.cpp \
    libgexf/dynamicgraph.cpp \
    libgexf/edgeiter.cpp \
    libgexf/filereader.cpp \
    libgexf/filewriter.cpp \
    libgexf/gexf.cpp \
    libgexf/gexfparser.cpp \
    libgexf/graph.cpp \
    libgexf/legacyparser.cpp \
    libgexf/legacywriter.cpp \
    libgexf/memoryvalidator.cpp \
    libgexf/metadata.cpp \
    libgexf/nodeiter.cpp \
    libgexf/rngvalidator.cpp \
    libgexf/schemavalidator.cpp \
    libgexf/undirectedgraph.cpp

HEADERS  += mainwindow.h \
    Csv.h \
    libgexf/abstractiter.h \
    libgexf/abstractparser.h \
    libgexf/attributeiter.h \
    libgexf/attvalueiter.h \
    libgexf/conv.h \
    libgexf/data.h \
    libgexf/directedgraph.h \
    libgexf/dynamicgraph.h \
    libgexf/edgeiter.h \
    libgexf/exceptions.h \
    libgexf/filereader.h \
    libgexf/filewriter.h \
    libgexf/gexf.h \
    libgexf/gexfparser.h \
    libgexf/graph.h \
    libgexf/legacyparser.h \
    libgexf/legacywriter.h \
    libgexf/libgexf.h \
    libgexf/memoryvalidator.h \
    libgexf/metadata.h \
    libgexf/nodeiter.h \
    libgexf/rngvalidator.h \
    libgexf/schemavalidator.h \
    libgexf/typedefs.h \
    libgexf/undirectedgraph.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/include/libxml2
LIBS += -lxml2
