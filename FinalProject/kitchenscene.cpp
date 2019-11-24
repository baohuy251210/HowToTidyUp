#include "kitchenscene.h"
#include "ui_kitchenscene.h"
#include "ToolsEnum.cpp"
#include <QDebug>

KitchenScene::KitchenScene(QWidget *parent) :
    IScene(parent),
    ui(new Ui::KitchenScene)
{
    ui->setupUi(this);
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
void KitchenScene::setupConnections(){
    connect(cleaningTools, SIGNAL(toolSelectedSignal(QString)), this, SLOT(toolSelectedSlot(QString)));
    connect(ui->knifeLabel, &EvidenceLabel::interactionSignal, this, &KitchenScene::evidenceActionSlot);
}

void KitchenScene::toolSelectedSlot(Tools tool){
    qDebug() << tool << " selected" << endl;
    selectedCleaningTool = tool;
}

void KitchenScene::evidenceActionSlot(QString evidenceName, QString actionName){
    if (actionName == "press"){
        evidencePressed(evidenceName);
    }
}

void KitchenScene::evidencePressed(QString evidenceName){
    selectedEvidence = evidenceName;
    emit signalUseToolAndEvidence(selectedCleaningTool, selectedEvidence);
}

