include(../../MiniSQL.pri)
TEMPLATE += lib
QT       -= gui

TARGET = API
TEMPLATE = lib

DESTDIR = ../../

LIBS += -L../../ -lBufferManager -lRecordManager -lCatalogManager

HEADERS += \
    API.h \
    Types.h \
    BpTreeCtrl.h

SOURCES += \
    API.cpp \
    BpTreeCtrl.cpp

OTHER_FILES += \
    README.md

CONFIG(test) {
}
