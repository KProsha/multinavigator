#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QString>
#include <QMap>
#include <QSet>

class Dictionary
{
public:
    class EntryList{
    public:
        EntryList(){count = 0;}
        QSet<int> fileIdList;
        QSet<QString> similarTags;
        int count;
    };

    Dictionary();

    void clear();

    void addEntry(const QString& text, int fileId, bool splitText);

    QMap<QString, QSet<int> > getTagAndFileIds(int minWordCount);
protected:
    QMap<QString, EntryList> dictionaryData;



};

#endif // DICTIONARY_H
