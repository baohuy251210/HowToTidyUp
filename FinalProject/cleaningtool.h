#ifndef CLEANINGTOOL_H
#define CLEANINGTOOL_H

#include <QString>
#include <QPixmap>

class CleaningTool
{
public:
    CleaningTool(QString description);
    void setSelected(bool);
    QPixmap* getIcon();
    void setPixmaps(QPixmap icon, QPixmap icon_selected);
    QPixmap icon;
    QPixmap icon_selected;
private:
    bool isSelected;
    QString description;

};

#endif // CLEANINGTOOL_H
