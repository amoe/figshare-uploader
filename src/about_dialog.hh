#ifndef ABOUT_DIALOG_HH
#define ABOUT_DIALOG_HH

#include <QWidget>
#include <QDialog>

class AboutDialog: public QDialog {
    Q_OBJECT

public:
    AboutDialog(QWidget* parent);
};

#endif /* ABOUT_DIALOG_HH */
