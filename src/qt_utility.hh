#ifndef QT_UTILITY_HH
#define QT_UTILITY_HH

#include <QAbstractItemView>
#include <QAbstractItemModel>
#include <QNetworkReply>

namespace qt_utility {
    void popEditors(QAbstractItemModel* model, QAbstractItemView* view);
    void handleHttpError(QString logPrefix, QNetworkReply* reply, QByteArray result);
    QString getDocumentsPath();
}

#endif /* QT_UTILITY_HH */
