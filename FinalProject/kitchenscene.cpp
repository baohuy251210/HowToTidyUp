#include "kitchenscene.h"
#include "ui_kitchenscene.h"
#include "ToolsEnum.cpp"
#include <QDebug>

KitchenScene::KitchenScene(QWidget *parent) :
    IScene(parent),
    ui(new Ui::KitchenScene)
{
    ui->setupUi(this);
   // QImage cleanKnife = QImage(":/art/interactables/knife_bloody");
    //QPixmap pm = QPixmap::fromImage(cleanKnife);
    //ui->knifeLabel->setPixmap(pm);
    /*connect add knife (test)*/
    selectedEvidence = "";
    selectedCleaningTool = GLOVE;
    InitializeWidgets();
    setupConnections();
}

KitchenScene::~KitchenScene()
{
    delete ui;
}

void KitchenScene::InitializeWidgets(){
    cleaningTools = ui->toolbarWidget;

}
//void KitchenScene::evidencePressed(QString evidenceName){
//    selectedEvidence = evidenceName;
//    emit signalUseToolAndEvidence(selectedCleaningTool, evidenceName);
//}

void KitchenScene::setupConnections(){
    connect(cleaningTools, SIGNAL(toolSelectedSignal(QString)), this, SLOT(toolSelectedSlot(QString)));
    connect(ui->knifeLabel, &EvidenceLabel::interactionSignal, this, &KitchenScene::evidenceActionSlot);
}

void KitchenScene::toolSelectedSlot(Tools tool){
    qDebug() << tool << " selected" << endl;
    selectedCleaningTool = tool;
}

void KitchenScene::evidenceActionSlot(QString evidenceName, QString actionName){
    qDebug() << "WHAT";
    if (actionName == "press"){
        evidencePressed(evidenceName);
    }
}
//void KitchenScene::evidenceActionSlot(QString evidenceName, QString actionName){
//    if (actionName == "press"){
//        qDebug()<< "WHAT";
//        evidencePressed(evidenceName);
//    }
//}
void KitchenScene::evidencePressed(QString fdfd){
    selectedEvidence = fdfd;
    emit signalUseToolAndEvidence(selectedCleaningTool, selectedEvidence);
}

