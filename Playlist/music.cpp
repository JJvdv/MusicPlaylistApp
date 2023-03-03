#include "music.h"

Music::Music()
{

}

Music::Music(QString a, QString al, QString sn, int r)
{
    m_artist = a;
    m_album = al;
    m_SongName = sn;
    m_rating = r;
}

QString Music::getArtist() const
{
    return m_artist;
}

void Music::setArtist(QString a)
{
    m_artist = a;
}

QString Music::getAlbum() const
{
    return m_album;
}

void Music::setAlbum(QString al)
{
    m_album = al;
}

QString Music::getName() const
{
    return m_SongName;
}

void Music::setName(QString sn)
{
    m_SongName = sn;
}

int Music::getRating() const
{
    return m_rating;
}

void Music::setRating(int r)
{
    m_rating = r;
}

QString Music::toString() const
{
    return QString("%1\n%2\n%3\n%4")
            .arg(m_artist)
            .arg(m_album)
            .arg(m_SongName)
            .arg(QString::number(m_rating));
}
