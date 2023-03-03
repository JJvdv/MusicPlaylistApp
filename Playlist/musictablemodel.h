#ifndef MUSICTABLEMODEL_H
#define MUSICTABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>

#include "music.h"

class MusicTableModel : public QAbstractTableModel
{
public:
    MusicTableModel();
    ~MusicTableModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void addMusic(Music *music);
    void clear();

private:
    QList<Music*> musicList;
};

#endif // MUSICTABLEMODEL_H
