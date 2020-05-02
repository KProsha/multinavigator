#include "playlistwidget.h"

#include <QHeaderView>

#include "backend/appglobal.h"

PlaylistWidget::PlaylistWidget(QWidget *parent) : QTableView(parent)
{
    setWordWrap(false);
    setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(AppGlobal::i(), &AppGlobal::sigNewCurrentPlayListModel, this, &PlaylistWidget::onModelUpdate);
    connect(this, &PlaylistWidget::clicked, this, &PlaylistWidget::onClicked);

    connect(AppGlobal::i(), &AppGlobal::sigNewCurrentFile, this, &PlaylistWidget::updateSelectedFile);
}
//------------------------------------------------------------------------------
void PlaylistWidget::updateSelectedFile()
{
    selectRow(AppGlobal::i()->getCurrentFileIndex());
}
//------------------------------------------------------------------------------
void PlaylistWidget::onModelUpdate()
{
    setModel(AppGlobal::i()->getCurrentPlayListModel());

    setColumnWidth(0, 500);
    setColumnWidth(1, 50);

    horizontalHeader()->setStretchLastSection(true);
}
//------------------------------------------------------------------------------
void PlaylistWidget::onClicked(const QModelIndex &index)
{
    bool ok;
    int fileId = index.data(Qt::UserRole).toInt(&ok);

    if(ok) AppGlobal::i()->setCurrentFileId(fileId);

}

//------------------------------------------------------------------------------
