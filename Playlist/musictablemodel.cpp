#include "musictablemodel.h"

#include <QColor>

MusicTableModel::MusicTableModel()
{

}

MusicTableModel::~MusicTableModel()
{
    qDeleteAll(musicList);
}

int MusicTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return musicList.size();
}

int MusicTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 4;
}

QVariant MusicTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }


    int col = index.column();
    int row = index.row();

    if (role == Qt::TextAlignmentRole) {

        switch(index.column()) {
            // Artist
            case 0:
                return int(Qt::AlignLeft | Qt::AlignVCenter);
                break;
            // Album
            case 1:
                return int(Qt::AlignLeft | Qt::AlignVCenter);
                break;
            // Song Name
            case 2:
                return int(Qt::AlignLeft | Qt::AlignVCenter);
                break;
            // Rating
            case 3:
                return int(Qt::AlignLeft | Qt::AlignVCenter);
                break;
            default:
                return int(Qt::AlignLeft | Qt::AlignVCenter);
        }
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch(col)
        {
            case 0:
                return musicList.at(row)->getArtist();
                break;
            case 1:
                return musicList.at(row)->getAlbum();
                break;
            case 2:
                return musicList.at(row)->getName();
                break;
            case 3:
                return QString::number(musicList.at(row)->getRating());
                break;
        }
    }

    if (role == Qt::BackgroundRole)
    {

         if (index.column() == 3)
         {

             if (musicList.at(row)->getRating() >= 7)
             {
                 return QVariant(QColor(Qt::green));
             }

             if (musicList.at(row)->getRating() < 7 && musicList.at(row)->getRating() >= 4)
             {
                 return QVariant(QColor(Qt::yellow));
             }

             if (musicList.at(row)->getRating() <= 3)
             {
                 return QVariant(QColor(Qt::red));
             }
         }
    }

    return QVariant();

}

QVariant MusicTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Vertical) {
        return QVariant();
    }

    switch (section) {
        case 0:
            return QString("Artist");
            break;
        case 1:
            return QString ("Album");
            break;
        case 2:
            return QString ("Song Name");
            break;
        case 3:
            return QString ("Rating");
            break;
        default:
            return QVariant();
    }

    return QVariant();
}

bool MusicTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid())
    {
        int col = index.column();
        int row = index.row();

        if (role == Qt::EditRole)
        {
            switch(col)
            {
                case 0:
                    musicList.at(row)->setArtist(value.toString());
                    break;
                case 1:
                    musicList.at(row)->setAlbum(value.toString());
                    break;
                case 2:
                    musicList.at(row)->setName(value.toString());
                    break;
                case 3:
                    musicList.at(row)->setRating(value.toInt());
                    break;
                default:
                    return false;
            }
        }

        emit dataChanged(index, index);
        return true;
    }

    return false;
}

Qt::ItemFlags MusicTableModel::flags(const QModelIndex &index) const
{
    if (index.isValid())
    {
        return (Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
    }
    else
    {
        return Qt::NoItemFlags;
    }
}

void MusicTableModel::addMusic(Music *music)
{
    int row = musicList.size();
    beginInsertRows(QModelIndex(), row, row);
    musicList.append(music);
    endInsertRows();
}

void MusicTableModel::clear()
{
    int row = musicList.size();
    beginRemoveRows(QModelIndex(), 0, row - 1);
    musicList.clear();
    qDeleteAll(musicList);
    endRemoveRows();
}
