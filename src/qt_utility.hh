#ifndef QT_UTILITY_HH
#define QT_UTILITY_HH

#include <QAbstractItemView>
#include <QAbstractItemModel>
#include <QContextMenuEvent>
#include <QModelIndex>
#include <QNetworkReply>

namespace qt_utility {
    void popEditors(QAbstractItemModel* model, QAbstractItemView* view);
    void handleHttpError(QString logPrefix, QNetworkReply* reply, QByteArray result);
    QString getDocumentsPath();
    QModelIndex indexOfEvent(QAbstractItemView* view, QContextMenuEvent* event);
    QJsonArray valueToArray(QJsonValue v);
    QJsonObject valueToObject(QJsonValue v);
    QJsonValue safeValue(QJsonObject object, string key);
}

#endif /* QT_UTILITY_HH */
