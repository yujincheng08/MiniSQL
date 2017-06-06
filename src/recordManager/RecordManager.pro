TEMPLATE += lib
QT       -= gui

include(../../MiniSQL.pri)

TARGET = BufferManager
TEMPLATE = lib

DESTDIR = ../../

HEADERS += \
    RecordManager.h

SOURCES += \
    RecordManager.cpp

OTHER_FILES += \
    README.md

CONFIG(test) {
    DEFINES += TEST
}
