TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS+=-lmariadbcpp -lredis++ -lhiredis -pthread


SOURCES += \
        cache.cpp \
        comment.cpp \
        commentbroker.cpp \
        commentinterface.cpp \
        commentproxy.cpp \
        jotting.cpp \
        jottingbroker.cpp \
        jottinginterface.cpp \
        jottingproxy.cpp \
        jottingsocialcontrol.cpp \
        main.cpp \
        material.cpp \
        materialbroker.cpp \
        materialinterface.cpp \
        materialproxy.cpp \
        netizen.cpp \
        netizenbroker.cpp \
        netizeninterface.cpp \
        netizenproxy.cpp \
        relationalbroker.cpp

HEADERS += \
    cache.h \
    comment.h \
    commentbroker.h \
    commentinterface.h \
    commentproxy.h \
    jotting.h \
    jottingbroker.h \
    jottinginterface.h \
    jottingproxy.h \
    jottingsocialcontrol.h \
    material.h \
    materialbroker.h \
    materialinterface.h \
    materialproxy.h \
    netizen.h \
    netizenbroker.h \
    netizeninterface.h \
    netizenproxy.h \
    relationalbroker.h \
    timeInfo.h
