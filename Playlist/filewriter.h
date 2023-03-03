#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <QString>

class FileWriter
{
public:
    FileWriter(QString fName);

    bool write(QString str) const;

private:
    QString m_fileName;
};

#endif // FILEWRITER_H
