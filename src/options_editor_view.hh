#ifndef OPTIONS_EDITOR_VIEW_HH
#define OPTIONS_EDITOR_VIEW_HH

#include <QTableView>
#include <QContextMenuEvent>

class OptionsEditorView: public QTableView {
    Q_OBJECT

public:
    OptionsEditorView(QWidget* parent);
    void contextMenuEvent(QContextMenuEvent *event);
};

#endif /* OPTIONS_EDITOR_VIEW_HH */
