TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS+=-lmariadbcpp -pthread -lboost_system -lpthread -lboost_timer


SOURCES += \
        comment.cpp \
        commentbroker.cpp \
        commentinterface.cpp \
        commentproxy.cpp \
        jotting.cpp \
        jottingbroker.cpp \
        jottinginterface.cpp \
        jottingnotification.cpp \
        jottingproxy.cpp \
        jottingsocialcontrol.cpp \
        main.cpp \
        material.cpp \
        materialbroker.cpp \
        materialinterface.cpp \
        materialproxy.cpp \
        messagesequence.cpp \
        mytimer.cpp \
        netizen.cpp \
        netizenbroker.cpp \
        netizeninterface.cpp \
        netizenproxy.cpp \
        relationalbroker.cpp \
        snowflakeidworker.cpp

HEADERS += \
    comment.h \
    commentbroker.h \
    commentinterface.h \
    commentproxy.h \
    jotting.h \
    jottingbroker.h \
    jottinginterface.h \
    jottingnotification.h \
    jottingproxy.h \
    jottingsocialcontrol.h \
    material.h \
    materialbroker.h \
    materialinterface.h \
    materialproxy.h \
    messagesequence.h \
    mytimer.h \
    netizen.h \
    netizenbroker.h \
    netizeninterface.h \
    netizenproxy.h \
    relationalbroker.h \
    snowflake_noncopyable.h \
    snowflake_singleton.h \
    snowflakeidworker.h \
    timeInfo.h
