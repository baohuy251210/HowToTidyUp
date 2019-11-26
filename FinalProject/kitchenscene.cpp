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
    cleaningTools = ui->toolbarWidget;

}
void KitchenScene::setupConnections(){
    connect(ui->knifeLabel, &EvidenceView::clickedSignal, model, &Model::evidenceClicked);
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
    CleaningTool* glove = new CleaningTool("click on things for more info");
    glove->setSelected(true);
    CleaningTool* rag = new CleaningTool("i'm a rag");
    CleaningTool* bleach = new CleaningTool("i'm bleach");
    CleaningTool* water = new CleaningTool("i'm water");
    CleaningTool* oxiclean = new CleaningTool("I'm oxiclean!");
    CleaningTool* nailPolishRemover = new CleaningTool("I'm nail polish remover");

    glove->setPixmaps(QPixmap(":/art/tools/glove"),QPixmap(":/art/tools/glove_highlighted"));
    rag->setPixmaps(QPixmap(":/art/tools/rag"),QPixmap(":/art/tools/rag"));
    bleach->setPixmaps(QPixmap(":/art/tools/bleach"),QPixmap(":/art/tools/bleach"));
    water->setPixmaps(QPixmap(":/art/tools/water"),QPixmap(":/art/tools/water"));
    oxiclean->setPixmaps(QPixmap(":/art/tools/oxiclean"), QPixmap(":/art/tools/oxiclean"));
    nailPolishRemover->setPixmaps(QPixmap(":/art/tools/nailpolishremover"), QPixmap(":/art/tools/nailpolishremover"));

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
