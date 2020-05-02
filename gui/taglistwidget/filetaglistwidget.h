#ifndef FILETAGLISTWIDGET_H
#define FILETAGLISTWIDGET_H

#include "taglistwidget.h"

class FileTagListWidget : public TagListWidget
{
    Q_OBJECT
public:
    explicit FileTagListWidget(QWidget *parent = nullptr);

protected slots:
    void updateFileTag();

protected:
    void onTagClickedImpl(int tagId) override;
};

#endif // FILETAGLISTWIDGET_H
