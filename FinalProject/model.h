#ifndef MODEL_H
#define MODEL_H
#include <evidence.h>
#include <cleaningtool.h>
#include <ToolsEnum.cpp>
#include <EvidenceEnum.cpp>
#include <QObject>
#include <QHash>

class Model : public QObject
{
    Q_OBJECT
signals:
    void updateDialogBoxSignal(Evidence*);
    void clearEvidenceSelections();
    void setSelected(EvidenceEnum);

public slots:
    void evidenceClicked(EvidenceEnum evidence);

public:
    Model(QObject *parent);
    ~Model();
    void eraseAll();
    Tools selectedTool;
    EvidenceEnum selectedEvidence;
private:
    QHash<EvidenceEnum, Evidence*> evidences;
    QHash<Tools, CleaningTool*> cleaningTools;
    void initializeTools();
    void initializeEvidence();
};

#endif // MODEL_H
