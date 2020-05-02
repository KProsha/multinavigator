#ifndef PLAYLISTTABLE_H
#define PLAYLISTTABLE_H

#include "table.h"
#include "types/playlist.h"

namespace database {
//==============================================================================
class PlayListTable: public Table
{
public:
    PlayListTable(DataBase* dataBase);

    PlayList fromSqlQuery(QSharedPointer<QSqlQuery> query);
protected:
    QString getTableCreateQueryText() override;

};
//==============================================================================
}
#endif // PLAYLISTTABLE_H
