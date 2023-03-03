#include "filewriter.h"

#include <QFile>
#include <QTextStream>

FileWriter::FileWriter(QString fName)
{
    m_fileName = fName;
}

bool FileWriter::write(QString str) const
{
    QFile outFile(m_fileName);

    if(!outFile.open(QIODevice::WriteOnly))
        return false;

    QTextStream out(&outFile);

    out << str << endl;

    out.flush();

    outFile.close();

    return true;
}
