
    QT       += core
    QT -= gui
    CONFIG += c++11 (Qt5)

    greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

    TARGET = lab8
    CONFIG += console
    CONFIG -= app_bundle

    TEMPLATE = app

SOURCES += tcp_client.cpp\
    tcp_server.cpp \
    main.cpp \
    places.cpp


#    unix:!macx: LIBS += -L$$PWD/../../../../../../../usr/local/lib/ -lprogbase-cpp

#    INCLUDEPATH += $$PWD/../../../../../../../usr/local/include
#    DEPENDPATH += $$PWD/../../../../../../../usr/local/include

#    unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../../../usr/local/lib/libprogbase-cpp.a

#    unix:!macx: LIBS += -L$$PWD/../../../../../../../usr/local/lib/ -lprogbase

#    INCLUDEPATH += $$PWD/../../../../../../../usr/local/include
#    DEPENDPATH += $$PWD/../../../../../../../usr/local/include

#    unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../../../usr/local/lib/libprogbase.a

#    unix:!macx: LIBS += -lssl

HEADERS += \
    places.h \
    tcp_server.h \
    tcp_client.h

RESOURCES += \
    data.qrc
