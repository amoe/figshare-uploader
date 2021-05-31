#ifndef GLOBAL_SETTINGS_WIDGET_HH
#define GLOBAL_SETTINGS_WIDGET_HH

#include <QWidget>
#include <QAbstractItemModel>
#include <QPushButton>

class GlobalSettingsWidget: public QWidget {
    Q_OBJECT

signals:
    void useStagingModified();

public:
    GlobalSettingsWidget(QWidget* parent);
};


#endif /* GLOBAL_SETTINGS_WIDGET_HH */
