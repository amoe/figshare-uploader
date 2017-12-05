#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include "presenter.hh"

class View : public QWidget {
    Q_OBJECT

public:
    View(Presenter presenter);

    std::string getSelectedFile() const;

private:
    Presenter presenter;
    QLineEdit* selectedFile;
    QPushButton* actionButton;
};
