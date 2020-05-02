#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QString>

namespace database {
//==============================================================================
class PlayList
{
public:
    PlayList();

    QString getName() const;
    void setName(const QString& value);

    QString getComment() const;
    void setComment(const QString& value);

protected:
    QString name;
    QString comment;


};
//==============================================================================
}
#endif // PLAYLIST_H
