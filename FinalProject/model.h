#ifndef MODEL_H
#define MODEL_H
#include <evidence.h>
#include <cleaningtool.h>
#include <ToolsEnum.cpp>
class Model
{
public:
    Model();
    void addEvidenceObject(QVector<Tools> correctTools, QString description);
private:
    QVector<Evidence> evidences;
    QVector<CleaningTool> cleaningTools;
};

#endif // MODEL_H
