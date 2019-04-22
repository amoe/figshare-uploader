#ifndef MAPPING_TABLE_WIDGET_HH
#define MAPPING_TABLE_WIDGET_HH

#include <QWidget>
#include <QAbstractItemModel>
#include <QPushButton>

class MappingTableWidget: public QWidget {
    Q_OBJECT

public:
    MappingTableWidget(QAbstractItemModel* fieldEncoderModel, QAbstractItemModel* fieldMappingModel, QWidget* parent);

signals:
    void saveRequested();
    void loadRequested();

private:
    QWidget* makeFirstGroup();
    QAbstractItemModel* fieldEncoderModel;
    QAbstractItemModel* fieldMappingModel;

    QPushButton* saveButton;
    QPushButton* loadButton;
};

#endif /* MAPPING_TABLE_WIDGET_HH */
