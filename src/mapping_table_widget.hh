#ifndef MAPPING_TABLE_WIDGET_HH
#define MAPPING_TABLE_WIDGET_HH

#include <QWidget>
#include <QAbstractItemModel>

class MappingTableWidget: public QWidget {
    Q_OBJECT

public:
    MappingTableWidget(QAbstractItemModel* fieldEncoderModel, QWidget* parent);

private:
    QWidget* makeFirstGroup();
    QAbstractItemModel* fieldEncoderModel;
};

#endif /* MAPPING_TABLE_WIDGET_HH */
