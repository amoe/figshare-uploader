#include <QObject>
#include <QDebug>
#include <QWidget>
#include <QString>
#include <QGridLayout>
#include <QDebug>
#include <QPushButton>
#include "view.hh"
#include "presenter.hh"

void myFunction() {
    qDebug() << "just a normal function";
}


typedef void (Presenter::*PresenterSlot)(); //MyTypedef is a type!

// This is the long way round of writing a lambda expression.  Note the double
// parens to overload application.
class SlotAdapter {
public:
    SlotAdapter(Presenter* p, PresenterSlot f) : p(p), f(f) { }

    void operator()() const {
        // Call member function through the provided function pointer
        (p->*f)();
    }

    Presenter* p;
    PresenterSlot f;
};

ViewImpl::ViewImpl() : QWidget(0, Qt::Window) {
    presenter = new PresenterImpl(this);
    
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

    SlotAdapter slotAdapter(presenter, &Presenter::someSlot);

    connect(
        this->actionButton,
        &QPushButton::released,
        slotAdapter
    );
}

std::string ViewImpl::getSelectedFile() const {
    QString content = selectedFile->text();
    return content.toStdString();
}
