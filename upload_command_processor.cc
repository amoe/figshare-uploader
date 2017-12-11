#include "upload_command_processor.hh"
#include <iostream>
#include <QByteArray>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QNetworkReply>

// This is a ring adapter class for communication with http.
// The thing to note is that this implements jbrains' ring idea, with the types
// being expressed as basic non-library types and converted to the library at
// the ring.

void UploadCommandProcessor::process(UploadCommand command) {
    std::cout << "processing command" << std::endl;
    std::cout << "url: "   << command.getUrl() << std::endl;

    // Convert everything into QT-layer.  In reality this is just one QT-specific
    // adapter, we could also use cpp-netlib etc.
    QNetworkAccessManager manager;
    QString urlString = QString::fromStdString(command.getUrl());
    QUrl theUrl(urlString);
    QNetworkRequest request(theUrl);

    std::vector<char> commandData = command.getData();
    int size = commandData.size();
    // initialize and zero the buffer
    QByteArray theData(size, 0);


    // Convert the data.
    for (int i = 0; i < size; i++) {
        // XXX: signedness?
        char charVersion = commandData[i];
        theData[i] = charVersion;
    }

    std::cout << "size is now " << theData.size() << std::endl;

    // Not clear that this should be here.
    request.setHeader(
        QNetworkRequest::ContentTypeHeader,
        "application/octet-stream"
    );

    std::cout << "sending" << std::endl;

    QNetworkReply* reply = manager.put(request, theData);
    QEventLoop waitLoop;
    
    QObject::connect(
        reply, &QNetworkReply::finished, &waitLoop, &QEventLoop::quit
    );
    waitLoop.exec();

    std::cout << "finished" << std::endl;

    QByteArray result = reply->readAll();
    qDebug() << result;
}
