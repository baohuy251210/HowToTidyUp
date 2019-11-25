#include "kitchenscene.h"
#include "ui_kitchenscene.h"
#include "ToolsEnum.cpp"
#include <QDebug>

KitchenScene::KitchenScene(QWidget *parent, Model* model) :
    IScene(parent),
    ui(new Ui::KitchenScene),
    model(model)
{
    ui->setupUi(this);\
    InitializeWidgets();
    setupConnections();
    setupPixmaps();
    setupEvidence();
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
    connect(ui->knifeLabel, &Evidence::clickedSignal, this, &KitchenScene::evidenceClickedSlot);

}


void KitchenScene::evidenceClickedSlot(EvidenceEnum evidenceName){
    emit signalUseToolAndEvidence(evidenceName);
}


void KitchenScene::setupPixmaps(){
    ui->knifeLabel->setPixmaps(QPixmap(":/art/interactables/knife_bloody"),
                               QPixmap(":/art/interactables/knife_bloody_highlighted"),
                               QPixmap(":/art/interactables/knife_clean"),
                               QPixmap(":/art/interactables/knife_clean_highlighted)"),
                               QPixmap(":/art/interactables/knife_clean"),
                               QPixmap(":/art/interactables/knife_clean_highlighted)"));
}

void KitchenScene::setupEvidence(){
    ui->knifeLabel->setStartValues(KNIFE, {WATER, RAG, BLEACH},"i'm a knife!!!");
    emit addEvidence(ui->knifeLabel);
}
