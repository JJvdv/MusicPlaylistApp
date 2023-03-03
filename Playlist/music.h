#ifndef MUSIC_H
#define MUSIC_H

#include <QObject>

class Music : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString artist READ getArtist WRITE setArtist)
    Q_PROPERTY(QString album READ getAlbum WRITE setAlbum)
    Q_PROPERTY(QString name READ getName WRITE setName)
    Q_PROPERTY(int rating READ getRating WRITE setRating)

public:
    Music();
    Music(QString a, QString al, QString sn, int r);

    QString getArtist() const;
    void setArtist(QString a);

    QString getAlbum() const;
    void setAlbum(QString al);

    QString getName() const;
    void setName(QString sn);

    int getRating() const;
    void setRating(int r);

    QString toString() const;

private:
    QString m_artist, m_album, m_SongName;
    int m_rating;
};

#endif // MUSIC_H
