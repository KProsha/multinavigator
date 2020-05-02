#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractTableModel>
#include <QList>

#include "database/database.h"

class PlayListModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit PlayListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    void setFilterTagIdList(const QList<int>& value);

    void moveForward(bool repeat, bool random);
    void moveBackward(bool repeat, bool random);

    int getCurrentFileId() const;
    void setCurrentFileId(int value);

    int getCurrentFileIndex() const;

public slots:
    void updatePlaylist();

signals:
    void sigNewCurrentFile();

protected:
    QList<database::File> fileList;
    QList<int> filterTagIdList;

    int currentFileId;

    int searchFileIndex(int fileId) const;

};

#endif // PLAYLISTMODEL_H
