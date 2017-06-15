include(../../MiniSQL.pri)

TEMPLATE = lib

TARGET = CatalogManager

DESTDIR = ../../

HEADERS += \
    CatalogManager.h

SOURCES += \
    CatalogManager.cpp

OTHER_FILES += \
    README.md

CONFIG(test) {
    TEMPLATE = app
}
