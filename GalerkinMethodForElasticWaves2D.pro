TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Solver.cpp \
    Triangle.cpp \
    SystemMaker.cpp \
    Support.cpp \
    FileWriter.cpp \
    Rectangle.cpp \
    TriangleMesh.cpp \
    RectangleMesh.cpp \
    SourceWrapper.cpp \
    SystemSolver.cpp \
    ProblemSolver.cpp

HEADERS += \
    Solver.h \
    Triangle.h \
    SystemMaker.h \
    Support.h \
    FileWriter.h \
    Rectangle.h \
    TriangleMesh.h \
    RectangleMesh.h \
    SourceWrapper.h \
    SystemSolver.h \
    ProblemSolver.h

INCLUDEPATH += /home/bobo/boost/boost_1_62_0/
