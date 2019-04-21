#ifndef CONVERTER_LIST_MODEL_HH
#define CONVERTER_LIST_MODEL_HH

#include <QAbstractListModel>

class ConverterListModel: public QAbstractListModel {
    Q_OBJECT

public:
    ConverterListModel(QObject* parent);
    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
};


#endif /* CONVERTER_LIST_MODEL_HH */
