#include "filereader.h"

#include <QFile>
#include <QTextStream>

FileReader::FileReader(QString fName)
{
    m_fileName = fName;
}

QString FileReader::read() const
{
    QFile inFile(m_fileName);

    if(!inFile.open(QIODevice::ReadOnly))
        return "";

    QTextStream inStream(&inFile);
    QString inStr(inFile.readAll());

    inFile.close();

    return inStr;
}
