#include "listreader.h"
#include "filereader.h"
#include "music.h"

#include <QStringList>
#include <QString>
#include <QVariant>
#include <QDebug>

ListReader::ListReader()
{

}

QList<Music*> ListReader::read(QString fileName) const
{
    FileReader fr(fileName);
    QString inStr(fr.read().trimmed());

    QList<Music*> ml;

    if(inStr.isEmpty())
        return ml;

    QStringList inData(inStr.split("\n"));
    QStringList line;

    for (int i = 0; i < inData.size(); i++)
    {
       line = inData.at(i).split("#");

       //Using reflective Programming - Static Properties of Music class
       Music *music(new Music);

       music->setProperty("artist", line.at(0));
       music->setProperty("album", line.at(1));
       music->setProperty("name", line.at(2));
       music->setProperty("rating", line.at(3).toInt());

       ml.append(music);
    }

    return ml;
}
