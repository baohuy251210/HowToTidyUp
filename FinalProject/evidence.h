#ifndef EVIDENCE_H
#define EVIDENCE_H

#include <QVector>
#include <QString>
#include "ToolsEnum.cpp"
#include <EvidenceEnum.cpp>
#include <CleanStateEnum.cpp>
#include <QPixmap>
#include <QLabel>
#include <cleaningtool.h>

class Evidence : public QObject
{
    Q_OBJECT

public:
    Evidence();
    ~Evidence() override;

    void setStartValues(QVector<CleaningTool*> correctTools, QString description);
    void addUsedTool(CleaningTool* usedTool);

    QList<CleaningTool*> usedTools;
    QString description;
private:
     void nothing();
    QVector<CleaningTool*> correctTools;

    CleanState cleanState;

};

#endif // EVIDENCE_H
