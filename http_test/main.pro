QT += widgets
QT += network
CONFIG += release
CONFIG += console
SOURCES += main.cc
TARGET = myapp.elf

QT += core network
win32 {
    LIBS += -LC:/OpenSSL-Win64/lib -lubsec
    INCLUDEPATH += C:/OpenSSL-Win64/include
}
