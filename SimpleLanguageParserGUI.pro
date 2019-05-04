#-------------------------------------------------
#
# Project created by QtCreator 2018-11-08T13:12:01
#
#-------------------------------------------------

QT += core gui widgets

TARGET = SimpleLanguageParserGUI
TEMPLATE = app

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

INCLUDEPATH += SimpleLanguageParser/
INCLUDEPATH += SimpleLanguageParser/ASTree
INCLUDEPATH += SimpleLanguageParser/LexicalAnalyzer/
INCLUDEPATH += SimpleLanguageParser/LexicalAnalyzer/LexicalParserBase/
INCLUDEPATH += SimpleLanguageParser/SyntacticAnalyzerRecursiveDown/
INCLUDEPATH += SimpleLanguageParser/SyntacticAnalyzerRecursiveDown/SyntacticalParserBase/

SOURCES += \
        main.cpp \
        MainWindow/mainwindow.cpp \
    SimpleLanguageParser/LexicalAnalyzer/LexicalParserBase/lexicalparserbase.cpp \
    SimpleLanguageParser/LexicalAnalyzer/lexicalanalyzer.cpp \
    SimpleLanguageParser/SyntacticAnalyzerRecursiveDown/SyntacticalParserBase/syntacticalparserbase.cpp \
    SimpleLanguageParser/SyntacticAnalyzerRecursiveDown/syntacticalanalyzer.cpp \
    SimpleLanguageParser/ASTree/astnode.cpp \
    SimpleLanguageParser/gorodlangexception.cpp \
    SimpleLanguageParser/gorodlangtokens.cpp \
    SimpleLanguageParser/SyntacticAnalyzerRecursiveDown/reversepolishnotationbuilder.cpp \
    SimpleLanguageParser/Executor/executor.cpp

HEADERS += \
        MainWindow/mainwindow.h \
    main.h \
    SimpleLanguageParser/LexicalAnalyzer/LexicalParserBase/lexicalparserbase.h \
    SimpleLanguageParser/LexicalAnalyzer/lexicalanalyzer.h \
    SimpleLanguageParser/SyntacticAnalyzerRecursiveDown/SyntacticalParserBase/syntacticalparserbase.h \
    SimpleLanguageParser/SyntacticAnalyzerRecursiveDown/syntacticalanalyzer.h \
    SimpleLanguageParser/ASTree/astnode.h \
    SimpleLanguageParser/gorodlangexception.h \
    SimpleLanguageParser/gorodlangtokens.h \
    SimpleLanguageParser/SyntacticAnalyzerRecursiveDown/reversepolishnotationbuilder.h \
    SimpleLanguageParser/Executor/executor.h

DESTDIR = build/
OBJECTS_DIR = obj/
MOC_DIR     = moc/
UI_DIR      = ui/

FORMS += \
        MainWindow/mainwindow.ui

RESOURCES += \
    res.qrc

