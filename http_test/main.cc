#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>

int main(int argc, char** argv) {
    qDebug() << "Starting up";
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    QWidget* centralWidget = new QWidget;
    QVBoxLayout* vbox = new QVBoxLayout(centralWidget);
    mainWindow.setCentralWidget(centralWidget);
    mainWindow.show();
    return app.exec();
}
