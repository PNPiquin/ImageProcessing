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
    SpatialFiltering/CommonSpatialFilters.cpp \
    SpatialFiltering/HistogramProcessor.cpp \
    SpatialFiltering/IntensityTransformation.cpp \
    SpatialFiltering/SpatialFilter.cpp \
    SpatialFiltering/statisticalspatialfilter.cpp \
    SpatialFiltering/unsharpmaskprocessor.cpp \
    ImageClasses/imagebundle.cpp \
    ImageClasses/imageholder.cpp \
    SpatialFiltering/cannyedgedetector.cpp \
    Segmentation/otsusegmentation.cpp \
    Segmentation/kmeans.cpp \
    ProgressLogger/progresslogger.cpp \
    Misc/resizeprocessor.cpp \
    Misc/differenceprocessor.cpp \
    IO/ImageIOManager.cpp \
    SpatialFiltering/morphgradient.cpp

HEADERS  += mainwindow.h \
    SpatialFiltering/CommonSpatialFilters.h \
    SpatialFiltering/HistogramProcessor.h \
    SpatialFiltering/IntensityTransformation.h \
    SpatialFiltering/SpatialFilter.h \
    SpatialFiltering/statisticalspatialfilter.h \
    SpatialFiltering/unsharpmaskprocessor.h \
    ImageClasses/imagebundle.h \
    ImageClasses/imageholder.h \
    SpatialFiltering/cannyedgedetector.h \
    Segmentation/otsusegmentation.h \
    Segmentation/kmeans.h \
    ProgressLogger/progresslogger.h \
    Misc/resizeprocessor.h \
    Misc/differenceprocessor.h \
    IO/ImageIOManager.h \
    SpatialFiltering/morphgradient.h

FORMS    += mainwindow.ui

win32 {
    INCLUDEPATH += C:/Boost/boost_1-58/include/boost-1_58
    INCLUDEPATH += C:/Eigen
    INCLUDEPATH += "C:\Program Files (x86)\GnuWin32\include"

    LIBS += -L"C:\Program Files (x86)\GnuWin32\lib" -ljpeg
    LIBS += -L"C:\Program Files (x86)\GnuWin32\lib" -lpng
    LIBS += -L"C:\Boost\boost_1-58\lib" -lboost_system-mgw53-mt-d-1_58
    LIBS += -L"C:\Boost\boost_1-58\lib" -lboost_filesystem-mgw53-mt-d-1_58
} unix {
    INCLUDEPATH += /usr/local/include
    INCLUDEPATH += /usr/local/include/eigen3

    LIBS += -L/usr/lib -ljpeg
    LIBS += -L/usr/lib -lpng
    LIBS += -L/usr/lib/x86_64-linux-gnu -lboost_system
    LIBS += -L/usr/lib/x86_64-linux-gnu -lboost_filesystem
}

QMAKE_CXXFLAGS += -Wall \
                -lboost_system \
                -std=gnu++11 \
                -O2 \
                -lboost_filesystem

DISTFILES += \
    LICENSE

