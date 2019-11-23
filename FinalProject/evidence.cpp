#include "evidence.h"

#include <QVector>
#include <QString>
#include "ToolsEnum.cpp"

Evidence::Evidence(QVector<Tools> correctTools, QVector<Tools> usedTools, QString description)
    : correctTools(correctTools), usedTools(usedTools), description(description)
{

}
