#include "model.h"
#include <QDebug>
#include <EvidenceEnum.cpp>


Model::Model(QObject * parent) :
    QObject(parent),
    selectedEvidence(EvidenceEnum::NONE){

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

void Model::toolClickedSlot(Tools tool){

}

void Model::evidenceClicked(EvidenceEnum evidence){
    if (selectedEvidence == evidence){
        evidences[evidence]->isSelected = false;
        selectedEvidence = NONE;
        emit clearEvidenceSelections();
        return;
    }
    if (selectedEvidence != NONE){
        evidences[selectedEvidence]->isSelected = false;
    } else {
        selectedEvidence = evidence;
        evidences[evidence]->isSelected = true;
        emit clearEvidenceSelections();
        if (evidences[evidence]->isSelected){
            emit setSelected(evidence);
            emit updateDialogBoxSignal(evidences[evidence]);
        }
    }


}

Evidence* Model::getEvidence(EvidenceEnum type){
    return evidences[type];
}
