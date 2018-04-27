#include <QCryptographicHash>
#include <QString>
#include <QDebug>
#include <QFile>
#include <iostream>
#include <cstring>

using std::string;

class DataSource {
public:
    virtual bool isReadable()  = 0;
    virtual bool isOpen() = 0;
    virtual bool atEnd() = 0;
    virtual qint64 read(char *data, qint64 maxSize) = 0;
};

class ByteArrayDataSource : public DataSource {
public:
    ByteArrayDataSource(QByteArray input) : source(input) {
    }
    
    bool isReadable() {
        return true;
    }

    bool isOpen() {
        return true;
    }

    bool atEnd() {
        return position == source.size();
    }
    

    qint64 read(char *data, qint64 maxSize) {
        QByteArray window = source.mid(position, maxSize);
        qint64 actuallyRead = window.size();
        memcpy(data, window.constData(), actuallyRead);
        this->position +=  actuallyRead;
        return actuallyRead;
    }
private:
    QByteArray source;
    qint64 position = 0;
};

class FileDataSource : public DataSource {
public:
    FileDataSource(std::string path) {
        theFile = new QFile(QString::fromStdString(path));
        bool isSuccess = theFile->open(QIODevice::ReadOnly);

        if (!isSuccess) {
            qFatal("unable to open file");
        }
    }
    ~FileDataSource() {
        delete theFile;
    }

    bool isReadable() {
        return theFile->isReadable();
    }

    bool isOpen() {
        return theFile->isOpen();
    }

    bool atEnd() {
        return theFile->atEnd();
    }
    
    qint64 read(char *data, qint64 maxSize) {
        qint64 result = theFile->read(data, maxSize);
        return result;
    }

private:
    QFile *theFile;
};

class MD5Calculator {
public:
    string getMD5(DataSource *source) {
        QCryptographicHash hash(QCryptographicHash::Md5);

        if (!source->isReadable())
            qFatal("something went wrong");
        if (!source->isOpen())
            qFatal("something went wrong");

        // this buffer is too large to allocate on the stack.
        char* buffer = new char[1048576];
        int length;

        while ((length = source->read(buffer,sizeof(buffer))) > 0)
            hash.addData(buffer,length);

        // Array form of delete
        delete[] buffer;

        qDebug() << "after loop";

        bool isAtEnd =  source->atEnd();

        if (!isAtEnd) 
            qFatal("something went wrong");

        return QString(hash.result().toHex()).toStdString();
    }
};
