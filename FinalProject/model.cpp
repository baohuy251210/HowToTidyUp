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

    if(selectedTool != GLOVE && selectedTool != EMPTY){
        evidences[evidence]->addUsedTool(cleaningTools[selectedTool]);
        emit updateDialogBoxSignal(evidences[evidence]);
    }

    if (selectedEvidence == evidence && selectedTool == GLOVE){
        evidences[evidence]->isSelected = false;
        selectedEvidence = NONE;
        emit clearEvidenceSelections();
        emit hideDialogSignal();
        emit deselectEvidence(evidence);
        return;
    }

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
        return;

    }


}

Evidence* Model::getEvidence(EvidenceEnum type){
    return evidences[type];
}

void Model::hideDialogSlot(){
    emit hideDialogSignal();
}
