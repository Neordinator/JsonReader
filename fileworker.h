#ifndef FILEWORKER_H
#define FILEWORKER_H

#include <QFile>
#include <QTextStream>

#include "jsonreader.h"

class FileWorker : public QObject
{
    Q_OBJECT
    Q_PROPERTY(std::string bufferString READ getBufferString WRITE setBufferString NOTIFY bufferStringChanged)
public:
    explicit FileWorker(QObject *parent = nullptr);

    Q_INVOKABLE QString getFileName();
    Q_INVOKABLE std::string getBufferString();
    Q_INVOKABLE void writeFileData(std::string);
    void readFileData();

signals:
    void fileReaded();
    void fileWrited();
    void parseDataRequest();
    void bufferStringChanged();

public slots:
    Q_INVOKABLE void setToRead(QString);
    Q_INVOKABLE void setToWrite(QString);
    Q_INVOKABLE void setBufferString(std::string);

private:
    QString m_fileName;
    std::string m_bufferString;

};

#endif // FILEWORKER_H
