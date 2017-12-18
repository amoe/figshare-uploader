#ifndef VIEW_HH
#define VIEW_HH

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include "interfaces.hh"

class ViewImpl : public QWidget, public View {
    Q_OBJECT

public:
    ViewImpl(Presenter* presenter);

    std::string getSelectedFile() const;

private:
    Presenter* presenter;
    QLineEdit* selectedFile;
    QPushButton* actionButton;
};

#endif // VIEW_HH
