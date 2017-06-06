TEMPLATE += lib
QT       -= gui

include(../../MiniSQL.pri)

TARGET = BufferManager
TEMPLATE = lib

DESTDIR = ../../

HEADERS += \
    Buffer.h \
    BufferManager.h \
    File.h \
    List.h \
    ListItem.h

SOURCES += \
    Buffer.cpp \
    BufferManager.cpp \
    File.cpp \
    List.cpp \
    ListItem.cpp

OTHER_FILES += \
    README.md

CONFIG(test) {
}
