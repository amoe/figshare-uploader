#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include "fake_qt_core_application.hh"

const std::string fakeExecutableName = "my-test-program";

// Do a bunch of memory wrangling to make sure that qt stays around in tests

void bootQtEventLoop() {
    int* argc = getFakeArgc();
    char** argv = getFakeArgv();
    QCoreApplication* app = new QCoreApplication(*argc, argv);
    qDebug() << "booted event loop: " << app;
}


int* getFakeArgc() {
    int* argc = new int;
    *argc = 1;
    return argc;
}


char** getFakeArgv() {
    int procLen = fakeExecutableName.size();
    char* fakeExecutable = new char[procLen];
    fakeExecutableName.copy(fakeExecutable, procLen);
    char** argArray = new char*[1];
    argArray[0] = fakeExecutable;

    return argArray;
}
