#include "model.h"
#include <QDebug>

Model::Model(QObject * parent) : QObject(parent)
{
}
void Model::eraseAll(){
    evidences.clear();
    cleaningTools.clear();
}

void Model::addEvidenceObject(QString evidenceName, QVector<Tools> correctTools, QString description){
    evidences.push_back(Evidence(evidenceName, correctTools, description));
}
/*
 * slot called when an evidenceName and usedTool
 * add the usedTool (if applicable) to the usedEvidence
 * and signal a change to dialog box
**/
void Model::slotUsedToolAndEvidence(Tools usedTool, QString usedEvidenceName){
    int eviIndex = findEvidenceIndex(usedEvidenceName);
    if (eviIndex == -1){
        qDebug() << "evidence name not found";
        return;
    }
    if (usedTool != GLOVE){
        evidences[eviIndex].addUsedTool(usedTool);
    }
    emit signalDialogBox(evidences[eviIndex]);
}

/*
 * find the index of the evidence given in 'evidences'
**/
int Model::findEvidenceIndex(QString usedEvidenceName){
    for (int i = 0; i < evidences.size(); i++){
        if (evidences[i].evidenceName == usedEvidenceName){
            return i;
        }
    }
    return -1;
}

