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
    qDebug() << "model::done adding evidence";
}

void Model::slotUsedToolAndEvidence(Tools usedTool, QString usedEvidence){
    qDebug()<<"Model::UsedToolAndEvidence";
}

