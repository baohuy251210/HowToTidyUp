#include "evidence.h"

#include <QVector>
#include <QString>
#include "ToolsEnum.cpp"
#include <QDebug>

Evidence::Evidence(): isSelected(false), cleanState(DIRTY)
{
    usedTools.clear();
}

Evidence::~Evidence(){

}

void Evidence::setStartValues(QVector<Tools> correctTools, QString newDescription){
    this->correctTools = correctTools;
    this->description = newDescription;
}

void Evidence::addUsedTool(CleaningTool* usedTool){
    usedTools.append(usedTool);
    if(usedTools.size() > 3){
        usedTools.removeFirst();
    }
}

void Evidence::setPixmaps(QPixmap dirty,
                          QPixmap dirtySelected,
                          QPixmap semiclean,
                          QPixmap semicleanSelected,
                          QPixmap clean,
                          QPixmap cleanSelected){
    this->dirty = dirty;
    this->dirty_highlighted = dirtySelected;
    this->semiclean = semiclean;
    this->semiclean_highlighted = semicleanSelected;
    this->clean = clean;
    this->clean_highlighted = cleanSelected;
}

QPixmap* Evidence::getIcon(){
    switch(cleanState){
    case CLEAN:
        return &clean;
    case DIRTY:
        return &dirty;
    case SEMICLEAN:
        return &semiclean;
    }
}
