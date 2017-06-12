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
   win32:LIBS += "C:\Users\KitmanLai\Code\MiniSQL\libBufferManager.a"
}
else{
    TEMPLATE = lib
}
