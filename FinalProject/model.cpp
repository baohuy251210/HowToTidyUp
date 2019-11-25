#include "model.h"
#include <QDebug>
#include <EvidenceEnum.cpp>


Model::Model(QObject * parent) :
    QObject(parent),
    selectedEvidence(NONE){

    initializeTools();
    initializeEvidence();
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

void Model::initializeTools(){
    CleaningTool* rag = new CleaningTool("i'm a rag");
    CleaningTool* bleach = new CleaningTool("i'm bleach");
    CleaningTool* water = new CleaningTool("i'm water");

    cleaningTools.insert(RAG, rag);
    cleaningTools.insert(BLEACH, bleach);
    cleaningTools.insert(WATER, water);
}

void Model::initializeEvidence(){
    Evidence* knife = new Evidence();
    evidences.insert(KNIFE, knife);
    evidences[KNIFE]->setStartValues({cleaningTools[BLEACH], cleaningTools[RAG], cleaningTools[WATER]}, "I'm a knife!");
}

void Model::evidenceClicked(EvidenceEnum evidence){
    selectedEvidence = evidence;
    emit clearEvidenceSelections();
    emit setSelected(evidence);
    emit updateDialogBoxSignal(evidences[evidence]);
}
