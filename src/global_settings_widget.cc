#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QCheckBox>
#include "global_settings_widget.hh"

GlobalSettingsWidget::GlobalSettingsWidget(
    QWidget* parent
): QWidget(parent) {
    QGridLayout* grid = new QGridLayout(this);
    
    QWidget* useStaging = new QCheckBox("Use staging environment", this);
    grid->setSpacing(16);
    grid->addWidget(useStaging, 0, 0, Qt::AlignTop);
    
    setWindowTitle("Global settings");
}
