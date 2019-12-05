#include "model.h"
#include <QDebug>
#include <EvidenceEnum.cpp>
#include <QTimer>

Model::Model(QObject * parent) :
    QObject(parent),
    selectedEvidence(EvidenceEnum::NONE),
    selectedTool(GLOVE){
}

Model::~Model(){
    foreach(Evidence* evidence, evidences){
        delete evidence;
    }
    foreach(CleaningTool* tool, cleaningTools){
        delete tool;
    }
}

void Model::eraseAll(){
    evidences.clear();
    cleaningTools.clear();
}



void Model::addEvidence(EvidenceEnum type, Evidence* evidence){
    evidences.insert(type, evidence);
    evidencesScore.insert(type, 0);
}

void Model::addCleaningTool(Tools type, CleaningTool* tool){
    cleaningTools.insert(type, tool);
}

void Model::toolClickedSlot(Tools tool){
    emit clearToolSelections();
    emit setSelectedTool(tool);
    selectedTool = tool;
}

void Model::evidenceClicked(EvidenceEnum evidence){
    //if an evidence selected with an actual cleaning supply (not GLOVE)
    if(selectedTool != GLOVE && selectedTool != EMPTY){
        if (selectedEvidence != NONE){
            evidences[selectedEvidence]->isSelected = false;
            emit deselectEvidence(selectedEvidence);
        }
        selectedEvidence = evidence;
        evidences[evidence]->isSelected = true;
        evidences[evidence]->addUsedTool(cleaningTools[selectedTool]);
        emit setSelectedEvidence(evidence);
        emit updateDialogBoxSignal(evidences[evidence]);
        emit updateEducationalPopupSignal(evidences[evidence]);
        updateScore(evidence);
    }
    //if the user click the same current evidence using GLOVE
    if (selectedEvidence == evidence && selectedTool == GLOVE){
        evidences[evidence]->isSelected = false;
        selectedEvidence = NONE;
        emit clearEvidenceSelections();
        emit hideDialogSignal();
        emit deselectEvidence(evidence);
        return;
    }
    //GLOVE + other evidence:
    else if (selectedTool == GLOVE){
        if (selectedEvidence != NONE){
            evidences[selectedEvidence]->isSelected = false;
            emit deselectEvidence(selectedEvidence);
        }
        selectedEvidence = evidence;
        evidences[evidence]->isSelected = true;
        emit clearEvidenceSelections();
        emit setSelectedEvidence(evidence);
        emit updateDialogBoxSignal(evidences[evidence]);
        emit updateEducationalPopupSignal(evidences[evidence]);

        return;
    }
}


void Model::updateScore(EvidenceEnum evidence){
    evidencesScore[evidence]=
            double(evidences[evidence]->getCorrectUsedTools())/double(evidences[evidence]->getCorrectToolsSize());
    qDebug()<<"Debug current overall score"<<getFinalScorePercentage();
}
double Model::getFinalScorePercentage(){
    double score = 0;
    int numEvidences = evidences.keys().size();
    double eachEvidencePercent = double(100)/numEvidences;
    for (EvidenceEnum e: evidencesScore.keys()){
        qDebug()<<e << " : "<<evidencesScore[e];
        /*66.67 percent of 20 is gonna be 66.67*20/100*/
        score += evidencesScore[e]*100.0*eachEvidencePercent/100.0;
    }
    return score;
}

double Model::getEvidenceScorePercentage(EvidenceEnum evidence){
    return evidencesScore[evidence] * 100;
}

Evidence* Model::getEvidence(EvidenceEnum type){
    return evidences[type];
}


void Model::hideDialogSlot(){
    emit hideDialogSignal();
}

void Model::saveGameState(QString fileName){

}
void Model::loadGameState(QString fileName){

}
