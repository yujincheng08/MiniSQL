CONFIG += console
CONFIG -= app_bundle

include(../MiniSQL.pri)

DESTDIR = ../

SOURCES += \
    main.cpp

TARGET = MiniSQL

HEADERS += \
    main.h

LIBS += -L.. -lAPI -lBufferManager -lInterpreter -lCatalogManager \
        -lRecordManager

CONFIG(test) {
}
