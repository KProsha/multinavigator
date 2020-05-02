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

    bool getUseDirNameAsTag() const;
    void setUseDirNameAsTag(bool value);

    bool getUseFileNameAsTag() const;
    void setUseFileNameAsTag(bool value);

    int getFileNameCountForTag() const;
    void setFileNameCountForTag(int value);

    bool getUseNumbersAsTag() const;
    void setUseNumbersAsTag(bool value);

protected:
    QString recentDir;

    bool useDirNameAsTag;
    bool useFileNameAsTag;
    bool useNumbersAsTag;
    int fileNameCountForTag;

};

#endif // USEROPTIONS_H
