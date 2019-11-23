#ifndef MODEL_H
#define MODEL_H
#include <evidence.h>
#include <cleaningtool.h>
#include <ToolsEnum.cpp>
#include <QObject>
class Model : public QObject
{
    Q_OBJECT
public:
    Model(QObject *parent);
    void addEvidenceObject(QString evidenceName,QVector<Tools> correctTools, QString description);
    void eraseAll();
private:
    QVector<Evidence> evidences;
    QVector<CleaningTool> cleaningTools;
};

#endif // MODEL_H
