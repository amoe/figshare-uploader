#ifndef VIEW_HH
#define VIEW_HH

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QLineEdit>
#include "interfaces.hh"

class ViewImpl : public QWidget, public View {
    Q_OBJECT

public:
    ViewImpl(Presenter* presenter);

    std::string getSelectedFile();
    void addLog(std::string logText);
    void reportError(std::string errorText);
    void showFileDialog();

private:
    Presenter* presenter;
    QLineEdit* selectedFile;
    QLineEdit* token;
    QPushButton* actionButton;
    QPlainTextEdit* logger;
};

#endif // VIEW_HH
