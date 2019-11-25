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
    initializeEvidence();

    setupConnections();
    setupPixmaps();
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
    connect(ui->knifeLabel, &EvidenceView::clickedSignal, model, &Model::evidenceClicked);
    connect(model, &Model::clearEvidenceSelections, ui->knifeLabel, &EvidenceView::clearSelection);
    connect(model, &Model::setSelected, ui->knifeLabel, &EvidenceView::setSelected);
    connect(model, &Model::updateDialogBoxSignal, ui->evidenceDialog, &itemDialog::setEvidence);
}

void KitchenScene::evidenceClickedSlot(EvidenceEnum evidenceName){
    model->selectedEvidence = evidenceName;
}

void KitchenScene::setupPixmaps(){
    ui->knifeLabel->setType(KNIFE);
    ui->knifeLabel->setModel(model->getEvidence(KNIFE));
}

void KitchenScene::initializeEvidence(){
    Evidence* knife = new Evidence();
    knife->setPixmaps(QPixmap(":/art/interactables/knife_bloody"),
                      QPixmap(":/art/interactables/knife_bloody_highlighted"),
                      QPixmap(":/art/interactables/knife_clean"),
                      QPixmap(":/art/interactables/knife_clean_highlighted"),
                      QPixmap(":/art/interactables/knife_clean"),
                      QPixmap(":/art/interactables/knife_clean_highlighted") );
    ui->knifeLabel->setType(KNIFE);
    ui->knifeLabel->setModel(model->getEvidence(KNIFE));
    knife->setStartValues({BLEACH, RAG, WATER}, "I'm a knife!");
    model->addEvidence(KNIFE, knife);
}
