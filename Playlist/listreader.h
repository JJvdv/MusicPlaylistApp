#ifndef LISTREADER_H
#define LISTREADER_H

#include <QString>

class Music;

class ListReader
{
public:
    ListReader();
    QList<Music*> read(QString fileName = "Playlist.txt") const;
};

#endif // LISTREADER_H
