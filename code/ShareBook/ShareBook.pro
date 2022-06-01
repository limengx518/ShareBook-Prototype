QT += quick


LIBS+=-lmariadbcpp -lredis++ -lhiredis -pthread

SOURCES += \
        main.cpp \
        personaluicontrol.cpp \
        roundimage.cpp\
        cache.cpp \
        jotting.cpp \
        jottingbroker.cpp \
        jottinginterface.cpp \
        jottingproxy.cpp \
        jottingsocialcontrol.cpp \
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
            relationalbroker.h
resources.files = main.qml 
resources.prefix = /$${TARGET}
RESOURCES += resources \
    res.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    PushPage.qml

HEADERS += \
    personaluicontrol.h \
    roundimage.h
