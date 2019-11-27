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
    void setPixmaps(QPixmap icon, QPixmap icon_selected);
    QPixmap icon;
    QPixmap icon_selected;
    bool isSelected;
    QString description;

    void setType(Tools type);
    Tools getType();

private:

    Tools type;

};

#endif // CLEANINGTOOL_H
