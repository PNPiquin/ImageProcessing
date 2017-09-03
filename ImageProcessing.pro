#-------------------------------------------------
#
# Project created by QtCreator 2017-08-18T23:23:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageProcessing
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    JpegManager.cpp \
    imageholder.cpp \
    imagebundle.cpp \
    SpatialFiltering/CommonSpatialFilters.cpp \
    SpatialFiltering/HistogramProcessor.cpp \
    SpatialFiltering/IntensityTransformation.cpp \
    SpatialFiltering/SpatialFilter.cpp \
    SpatialFiltering/statisticalspatialfilter.cpp \
    SpatialFiltering/unsharpmaskprocessor.cpp

HEADERS  += mainwindow.h \
    JpegManager.h \
    imageholder.h \
    imagebundle.h \
    SpatialFiltering/CommonSpatialFilters.h \
    SpatialFiltering/HistogramProcessor.h \
    SpatialFiltering/IntensityTransformation.h \
    SpatialFiltering/SpatialFilter.h \
    SpatialFiltering/statisticalspatialfilter.h \
    SpatialFiltering/unsharpmaskprocessor.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -Wall \
                 -lboost_system \
                 -std=gnu++11 \
                 -O2 \
                -lboost_filesystem

LIBS += -L/usr/lib -ljpeg
LIBS += -L/usr/lib/x86_64-linux-gnu -lboost_system
LIBS += -L/usr/lib/x86_64-linux-gnu -lboost_filesystem
