#include "kitchenscene.h"
#include "ui_kitchenscene.h"
#include "ToolsEnum.cpp"
#include <QDebug>

KitchenScene::KitchenScene(QWidget *parent, Model* model) :
    IScene(parent),
    ui(new Ui::KitchenScene),
    model(model)
{
    ui->setupUi(this);

    InitializeWidgets();
    initializeTools();
    initializeEvidence();

    setupConnections();
    setupPixmaps();


}

KitchenScene::~KitchenScene()
{
    delete ui;
}

void KitchenScene::InitializeWidgets(){
    toolbarWidget = ui->toolbarWidget;
}

void KitchenScene::setupConnections(){
    connect(this, &IScene::hideDialogSignal, model, &Model::hideDialogSlot);
    connect(model, &Model::hideDialogSignal, ui->evidenceDialog, &itemDialog::hideDialogSlot );
    connect(ui->knifeLabel, &EvidenceView::clickedSignal, model, &Model::evidenceClicked);

    connect(ui->toolbarWidget->glove, &CleaningToolView::toolClickedSignal, model, &Model::toolClickedSlot);
    connect(ui->toolbarWidget->rag, &CleaningToolView::toolClickedSignal, model, &Model::toolClickedSlot);
    connect(ui->toolbarWidget->bleach, &CleaningToolView::toolClickedSignal, model, &Model::toolClickedSlot);
    connect(ui->toolbarWidget->water, &CleaningToolView::toolClickedSignal, model, &Model::toolClickedSlot);
    connect(ui->toolbarWidget->oxiclean, &CleaningToolView::toolClickedSignal, model, &Model::toolClickedSlot);
    connect(ui->toolbarWidget->nailpolish_remover, &CleaningToolView::toolClickedSignal, model, &Model::toolClickedSlot);

    connect(model, &Model::clearEvidenceSelections, ui->evidenceDialog, &itemDialog::clearEvidenceSlot);
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

void KitchenScene::initializeTools(){
    CleaningTool* glove = new CleaningTool("Glove: A convenient cleaning tool.  I can use it to find out more information about evidence.");
    glove->setSelected(true);
    CleaningTool* rag = new CleaningTool("Rag: An absorbent material good for cleaning up liquids and wiping down surfaces.");
    CleaningTool* bleach = new CleaningTool("Bleach: A hydrogen peroxide based cleaner. Good for removing stains and eliminating odor.");
    CleaningTool* water = new CleaningTool("Water: An old fashioned cleaning liquid that can still be useful on occasion.");
    CleaningTool* oxiclean = new CleaningTool("OxiClean: A versitile stain remover containing an active ingredient known as sodium percarbonate. Known to cause hemoglobin proteins to degrade and no longer uptake oxygen");
    CleaningTool* nailPolishRemover = new CleaningTool("Nail Polish Remover: An organic solvent that can remove the lipids from non-porous substrates if used properly");

    glove->setPixmaps(QPixmap(":/art/tools/glove"),QPixmap(":/art/tools/glove_highlighted"));
    rag->setPixmaps(QPixmap(":/art/tools/rag"),QPixmap(":/art/tools/rag"));
    bleach->setPixmaps(QPixmap(":/art/tools/bleach"),QPixmap(":/art/tools/bleach"));
    water->setPixmaps(QPixmap(":/art/tools/water"),QPixmap(":/art/tools/water"));
    oxiclean->setPixmaps(QPixmap(":/art/tools/oxiclean"), QPixmap(":/art/tools/oxiclean"));
    nailPolishRemover->setPixmaps(QPixmap(":/art/tools/nailpolishremover"), QPixmap(":/art/tools/nailpolishremover"));

    ui->toolbarWidget->glove->setType(GLOVE);
    ui->toolbarWidget->rag->setType(RAG);
    ui->toolbarWidget->bleach->setType(BLEACH);
    ui->toolbarWidget->water->setType(WATER);
    ui->toolbarWidget->oxiclean->setType(OXICLEAN);
    ui->toolbarWidget->nailpolish_remover->setType(NAILPOLISHREMOVER);

    ui->toolbarWidget->glove->setModel(glove);
    ui->toolbarWidget->glove->highlightTool();
    ui->toolbarWidget->rag->setModel(rag);
    ui->toolbarWidget->bleach->setModel(bleach);
    ui->toolbarWidget->water->setModel(water);
    ui->toolbarWidget->oxiclean->setModel(oxiclean);
    ui->toolbarWidget->nailpolish_remover->setModel(nailPolishRemover);

    model->addCleaningTool(RAG, rag);
    model->addCleaningTool(BLEACH, bleach);
    model->addCleaningTool(WATER, water);
    model->addCleaningTool(OXICLEAN, oxiclean);
    model->addCleaningTool(NAILPOLISHREMOVER, nailPolishRemover);



    Evidence* knife = new Evidence();
    knife->setPixmaps(QPixmap(":/art/interactables/knife_bloody"),
                      QPixmap(":/art/interactables/knife_bloody_highlighted"),
                      QPixmap(":/art/interactables/knife_clean"),
                      QPixmap(":/art/interactables/knife_clean_highlighted"),
                      QPixmap(":/art/interactables/knife_clean"),
                      QPixmap(":/art/interactables/knife_clean_highlighted") );
    ui->knifeLabel->setType(KNIFE);
    ui->knifeLabel->setModel(model->getEvidence(KNIFE));
    knife->setStartValues({bleach, rag, water}, "I'm a knife!");
    model->addEvidence(KNIFE, knife);
}

void KitchenScene::initializeEvidence(){

}

void KitchenScene::unselectTool(){

}
