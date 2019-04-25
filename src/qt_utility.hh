#ifndef QT_UTILITY_HH
#define QT_UTILITY_HH

#include <QAbstractItemView>
#include <QAbstractItemModel>
#include <QContextMenuEvent>
#include <QModelIndex>
#include <QNetworkReply>
#include <string>

using std::string;

namespace qt_utility {
    void popEditors(QAbstractItemModel* model, QAbstractItemView* view);
    void handleHttpError(QString logPrefix, QNetworkReply* reply, QByteArray result);
    QString getDocumentsPath();
    QModelIndex indexOfEvent(QAbstractItemView* view, QContextMenuEvent* event);
    QJsonArray valueToArray(QJsonValue v);
    QJsonObject valueToObject(QJsonValue v);
    QString valueToString(QJsonValue v);
    QJsonValue safeValue(QJsonObject object, QString key);
    const string qtStringToStdString(QString s); 
    
    // function alias, this is for use with spdlog.
    const auto QS = qtStringToStdString;
}

#endif /* QT_UTILITY_HH */
