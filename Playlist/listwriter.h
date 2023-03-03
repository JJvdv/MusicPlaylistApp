#ifndef LISTWRITER_H
#define LISTWRITER_H

#include <QString>

#include "musictablemodel.h"

class ListWriter
{
public:
    ListWriter(MusicTableModel *model);

    bool write(QString fileName = "playlist.txt");

private:
    MusicTableModel *mtm;
};

#endif // LISTWRITER_H
