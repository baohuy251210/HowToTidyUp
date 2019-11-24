#include "evidence.h"

#include <QVector>
#include <QString>
#include "ToolsEnum.cpp"
#include <QDebug>
Evidence::Evidence(QString evidenceName,QVector<Tools> correctTools, QString description)
    : evidenceName(evidenceName), correctTools(correctTools), description(description)
{
    usedTools.clear();
}

void Evidence::addUsedTool(Tools usedTool){
    if (usedTools.size() == correctTools.size()){
        usedTools.removeFirst();
    }
    usedTools.push_back(usedTool);
}
