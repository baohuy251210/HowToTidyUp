#include "model.h"
#include <QDebug>
#include <EvidenceEnum.cpp>
#include <QTimer>
#include <QFile>
Model::Model(QObject * parent) :
    QObject(parent),
    selectedEvidence(EvidenceEnum::NONE),
    selectedTool(GLOVE){

    initDictionaries();

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
    //Save the file whenever update score (kinda make sense right :] )
    saveGameState(QApplication::applicationDirPath()+"/save01.json");
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


/**SAVE/LOAD WORK:*/
/*need a dictionary for Enum*/


/*save QHash<evidenceEnum, evidence*  */
//save cleaning tools <Tools, Cleaning Tool *
//save evidences Score  <Evidence Enum, double>
/*selectec tool and selected Evidence are probably not needed*/
void Model::saveGameState(QString fileName){
    qDebug()<<"saveGame::fileName"<<fileName;
    if (fileName.isEmpty()){
        qDebug() << "saveGame::file empty";
        return;
    }

    QFile file(fileName);
    if (file.isOpen()){
        file.close();
    }

    qDebug()<<"saveGame::exists? :"<<file.openMode();
    qDebug() << "saveGame::file permissions:"<<file.permissions();
    if (!file.open(QIODevice::WriteOnly)){
        qDebug() << "saveGame::not able to write";
        return;
    }

    /*Start json:*/
    QJsonObject fileObj;
    //write evidences score:
    QJsonObject evidenceOrderObj;
    EvidenceEnum orderEvi[] = {NONE, KNIFE, BLOOD_TILE,
                            BLOOD_WALL_WOOD, BLOOD_FOOTPRINT,
                           HAIR, FINGERPRINT_GLASS,
                           GUNPOWDER_WALL};
    QJsonObject scoreObj;
    QJsonArray scoreArray;
    for (EvidenceEnum orderEnum: orderEvi){
        scoreArray.append(evidencesScore[orderEnum]);
    }
    fileObj["scores"] = scoreArray;
    qDebug()<<"saveGame::scores gate done";

    //Save evidence
    QJsonArray evidenceArray;
    for (EvidenceEnum e: orderEvi){
       if  (evidences.find(e) == evidences.end())
           continue;
       QList<CleaningTool*>usedToolsList = *evidences[e]->getUsedTools();
       QJsonArray usedToolsArray;
       for (CleaningTool *iterTool : usedToolsList){
            QString ToolString = mapToolsString[iterTool->getType()];
            qDebug() << "inSaveGame::"<<ToolString;
           usedToolsArray.append(ToolString);
       }
       evidenceArray.append(usedToolsArray);
    }

    //get evidences by
    fileObj["usedToolsMap:"] = evidenceArray;

    /*finalize*/
    QJsonDocument jsonDoc(fileObj);
    qDebug() << "saveGame::evidenceArray done";
    file.write(jsonDoc.toJson(QJsonDocument::Compact));
    qDebug() << "saveGame::done ";
}
/*Perhaps load the evidences, cleaning tools back-end ?
* evidences Score -> easy to load.
* cleaning Tools -> easy-medium load -> need function to update the cleaning Tool
* evidences -> medium-hard load -> need functions to update the Evidences.
*/
void Model::loadGameState(QString fileName){
}

void Model::initDictionaries(){
    mapEnumString.insert(NONE, "NONE");
    mapEnumString.insert(KNIFE, "KNIFE");
    mapEnumString.insert(BLOOD_TILE, "BLOOD_TILE");
    mapEnumString.insert(BLOOD_WALL_WOOD, "BLOOD_WALL_WOOD");
    mapEnumString.insert(BLOOD_FOOTPRINT, "BLOOD_FOOTPRINT");
    mapEnumString.insert(HAIR, "HAIR");
    mapEnumString.insert(FINGERPRINT_GLASS, "FINGERPRINT_GLASS");
    mapEnumString.insert(GUNPOWDER_WALL, "GUNPOWDER_WALL");

    mapStringEnum.insert("NONE", NONE);
    mapStringEnum.insert("KNIFE", KNIFE);
    mapStringEnum.insert("BLOOD_TILE", BLOOD_TILE);
    mapStringEnum.insert("BLOOD_WALL_WOOD", BLOOD_WALL_WOOD);
    mapStringEnum.insert("BLOOD_FOOTPRINT", BLOOD_FOOTPRINT);
    mapStringEnum.insert("HAIR", HAIR);
    mapStringEnum.insert("FINGERPRINT_GLASS", FINGERPRINT_GLASS);
    mapStringEnum.insert("GUNPOWDER_WALL", GUNPOWDER_WALL);

    mapToolsString.insert(EMPTY, "EMPTY");
    mapToolsString.insert(GLOVE, "GLOVE");
    mapToolsString.insert(WATER, "WATER");
    mapToolsString.insert(NAILPOLISHREMOVER, "NAILPOLISHREMOVER");
    mapToolsString.insert(BLEACH, "BLEACH");
    mapToolsString.insert(RAG, "RAG");
    mapToolsString.insert(OXICLEAN, "OXICLEAN");

    mapStringTools.insert("EMPTY", EMPTY);
    mapStringTools.insert("GLOVE", GLOVE);
    mapStringTools.insert("WATER", WATER);
    mapStringTools.insert("NAILPOLISHREMOVER", NAILPOLISHREMOVER);
    mapStringTools.insert("BLEACH", BLEACH);
    mapStringTools.insert("RAG", RAG);
    mapStringTools.insert("OXICLEAN", OXICLEAN);
}
