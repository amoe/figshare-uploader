#ifndef ABOUT_DIALOG_HH
#define ABOUT_DIALOG_HH

#include <QWidget>
#include <QDialog>

class AboutDialog: public QDialog {
    Q_OBJECT

public:
    AboutDialog(QWidget* parent);

private:
    QString getRichTextUrl(QString url) const;
};

#endif /* ABOUT_DIALOG_HH */
