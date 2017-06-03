TEMPLATE = app
CONFIG += console c++14 #warn_off
CONFIG -= app_bundle

SOURCES += \
    src/interpreter/scanner/Scanner.cpp \
    src/interpreter/Interpreter.cpp \
    src/bufferManager/Buffermanager.cpp \
    src/main.cpp \
    src/api/API.cpp \
    src/recordManager/RecordManager.cpp \
    src/catalogManager/CatalogManager.cpp \
    src/indexManager/IndexManager.cpp \
    src/bufferManager/Buffer.cpp \
    src/bufferManager/File.cpp \
    src/bufferManager/List.cpp \
    src/bufferManager/ListItem.cpp \
    src/interpreter/Action.cpp \
    src/interpreter/Column.cpp \
    src/interpreter/Constraint.cpp \
    src/interpreter/Condition.cpp \
    src/interpreter/parser/parser.cpp

HEADERS += \
    src/bufferManager/BufferManager.h \
    src/interpreter/scanner/Scanner.h \
    src/interpreter/scanner/Scanner.ih \
    src/interpreter/scanner/Scannerbase.h \
    src/interpreter/Interpreter.h \
    src/main.h \
    src/api/API.h \
    src/recordManager/RecordManager.h \
    src/catalogManager/CatalogManager.h \
    src/indexManager/IndexManager.h \
    src/bufferManager/Buffer.h \
    src/bufferManager/File.h \
    src/bufferManager/List.h \
    src/bufferManager/ListItem.h \
    src/interpreter/Action.h \
    src/interpreter/Column.h \
    src/interpreter/Constraint.h \
    src/interpreter/Condition.h \
    src/interpreter/parser/parser.h

OTHER_FILES += \
    src/interpreter/scanner/Scanner.l \
    src/interpreter/README.md \
    src/bufferManager/README.md
