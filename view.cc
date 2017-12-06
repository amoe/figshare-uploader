#include <QObject>
#include <QDebug>
#include <QWidget>
#include <QString>
#include <QGridLayout>
#include <QPushButton>
#include "view.hh"
#include "presenter.hh"

void myFunction() {
    qDebug() << "just a normal function";
}

// This is the long way round of writing a lambda expression.  Note the double
// parens to overload application.
class SlotAdapter {
public:
    void operator()() const {
        qDebug() << "within the functor";
    }
};

View::View(Presenter presenter) : QWidget(0, Qt::Window), presenter(presenter) {
    // layout MUST be allocated on the heap here, if it goes out of scope, it
    // will simply stop layout out the widgets properly!
    // But, I think that we don't need to clean it up because the QWidget
    // destructor will delete it at the appropriate time.
    QGridLayout* layout = new QGridLayout(this);

    this->selectedFile = new QLineEdit(this);
    layout->addWidget(this->selectedFile, 0, 0);

    this->actionButton = new QPushButton("Push me", this);
    layout->addWidget(this->actionButton, 1, 0);

    setLayout(layout);

    SlotAdapter slotAdapter;

    // connect(
    //     this->actionButton,
    //     &QPushButton::released,
    //     &presenter,
    //     &Presenter::someSlot
    // );
}

std::string View::getSelectedFile() const {
    QString content = selectedFile->text();
    return content.toStdString();
}
