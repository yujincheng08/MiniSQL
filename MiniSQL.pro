TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += main.cpp \
    src/interpreter/scanner/Scanner.cpp \
    src/interpreter/parser/logutils.c \
    src/interpreter/parser/parse.c \
    src/interpreter/Interpreter.cpp

HEADERS += \
    src/bufferManager/BufferManager.h \
    src/interpreter/parser/miniSqlDef.h \
    src/interpreter/parser/parse.h \
    src/interpreter/parser/test.h \
    src/interpreter/scanner/def.h \
    src/interpreter/scanner/Scanner.h \
    src/interpreter/scanner/Scanner.ih \
    src/interpreter/scanner/Scannerbase.h \
    src/interpreter/parser/parse.y \
    src/interpreter/Interpreter.h

OTHER_FILES += \
    src/interpreter/scanner/Scanner.l
