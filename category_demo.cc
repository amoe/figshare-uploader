#include <iostream>
#include "raw_literals.hh"
#include <QJsonDocument>
#include <QByteArray>
#include <QDebug>


int main() {
    std::cout << raw_literals::expectedResult << std::endl;

    QJsonDocument document = QJsonDocument::fromJson(
        QByteArray::fromStdString(
            raw_literals::expectedResult
        )
    );

}
