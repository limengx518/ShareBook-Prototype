TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        broker.cpp \
        comment.cpp \
        commentbroker.cpp \
        jotting.cpp \
        jottingbroker.cpp \
        jottingsocialcontrol.cpp \
        main.cpp \
        material.cpp \
        materialbroker.cpp \
        netizen.cpp \
        netizenbroker.cpp

HEADERS += \
    broker.h \
    comment.h \
    commentbroker.h \
    jotting.h \
    jottingbroker.h \
    jottingsocialcontrol.h \
    material.h \
    materialbroker.h \
    netizen.h \
    netizenbroker.h

DISTFILES += \
    Fan_Interest.txt \
    jottingData.txt \
    materialData.txt \
    netizenData.txt
