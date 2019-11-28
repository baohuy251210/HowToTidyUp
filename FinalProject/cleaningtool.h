#ifndef CLEANINGTOOL_H
#define CLEANINGTOOL_H

#include <QString>
#include <QPixmap>
#include <ToolsEnum.cpp>

class CleaningTool
{
public:
    CleaningTool(QString description);
    void setSelected(bool);
    QPixmap getIcon();
    QPixmap getCursor();
    QPixmap getIconHighlighted();
    void setPixmaps(QPixmap icon, QPixmap icon_selected, QPixmap cursor);
    bool isSelected;
    QString description;

    void setType(Tools type);
    Tools getType();

private:
    QPixmap cursor;
    QPixmap icon;
    QPixmap icon_selected;

    Tools type;

};

#endif // CLEANINGTOOL_H
