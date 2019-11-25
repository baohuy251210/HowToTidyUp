#include "evidence.h"

#include <QVector>
#include <QString>
#include "ToolsEnum.cpp"
#include <QDebug>

Evidence::Evidence(): cleanState(DIRTY)
{
    usedTools.clear();
}

Evidence::~Evidence(){

}

void Evidence::setStartValues(QVector<CleaningTool*> correctTools, QString newDescription){
    this->correctTools = correctTools;
    this->description = newDescription;
}

void Evidence::addUsedTool(CleaningTool* usedTool){
    usedTools.append(usedTool);
    if(usedTools.size() > 3){
        usedTools.removeFirst();
    }
}

