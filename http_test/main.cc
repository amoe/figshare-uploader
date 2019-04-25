#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSslSocket>
#include <QDebug>

void dumpSslInformation() {
    qDebug() << "Supports SSL:" << QSslSocket::supportsSsl();
    qDebug() << "COMPILE TIME INFO:";
    qDebug() << "sslLibraryBuildVersionNumber:" << QSslSocket::sslLibraryBuildVersionNumber();
    qDebug() << "sslLibraryBuildVersionString:" << QSslSocket::sslLibraryBuildVersionString();
    qDebug() << "RUN TIME INFO:";
    qDebug() << "sslLibraryVersionNumber:" << QSslSocket::sslLibraryVersionNumber();
    qDebug() << "sslLibraryVersionString:" << QSslSocket::sslLibraryVersionString();
}

int main(int argc, char** argv) {
    qDebug() << "Starting up";
    QApplication app(argc, argv);
    dumpSslInformation();
    QMainWindow mainWindow;
    QWidget* centralWidget = new QWidget;
    QVBoxLayout* vbox = new QVBoxLayout(centralWidget);
    mainWindow.setCentralWidget(centralWidget);
    mainWindow.show();
    return app.exec();
}
