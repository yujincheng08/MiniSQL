TEMPLATE += lib
QT       -= gui

include(../../MiniSQL.pri)

TARGET = BufferManager


DESTDIR = ../../

HEADERS += \
    RecordManager.h

SOURCES += \
    RecordManager.cpp

OTHER_FILES += \
    README.md

CONFIG(test) {
    DEFINES += TEST
    TEMPLATE = lib
    SOURCES += \
        test.cpp
}
else{
    TEMPLATE = app
}
