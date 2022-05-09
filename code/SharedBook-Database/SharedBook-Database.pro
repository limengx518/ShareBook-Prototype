QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    audio.cpp \
    comment.cpp \
    commentbroker.cpp \
    database.cpp \
    jotting.cpp \
    jottingbroker.cpp \
    jottingsocialcontrol.cpp \
    main.cpp \
    material.cpp \
    materialbroker.cpp \
    netizen.cpp \
    netizenbroker.cpp \
    picture.cpp \
    video.cpp

HEADERS += \
    audio.h \
    comment.h \
    commentbroker.h \
    database.h \
    jotting.h \
    jottingbroker.h \
    jottingsocialcontrol.h \
    material.h \
    materialbroker.h \
    netizen.h \
    netizenbroker.h \
    picture.h \
    video.h

TRANSLATIONS += \
    SharedBook-Database_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
