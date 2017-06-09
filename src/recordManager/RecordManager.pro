include(../../MiniSQL.pri)

TARGET = RecordManager

DESTDIR = ../../

HEADERS += \
    RecordManager.h \
    record.h

SOURCES += \
    RecordManager.cpp \
    record.cpp

OTHER_FILES += \
    README.md

CONFIG(test) {
TEMPLATE = app
SOURCES += \
    test.cpp
}
else{
TEMPLATE = lib
}
