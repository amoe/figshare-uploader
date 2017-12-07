#include <QCoreApplication>
#include <iostream>

const std::string fakeExecutableName = "my-test-program";

static int* getFakeArgc();
static char** getFakeArgv();

// Do a bunch of memory wrangling to make sure that qt stays around in tests

void bootQtEventLoop() {
    int* argc = getFakeArgc();
    char** argv = getFakeArgv();
    QCoreApplication* app = new QCoreApplication(*argc, argv);
}


static int* getFakeArgc() {
    int* argc = new int;
    *argc = 1;
    return argc;
}


static char** getFakeArgv() {
    int procLen = fakeExecutableName.size();
    char* fakeExecutable = new char[procLen];
    fakeExecutableName.copy(fakeExecutable, procLen);
    char** argArray = new char*[1];
    argArray[0] = fakeExecutable;

    return argArray;
}
