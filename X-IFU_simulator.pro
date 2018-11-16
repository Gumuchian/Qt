#-------------------------------------------------
#
# Project created by QtCreator 2018-02-04T22:26:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
CONFIG += c++11
TARGET = X-IFU_simulator
TEMPLATE = app
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp\
    mainwindow.cpp \
    channel.cpp \
    bbfb.cpp \
    butterworth.cpp \
    dds.cpp \
    pixel.cpp \
    pulse_generator.cpp \
    tes.cpp \
    cic.cpp \
    tinystr.cpp \
    tinyxml.cpp \
    tinyxmlerror.cpp \
    tinyxmlparser.cpp \
    xifu.cpp \
    config.cpp \
    global.cpp \
    importation.cpp \
    qcustomplot.cpp \
    truncation.cpp \
    dac.cpp \
    squid.cpp \
    adc.cpp \
    event_processor.cpp \
    fpa.cpp \
    instrument.cpp \
    dre.cpp \
    lna.cpp \
    simulation.cpp

HEADERS  += mainwindow.h \
    channel.h \
    ressources.h \
    bbfb.h \
    butterworth.h \
    dds.h \
    pixel.h \
    pulse_generator.h \
    tes.h \
    cic.h \
    global.h \
    tinystr.h \
    tinyxml.h \
    xifu.h \
    config.h \
    importation.h \
    qcustomplot.h \
    truncation.h \
    dac.h \
    squid.h \
    adc.h \
    event_processor.h \
    fpa.h \
    instrument.h \
    dre.h \
    lna.h \
    simulation.h

INCLUDEPATH += C:\Users\Paul\Downloads\Boost\boost_1_66_0
#INCLUDEPATH += /usr/local/Cellar/boost/1.66.0/include

FORMS    += mainwindow.ui \
    truncation.ui

RESOURCES += \
    ressources.qrc

