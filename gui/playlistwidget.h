#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QWidget>
#include <QList>
#include <QTableView>
#include <backend/playlistmodel.h>

class PlaylistWidget : public QTableView
{
    Q_OBJECT
public:
    explicit PlaylistWidget(QWidget *parent = nullptr);

public slots:
    void onModelUpdate();
    void updateSelectedFile();

protected slots:
    void onClicked(const QModelIndex &index);

};

#endif // PLAYLISTWIDGET_H
