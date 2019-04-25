#include <exception>
#include <stdexcept>
#include <QStandardPaths>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include "qt_utility.hh"
#include "logging.hh"

using std::runtime_error;

namespace qt_utility {
    void popEditors(QAbstractItemModel* model, QAbstractItemView* view) {
        for (int i = 0; i < model->rowCount(); i++) {
            for (int j = 0; j < model->columnCount(); j++) {
                QModelIndex index = model->index(i, j, QModelIndex());
                view->openPersistentEditor(index);
            }
        }
    }

    void handleHttpError(QString logPrefix, QNetworkReply* reply, QByteArray result) {
        QNetworkReply::NetworkError error = reply->error();

        // QString coercion;
        // QDebug coercer(&coercion);
        // coercer << error;
        // spdlog::info("error: {}", coercion.toStdString());

        spdlog::info("error: {}", error);
        spdlog::info("result: {}", result);

        if (error != QNetworkReply::NoError) {
            QString errorMessage;
            QDebug debugStream(&errorMessage);
            debugStream << logPrefix << error << "; content =" << QString::fromUtf8(result);
            throw std::runtime_error(errorMessage.toStdString());
        }
    }

    QString getDocumentsPath() {
        return QStandardPaths::standardLocations(
            QStandardPaths::DocumentsLocation
        ).first();
    }

    QModelIndex indexOfEvent(QAbstractItemView* view, QContextMenuEvent* event) {
        QPoint widgetPos = view->mapFromGlobal(event->globalPos());
        QModelIndex result = view->indexAt(widgetPos);
        qDebug() << "found index" << result;
        return result;
    }

    QJsonArray valueToArray(QJsonValue v) {
        if (!v.isArray()) {
            throw new runtime_error("unexpected non-array type");
        }

        return v.toArray();
    }

    QJsonObject valueToObject(QJsonValue v) {
        if (!v.isObject()) {
            throw new runtime_error("unexpected non-object type");
        }

        return v.toObject();
    }

    QString valueToString(QJsonValue v) {
        if (!v.isString()) {
            throw new runtime_error("unexpected non-string type");
        }

        return v.toString();
    }

    
    QJsonValue safeValue(QJsonObject object, QString key) {
        QJsonValue result = object.value(key);

        if (result.isUndefined()) {
            qDebug() << key;
            throw new runtime_error("unable to find key: " + key.toStdString());
        }

        return result;
    }

    const string qtStringToStdString(QString s) {
        return s.toStdString();
    }
}
