#ifndef USEROPTIONS_H
#define USEROPTIONS_H


#include <QSettings>

class UserOptions: public QSettings
{

public:
    UserOptions(const QString& fileName, QObject *parent = nullptr);

    void save();
    void load();

    const QString& getRecentDir() const;
    void setRecentDir(const QString &value);

protected:
    QString recentDir;
};

#endif // USEROPTIONS_H
