include(../../MiniSQL.pri)

TARGET = RecordManager

DESTDIR = ../../

HEADERS += \
    RecordManager.h

SOURCES += \
    RecordManager.cpp

OTHER_FILES += \
    README.md

TEMPLATE = lib

LIBS += -L../.. -lBufferManager

CONFIG(test) {
    DEFINES += TEST
    TEMPLATE = app
    SOURCES += \
        test.cpp
}
