#ifndef EVIDENCE_H
#define EVIDENCE_H

#include <QVector>
#include <QString>


class Evidence
{
public:
    Evidence(QVector<QString>, QVector<QString>, QString);
    QVector<QString> correctTools;
    QVector<QString> usedTools;
    QString description;
private:

};

#endif // EVIDENCE_H
