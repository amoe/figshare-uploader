#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QCheckBox>
#include "global_settings_widget.hh"

GlobalSettingsWidget::GlobalSettingsWidget(
    QWidget* parent
): QWidget(parent) {
    QGridLayout* grid = new QGridLayout(this);
    
    QCheckBox* useStaging = new QCheckBox("Use staging environment", this);

    // TODO: use setChecked to reflect value based on model.
    
    grid->setSpacing(16);
    grid->addWidget(useStaging, 0, 0, Qt::AlignTop);

    connect(
        useStaging, &QCheckBox::stateChanged,
        this, &GlobalSettingsWidget::useStagingModified
    );
    
    setWindowTitle("Global settings");
}
