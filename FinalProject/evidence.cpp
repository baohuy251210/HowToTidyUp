#include "evidence.h"

Evidence::Evidence(): isSelected(false), cleanState(DIRTY)
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
    //we should only have three states.
    assert(cleanState == CLEAN || cleanState == DIRTY
           || cleanState == SEMICLEAN);
    switch(cleanState){
    case CLEAN:
        return &clean;
    case DIRTY:
        return &dirty;
    case SEMICLEAN:
        return &semiclean;
    }
}

CleanState Evidence::getCleanState(){
    return cleanState;
}

void Evidence::setType(EvidenceEnum type){
    this->type = type;
}

void Evidence::setCleanState(CleanState state){
    this->cleanState = state;
    emit cleanStateChangedSignal();
}

int Evidence::getCorrectUsedTools(){
    int correctNumber = 0;
    for (int i = 0; i < usedTools.size();i++){
        if (usedTools[i] == correctTools[i]){
            correctNumber++;
        }
    }
    return (correctNumber);
}
int Evidence::getCorrectToolsSize(){
    return correctTools.size();
}
QVector<CleaningTool*> Evidence::getCorrectToolsVector(){
    return correctTools;
}

QVector<CleaningTool *> Evidence::getCorrectTools(){
    return correctTools;
}

EvidenceEnum Evidence::getType(){
    return this->type;
}

QList<CleaningTool*>* Evidence::getUsedTools(){
    return &usedTools;
}
QVector<CleaningTool> Evidence::getUsedToolsVector(){
    QVector<CleaningTool> usedToolsVector;
    for (int i = 0; i < usedTools.size();i++){
        usedToolsVector.push_back(*usedTools[i]);
    }
    return usedToolsVector;
}

void Evidence::retryCleaningEvidence(){
    usedTools.clear();
    cleanState = DIRTY;
}
