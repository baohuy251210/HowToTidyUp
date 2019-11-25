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

    void setStartValues(QVector<Tools> correctTools, QString description);
    void addUsedTool(CleaningTool* usedTool);
    void setPixmaps(QPixmap dirty,
                    QPixmap dirty_highlighted,
                    QPixmap semiclean,
                    QPixmap semiclean_highlighted,
                    QPixmap clean,
                    QPixmap clean_highlighted);

    QList<CleaningTool*> usedTools;
    QString description;
    QPixmap dirty, dirty_highlighted, semiclean, semiclean_highlighted, clean, clean_highlighted;

private:
     void nothing();
    QVector<Tools> correctTools;

    CleanState cleanState;

};

#endif // EVIDENCE_H
