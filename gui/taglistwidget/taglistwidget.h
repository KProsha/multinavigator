#ifndef TAGLISTWIDGET_H
#define TAGLISTWIDGET_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>

#include <gui/tagwidget/tagwidget.h>
#include <database/types/tag.h>

class TagListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TagListWidget(QWidget *parent = nullptr);

public slots:
    void updateAvaliableTag();

protected slots:
    void onTagClicked(int tagId);

protected:
    QVBoxLayout* tagLayout;

    QWidget* scrollTagListWidget;

    QLabel* tagsLabel;
    QList<TagWidget*> tagWidgetList;

    virtual void onTagClickedImpl(int tagId){Q_UNUSED(tagId)}
    virtual void addTagWidget(database::Tag tag);
};

#endif // TAGLISTWIDGET_H
