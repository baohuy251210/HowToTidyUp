#ifndef EVIDENCE_H
#define EVIDENCE_H

#include <QDebug>
#include "ToolsEnum.cpp"
#include "EvidenceEnum.cpp"
#include "CleanStateEnum.cpp"
#include "cleaningtool.h"

class Evidence : public QObject
{
    Q_OBJECT

signals:
    void cleanStateChangedSignal();

public:

    Evidence();
    ~Evidence() override;

    void setStartValues(QVector<CleaningTool*> correctTools, QString description);
    void addUsedTool(CleaningTool* usedTool);
    void setPixmaps(QPixmap dirty,
                    QPixmap dirty_highlighted,
                    QPixmap semiclean,
                    QPixmap semiclean_highlighted,
                    QPixmap clean,
                    QPixmap clean_highlighted);

    QList<CleaningTool*> usedTools;
    QString description;
    QString educationalURL;
    QString hint;
    QPixmap dirty, dirty_highlighted, semiclean, semiclean_highlighted, clean, clean_highlighted;
    QPixmap* getIcon();
    EvidenceEnum getType();
    void setType(EvidenceEnum type);
    bool isSelected;
    void setCleanState(CleanState state);
    QList<CleaningTool*>* getUsedTools();
    QVector<CleaningTool> getUsedToolsVector();
    QVector<CleaningTool*> getCorrectToolsVector();
    int getCorrectUsedTools();
    int getCorrectToolsSize();
    QVector<CleaningTool *> getCorrectTools();
    CleanState getCleanState();
    void retryCleaningEvidence();
private:
     void nothing();
    QVector<CleaningTool*> correctTools;
    EvidenceEnum type;
    CleanState cleanState;
    /*Scoring*/

};

#endif // EVIDENCE_H
