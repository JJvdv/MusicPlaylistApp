#include "listwriter.h"
#include "filewriter.h"

//#include <QMetaProperty>
//#include <QDebug>

ListWriter::ListWriter(MusicTableModel *model)
{
    mtm = model;
}

bool ListWriter::write(QString fileName)
{
    QString outStr;

    for (int i = 0; i < mtm->rowCount(QModelIndex()); i++)
    {
        outStr.append(QString("%1#%2#%3#%4")
                      .arg(mtm->data(mtm->index(i, 0), Qt::DisplayRole).toString())
                      .arg(mtm->data(mtm->index(i, 1), Qt::DisplayRole).toString())
                      .arg(mtm->data(mtm->index(i, 2), Qt::DisplayRole).toString())
                      .arg(mtm->data(mtm->index(i, 3), Qt::DisplayRole).toString())
                      );
    }

    FileWriter fw(fileName);

    if (!fw.write(outStr))
    {
        return false;
    }

    return true;
}
