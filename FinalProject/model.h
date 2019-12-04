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
    void setSelectedTool(Tools);
    void setSelectedEvidence(EvidenceEnum);
    void hideDialogSignal();
    void clearToolSelections();
    void deselectEvidence(EvidenceEnum);
public slots:
    void evidenceClicked(EvidenceEnum evidence);
    void toolClickedSlot(Tools tool);
    void hideDialogSlot();
public:
    Model(QObject *parent);
    ~Model();
    void eraseAll();
    EvidenceEnum selectedEvidence;
    Evidence* getEvidence(EvidenceEnum type);
    void addCleaningTool(Tools type, CleaningTool* evidence);
    void addEvidence(EvidenceEnum type, Evidence* evidence);
    double getFinalScorePercentage();
    double getEvidenceScorePercentage(EvidenceEnum evidence);
private:
    QHash<EvidenceEnum, Evidence*> evidences;
    QHash<Tools, CleaningTool*> cleaningTools;
    QHash<EvidenceEnum, double> evidencesScore;
    void updateScore(EvidenceEnum);
    void saveGameState(QString fileName);
    void loadGameState(QString fileName);

    Tools selectedTool;

};

#endif // MODEL_H
