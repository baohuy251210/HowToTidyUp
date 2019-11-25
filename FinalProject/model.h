#ifndef MODEL_H
#define MODEL_H
#include <evidence.h>
#include <cleaningtool.h>
#include <ToolsEnum.cpp>
#include <EvidenceEnum.cpp>
#include <QObject>

class Model : public QObject
{
    Q_OBJECT
signals:
    void signalDialogBox(Evidence*);
public slots:
    void addEvidenceObject(Evidence* evidenceName);
public:
    Model(QObject *parent);
    void eraseAll();
private:
    QVector<Evidence*> evidences;
    QVector<CleaningTool> cleaningTools;
    EvidenceEnum currentEvidence;
    Tools selectedTool;
};

#endif // MODEL_H
