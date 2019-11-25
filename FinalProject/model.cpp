#include "model.h"
#include <QDebug>
#include <EvidenceEnum.cpp>


Model::Model(QObject * parent) :
    QObject(parent),
    currentEvidence(NONE){

}

void Model::eraseAll(){
    evidences.clear();
    cleaningTools.clear();
}

void Model::addEvidenceObject(Evidence* evidenceName){
    evidences.push_back(evidenceName);
}


