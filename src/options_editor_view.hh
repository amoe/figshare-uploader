#ifndef OPTIONS_EDITOR_VIEW_HH
#define OPTIONS_EDITOR_VIEW_HH

#include <QTableView>
#include <QContextMenuEvent>
#include "options_editor_model.hh"


class OptionsEditorView: public QTableView {
    Q_OBJECT

public:
    OptionsEditorView(OptionsEditorModel* optionsEditorModel, QWidget* parent);
    void contextMenuEvent(QContextMenuEvent *event);

private:
    OptionsEditorModel* optionsEditorModel;
};

#endif /* OPTIONS_EDITOR_VIEW_HH */
