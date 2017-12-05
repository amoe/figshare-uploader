#include <QObject>
#include <QWidget>
#include <QLineEdit>


class View : public QWidget {
    Q_OBJECT

public:
    View();

    std::string getSelectedFile() const;

private:
    QLineEdit *selectedFile;
};
