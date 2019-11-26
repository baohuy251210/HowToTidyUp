#include "model.h"
#include <QDebug>
#include <EvidenceEnum.cpp>


Model::Model(QObject * parent) :
    QObject(parent),
    selectedEvidence(NONE){

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
}

void Model::addCleaningTool(Tools type, CleaningTool* tool){
    cleaningTools.insert(type, tool);
}

void Model::evidenceClicked(EvidenceEnum evidence){
    selectedEvidence = evidence;
    emit clearEvidenceSelections();
    if (evidences[evidence]->isSelected){
        emit setSelected(evidence);
        emit updateDialogBoxSignal(evidences[evidence]);
    }

}

Evidence* Model::getEvidence(EvidenceEnum type){
    return evidences[type];
}
