#ifndef EVIDENCE_H
#define EVIDENCE_H

#include <QVector>
#include <QString>
#include "ToolsEnum.cpp"

class Evidence
{
public:
    Evidence(QVector<Tools>, QVector<Tools>, QString);
    QVector<Tools> correctTools;
    QVector<Tools> usedTools;
    QString description;
private:

};

#endif // EVIDENCE_H
