include(../../MiniSQL.pri)

TARGET = BufferManager

DESTDIR = ../../

HEADERS += \
    Buffer.h \
    BufferManager.h \
    File.h \
    WriteThread.h \
    ReadThread.h \
    BufferList.h \
    BufferListItem.h

SOURCES += \
    Buffer.cpp \
    BufferManager.cpp \
    File.cpp \
    WriteThread.cpp \
    ReadThread.cpp \
    BufferList.cpp \
    BufferListItem.cpp

OTHER_FILES += \
    README.md

CONFIG(test) {
TEMPLATE = app
SOURCES += \
    test.cpp
}
else{
TEMPLATE += lib
}
