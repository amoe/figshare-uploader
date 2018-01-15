#include <string>
#include <QMessageLogger>
#include <QString>

void log_init() {
    QString pattern("%{type} - %{message}");
    qSetMessagePattern(pattern);
}
