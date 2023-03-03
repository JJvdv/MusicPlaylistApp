#ifndef FILEREADER_H
#define FILEREADER_H

#include <QString>

class FileReader
{
public:
    FileReader(QString fName);
    QString read() const;

private:
    QString m_fileName;
};

#endif // FILEREADER_H
