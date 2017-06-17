include(MiniSQL.pri)
TEMPLATE += lib
QT       -= gui

TARGET = API
TEMPLATE = lib

DESTDIR = ../../

LIBS += -L../../ -lBufferManager -lRecordManager -lIndexManager -lCatalogManager

HEADERS += \
    API.h

SOURCES += \
    API.cpp

OTHER_FILES += \
    README.md

CONFIG(test) {
}
