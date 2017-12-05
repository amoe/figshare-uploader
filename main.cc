#include <iostream>
#include <QApplication>
#include "view.hh"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    Presenter presenter;
    View view(presenter);

    view.show();
    return app.exec();
}
