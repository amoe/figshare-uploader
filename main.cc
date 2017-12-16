#include <iostream>
#include <QApplication>
#include "view.hh"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    ViewImpl* view = new ViewImpl;

    view->show();

    return app.exec();
}
