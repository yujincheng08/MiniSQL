include(../../MiniSQL.pri)

TARGET = RecordManager

DESTDIR = ../../

HEADERS += \
    RecordManager.h

SOURCES += \
    RecordManager.cpp

OTHER_FILES += \
    README.md


CONFIG(test) {
    DEFINES += TEST
    TEMPLATE = app
    SOURCES += \
        test.cpp
   win32:LIBS += -L../../ -lbufferManager
}
else{
    TEMPLATE = lib
}
