#ifndef EVIDENCE_H
#define EVIDENCE_H

#include <QVector>
#include <QString>
#include "ToolsEnum.cpp"

class Evidence
{
public:
    Evidence(QString, QVector<Tools>, QString);
    QVector<Tools> correctTools;
    QVector<Tools> usedTools;
    QString description;
    QString evidenceName;
    void addUsedTool(Tools);
private:
     void nothing();

};

#endif // EVIDENCE_H
