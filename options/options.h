#ifndef OPTIONS_H
#define OPTIONS_H

#include <QSettings>

class Options: public QSettings
{

public:
    Options(const QString& fileName, QObject *parent = nullptr);

    void load();
    QStringList getSuffixList() const;
    QString getDatabaseFileName() const;

protected:
    QStringList suffixList;
    QString databaseFileName;


};

#endif // OPTIONS_H
