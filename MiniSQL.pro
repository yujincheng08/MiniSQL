TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += \
    src/interpreter/scanner/Scanner.cpp \
    src/interpreter/parser/logutils.c \
    src/interpreter/parser/parse.c \
    src/interpreter/Interpreter.cpp \
    src/bufferManager/Buffermanager.cpp \
    src/main.cpp \
    src/api/API.cpp \
    src/recordManager/CecordManager.cpp \
    src/catalogManager/CatalogManager.cpp \
    src/indexManager/IndexManager.cpp

HEADERS += \
    src/bufferManager/BufferManager.h \
    src/interpreter/parser/miniSqlDef.h \
    src/interpreter/parser/parse.h \
    src/interpreter/parser/test.h \
    src/interpreter/scanner/def.h \
    src/interpreter/scanner/Scanner.h \
    src/interpreter/scanner/Scanner.ih \
    src/interpreter/scanner/Scannerbase.h \
    src/interpreter/Interpreter.h \
    src/main.h \
    src/api/API.h \
    src/recordManager/RecordManager.h \
    src/catalogManager/CatalogManager.h \
    src/indexManager/IndexManager.h

    src/interpreter/Interpreter.h

OTHER_FILES += \
    src/interpreter/parser/parse.y \
    src/interpreter/scanner/Scanner.l
