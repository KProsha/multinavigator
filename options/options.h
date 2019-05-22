#ifndef OPTIONS_H
#define OPTIONS_H

#include <QSettings>

class Options: public QSettings
{



public:
    Options(const QString& fileName, QObject *parent = nullptr);

    static Options* i;

    QString databaseFileName;

    QStringList suffixList;

    void load();
};

#endif // OPTIONS_H
