#ifndef APPGLOBAL_H
#define APPGLOBAL_H

#include <QObject>

#include "database/database.h"
#include "options/options.h"
#include "options/useroptions.h"
#include "options/textvalue.h"
#include "playlistmodel.h"

class AppGlobal : public QObject
{
    Q_OBJECT
public:
    explicit AppGlobal(QObject *parent = nullptr);

    enum EAppState {
        StateFullScreen = 0x0,
        StatePlayList = 0x1,
        StateCreatePlayList = 0x2,
        StatePlayCustomPlayList = 0x4,
        StateVideo = 0x8
    };

    static AppGlobal* i();

    Options* getOptions() const;
    UserOptions* getUserOptions();
    QString getTextValue(const QString& key) const;

    database::DataBase* getDataBase();

    EAppState getState() const;
    EAppState getPastState() const;

    QString getRootDirPath() const;
    void setRootDirPath(const QString &value);
    void scanRootDir();

    int getCurrentFileId() const;
    void setCurrentFileId(int value);
    int getCurrentFileIndex() const;

    PlayListModel* getCurrentPlayListModel() const;
    void setCurrentAllPlayListModel();
    void setCurrentCustomPlayListModel();

    bool getRandomMode() const;
    bool getRepeatMode() const;

signals:
    void sigNewState(EAppState newState);
    void sigNewCurrentFile();
    void sigNewCurrentPlayListModel();

//    void sigNewRandomMode(bool);
    void sigNewRepeatMode(bool);

public slots:
    void setNewState(EAppState newState);
    void switchFullScreen();
    void setTagIdFilter(int id, database::Tag::ESelectionType type);
    void toggleRandomMode(bool b);
    void toggleRepeatMode();
    void moveForward();
    void moveBackward();

protected:
    static AppGlobal* inst;

    Options* optionsInst;
    UserOptions* userOptionsInst;
    QSharedPointer<TextValue> textValueInst;
    // -----  -----
    database::DataBase* dataBase;
    // -----  -----
    EAppState pastState;
    EAppState state;
    // -----  -----
    QString rootDirPath;
    // -----  -----
    PlayListModel* allPlayListModel;
    PlayListModel* customPlayListModel;
    PlayListModel* currentPlayListModel;
    // -----  -----

    bool randomMode;
    bool repeatMode;
};

#endif // APPGLOBAL_H
