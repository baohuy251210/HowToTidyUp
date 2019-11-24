#ifndef MODEL_H
#define MODEL_H
#include <evidence.h>
#include <cleaningtool.h>
#include <ToolsEnum.cpp>
#include <QObject>
class Model : public QObject
{
    Q_OBJECT
signals:
    void signalDialogBox(Evidence);
public slots:
    void slotUsedToolAndEvidence(Tools, QString);
public:
    Model(QObject *parent);
    void addEvidenceObject(QString evidenceName,QVector<Tools> correctTools, QString description);
    void eraseAll();
private:
    QVector<Evidence> evidences;
    QVector<CleaningTool> cleaningTools;
    int findEvidenceIndex(QString evidenceName);
};

#endif // MODEL_H
