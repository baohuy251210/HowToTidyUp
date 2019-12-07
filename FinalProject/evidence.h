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
#include <ToolsEnum.cpp>

class Evidence : public QObject
{
    Q_OBJECT

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
    QList<CleaningTool*>* getUsedTools();
    QVector<CleaningTool> getUsedToolsVector();
    int getCorrectUsedTools();
    int getCorrectToolsSize();
    QVector<CleaningTool *> getCorrectTools();
private:
     void nothing();
    QVector<CleaningTool*> correctTools;
    EvidenceEnum type;
    CleanState cleanState;
    /*Scoring*/

};

#endif // EVIDENCE_H
