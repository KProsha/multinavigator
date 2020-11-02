#include "dictionary.h"

#include <QRegularExpression>
#include "backend/appglobal.h"

Dictionary::Dictionary()
{

}
//------------------------------------------------------------------------------
void Dictionary::clear()
{
    dictionaryData.clear();
}
//------------------------------------------------------------------------------
void Dictionary::addEntry(const QString& text, int fileId, bool splitText)
{
    QSet<QString> tags;
    if(splitText){
        QString regExpText;
        if(AppGlobal::i()->getUserOptions()->getUseNumbersAsTag())
            regExpText = QStringLiteral("[\\(\\)\\s+\\.\\,\\_\\-\\]\\[]");
        else
            regExpText = QStringLiteral("[\\(\\)\\s+\\.\\,\\_\\-\\]\\[\\d]");

        QStringList words = text.toLower().split(QRegularExpression(regExpText), QString::SkipEmptyParts);
        for(int i = 0; i < words.size();){
            bool ok;
            words[i].toInt(&ok);
            if(!ok && (words[i].length() < 4)){
                words.removeAt(i);
            }else{
                ++i;
            }
        }

        for(int j = 2; j < words.size(); ++j){
            for(int i = 0; i <= words.size() - j; ++i){
                QStringList tagStringList = words.mid(i, j);
                tags.insert(tagStringList.join(' '));
            }
        }
//        tags.unite(words.toSet());  одиночные слова

    }else {
        tags.insert(text);
    }

    foreach(QString tag, tags){
        auto it = dictionaryData.find(tag);
        if(it == dictionaryData.end()) {
            EntryList entry;
            it = dictionaryData.insert(tag, entry);
        }
        it.value().fileIdList.insert(fileId);
        it.value().similarTags = tags;
        it.value().count++;
    }
}
//------------------------------------------------------------------------------
QMap<QString, QSet<int> > Dictionary::getTagAndFileIds(int minWordCount)
{
    QMap<QString, QSet<int> > res;

    QList<QSet<int> > usedSet;

    for(auto it = dictionaryData.begin(); it != dictionaryData.end(); ++it){
        if(it.value().count < minWordCount) continue;

        auto fileIdSet = it.value().fileIdList;
        auto similarTags = it.value().similarTags;

        auto useKey = [this, &fileIdSet, &similarTags](QString key)->bool{
            foreach(auto tagName,similarTags){
                if((tagName == key) || !dictionaryData.contains(tagName)) continue;
                if((dictionaryData[tagName].fileIdList == fileIdSet) &&
                    (tagName.size() > key.size())) return false;
            }
            return true;
        };

        if(!useKey(it.key())) continue;

        usedSet.append(fileIdSet);
        res[it.key()] = fileIdSet;
    }

    return res;
}
//------------------------------------------------------------------------------



