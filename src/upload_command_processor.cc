#include <iostream>
#include <QByteArray>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QNetworkReply>
#include "upload_command_processor.hh"
#include "logging.hh"

// This is a ring adapter class for communication with http.
// The thing to note is that this implements jbrains' ring idea, with the types
// being expressed as basic non-library types and converted to the library at
// the ring.

void UploadCommandProcessor::process(UploadCommand command) {
    spdlog::info("processing upload command, url = {}", command.getUrl());

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

    spdlog::info("size is now {}", theData.size());

    // Not clear that this should be here.
    request.setHeader(
        QNetworkRequest::ContentTypeHeader,
        "application/octet-stream"
    );

    spdlog::info("sending upload");

    QNetworkReply* reply = manager.put(request, theData);
    QEventLoop waitLoop;
    
    QObject::connect(
        reply, &QNetworkReply::finished, &waitLoop, &QEventLoop::quit
    );
    waitLoop.exec();

    spdlog::info("finished sending upload");

    QByteArray result = reply->readAll();
    qDebug() << result;
}
