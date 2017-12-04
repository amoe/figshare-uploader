#include <iostream>
#include <gmock/gmock.h>
#include <QString>
#include <QIODevice>
#include <QCryptographicHash>
#include <QDebug>

using ::testing::Eq;



class QtWrapper {
public:
    static std::string toUpperCase(const std::string& input) {
        QString myString = QString::fromStdString(input);
        return myString.toUpper().toStdString();
    }; 
};

class QStringDevice : public QIODevice {
public:
    QStringDevice(QString source) {
        this->bytes = source.toUtf8();
    }

protected:
    qint64 readData(char *data, qint64 maxSize) {
        qDebug() << "memcpy was called";
        memcpy(data, this->bytes.constData(), maxSize);
    }

    qint64 writeData(const char *data, qint64 maxSize) {
        qFatal("unsupported operation");
    }

private:
    qint64 currentPosition = 0;
    QByteArray bytes;
};


TEST(QtWrapper, CanCalculateMD5) {
    QStringDevice stringDev(QString("my string"));
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(&stringDev);

    QByteArray result = hash.result();
    QString hexVersion(result.toHex());

    qDebug() << hexVersion;
}

TEST(QtWrapper, CanUseQtClasses) {
    ASSERT_THAT(QtWrapper::toUpperCase("hello world"), Eq("HELLO WORLD"));
}


int main(int argc, char **argv) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
