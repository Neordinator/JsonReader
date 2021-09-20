#include "fileworker.h"

FileWorker::FileWorker(QObject *parent) : QObject(parent), m_fileName("O:\\TestTasks\\for_Innopolis\\build-JsonReaderApp-Desktop_Qt_6_2_0_MinGW_64_bit-Debug\\test.json")
{

}

QString FileWorker::getFileName()
{
    return m_fileName;
}

std::string FileWorker::getBufferString()
{
    return m_bufferString;
}

void FileWorker::writeFileData(std::string jsonDoc)
{
    QFile mFile(m_fileName);
    if(!mFile.open(QFile::WriteOnly | QFile::Text)){
        qDebug() << "Could not open file for writing";
        return;
    }
    QTextStream out(&mFile);
    for(unsigned int i = 0; i < jsonDoc.size(); i++){
        out << jsonDoc[i];
    }
    emit fileWrited();
    mFile.flush();
    mFile.close();
}

void FileWorker::readFileData()
{
    QFile mFile(m_fileName);
    if(!mFile.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "Could not open file for reading";
        return;
    }
    QTextStream in(&mFile);
    QString mText = in.readAll();
    mFile.close();
    FileWorker::setBufferString(mText.toStdString());//readJson(std::string)
    emit fileReaded();
}

void FileWorker::setToRead(QString newFileName)
{
    if(newFileName.contains("file:///"))
        newFileName.remove(0, 8); // delete "file:///" from directory
    if (m_fileName != newFileName){
        m_fileName = newFileName;
    }
    FileWorker::readFileData();
}
void FileWorker::setToWrite(QString newFileName)
{
    if(newFileName.contains("file:///"))
        newFileName.remove(0, 8); // delete "file:///" from directory
    if (m_fileName != newFileName){
        m_fileName = newFileName;
    }
    emit parseDataRequest();
}

void FileWorker::setBufferString(std::string newBufferString)
{
    if (m_bufferString != newBufferString)
    {
        m_bufferString = newBufferString;
        emit bufferStringChanged();
    }
}
