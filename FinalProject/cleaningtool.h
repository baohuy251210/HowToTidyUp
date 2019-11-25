#ifndef CLEANINGTOOL_H
#define CLEANINGTOOL_H

#include <QString>


class CleaningTool
{
public:
    CleaningTool(QString description);
    void setSelected(bool);
private:
    bool isSelected;
    QString description;
};

#endif // CLEANINGTOOL_H
