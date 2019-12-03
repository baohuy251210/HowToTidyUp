#include "kitchenscene.h"
#include "ui_kitchenscene.h"
#include "ToolsEnum.cpp"
#include <evidenceview.h>
#include <QDebug>

KitchenScene::KitchenScene(QWidget *parent, Model* model) :
    IScene(parent),
    ui(new Ui::KitchenScene),
    model(model)
{
    ui->setupUi(this);

    InitializeWidgets();
    initializeEvidence();
    initializeTools();

    setupConnections();

}

KitchenScene::~KitchenScene()
{
    delete ui;
}

void KitchenScene::InitializeWidgets(){
    toolbarWidget = ui->toolbarWidget;
    ui->toolbarWidget->raise();
    ui->evidenceDialog->raise();
    ui->exitButton->setAutoRaise(false);
}

void KitchenScene::setupConnections(){
    connect(this, &IScene::hideDialogSignal, model, &Model::hideDialogSlot);
    connect(model, &Model::hideDialogSignal, ui->evidenceDialog, &itemDialog::hideDialogSlot );
    connect(knifeLabel, &EvidenceView::clickedSignal, model, &Model::evidenceClicked);
    connect(bloodFloorLabel, &EvidenceView::clickedSignal, model, &Model::evidenceClicked);
    connect(oilyHandLabel, &EvidenceView::clickedSignal, model, &Model::evidenceClicked);
    connect(bloodFootprintsLabel, &EvidenceView::clickedSignal, model, &Model::evidenceClicked);
    connect(brokenPlateLabel, &EvidenceView::clickedSignal, model, &Model::evidenceClicked);
    connect(bloodWallLabel, &EvidenceView::clickedSignal, model, &Model::evidenceClicked);


    connect(ui->toolbarWidget->glove, &CleaningToolView::toolClickedSignal, model, &Model::toolClickedSlot);
    connect(ui->toolbarWidget->rag, &CleaningToolView::toolClickedSignal, model, &Model::toolClickedSlot);
    connect(ui->toolbarWidget->bleach, &CleaningToolView::toolClickedSignal, model, &Model::toolClickedSlot);
    connect(ui->toolbarWidget->water, &CleaningToolView::toolClickedSignal, model, &Model::toolClickedSlot);
    connect(ui->toolbarWidget->oxiclean, &CleaningToolView::toolClickedSignal, model, &Model::toolClickedSlot);
    connect(ui->toolbarWidget->nailpolish_remover, &CleaningToolView::toolClickedSignal, model, &Model::toolClickedSlot);

    connect(model, &Model::setSelectedTool, ui->toolbarWidget->glove, &CleaningToolView::setSelectedSlot);
    connect(model, &Model::setSelectedTool, ui->toolbarWidget->rag, &CleaningToolView::setSelectedSlot);
    connect(model, &Model::setSelectedTool, ui->toolbarWidget->bleach, &CleaningToolView::setSelectedSlot);
    connect(model, &Model::setSelectedTool, ui->toolbarWidget->water, &CleaningToolView::setSelectedSlot);
    connect(model, &Model::setSelectedTool, ui->toolbarWidget->oxiclean, &CleaningToolView::setSelectedSlot);
    connect(model, &Model::setSelectedTool, ui->toolbarWidget->nailpolish_remover, &CleaningToolView::setSelectedSlot);

    connect(model, &Model::clearToolSelections, ui->toolbarWidget->glove, &CleaningToolView::clearSelectionSlot);
    connect(model, &Model::clearToolSelections, ui->toolbarWidget->rag, &CleaningToolView::clearSelectionSlot);
    connect(model, &Model::clearToolSelections, ui->toolbarWidget->bleach, &CleaningToolView::clearSelectionSlot);
    connect(model, &Model::clearToolSelections, ui->toolbarWidget->water, &CleaningToolView::clearSelectionSlot);
    connect(model, &Model::clearToolSelections, ui->toolbarWidget->oxiclean, &CleaningToolView::clearSelectionSlot);
    connect(model, &Model::clearToolSelections, ui->toolbarWidget->nailpolish_remover, &CleaningToolView::clearSelectionSlot);

    connect(model, &Model::clearEvidenceSelections, ui->evidenceDialog, &itemDialog::clearEvidenceSlot);
    connect(model, &Model::deselectEvidence, this, &KitchenScene::deselectEvidenceSlot);
    connect(model, &Model::setSelectedEvidence, this, &KitchenScene::setSelectedEvidenceSlot);
    connect(model, &Model::updateDialogBoxSignal, ui->evidenceDialog, &itemDialog::setEvidence);
}


void KitchenScene::setupPixmaps(){

}

void KitchenScene::initializeTools(){
    CleaningTool* glove = new CleaningTool("Glove: A convenient cleaning tool.  I can use it to find out more information about evidence.");
    glove->setSelected(true);
    CleaningTool* rag = new CleaningTool("Rag: An absorbent material good for cleaning up liquids and wiping down surfaces.");
    CleaningTool* bleach = new CleaningTool("Bleach: A hydrogen peroxide based cleaner. Good for removing stains and eliminating odor.");
    CleaningTool* water = new CleaningTool("Water: An old fashioned cleaning liquid that can still be useful on occasion.");
    CleaningTool* oxiclean = new CleaningTool("OxiClean: A versitile stain remover containing an active ingredient known as sodium percarbonate. Known to cause hemoglobin proteins to degrade and no longer uptake oxygen.");
    CleaningTool* nailPolishRemover = new CleaningTool("Nail Polish Remover: An organic solvent that can remove the lipids from non-porous substrates if used properly.");

    glove->setPixmaps(QPixmap(":/art/tools/glove"),QPixmap(":/art/tools/glove_highlighted"),QPixmap(":/art/cursor/glove_cursor"));
    rag->setPixmaps(QPixmap(":/art/tools/rag"),QPixmap(":/art/tools/rag_highlighted"),QPixmap(":/art/cursor/rag_cursor"));
    bleach->setPixmaps(QPixmap(":/art/tools/bleach"),QPixmap(":/art/tools/bleach_highlighted"),QPixmap(":/art/cursor/bleach_cursor"));
    water->setPixmaps(QPixmap(":/art/tools/water"),QPixmap(":/art/tools/water_highlighted"),QPixmap(":/art/cursor/water_cursor"));
    oxiclean->setPixmaps(QPixmap(":/art/tools/oxiclean"), QPixmap(":/art/tools/oxiclean_highlighted"),QPixmap(":/art/cursor/oxiclean_cursor"));
    nailPolishRemover->setPixmaps(QPixmap(":/art/tools/nailpolishremover"), QPixmap(":/art/tools/nailpolishremover_highlighted"),QPixmap(":/art/cursor/nailpolishremover_cursor"));

    ui->toolbarWidget->glove->setType(GLOVE);
    ui->toolbarWidget->rag->setType(RAG);
    ui->toolbarWidget->bleach->setType(BLEACH);
    ui->toolbarWidget->water->setType(WATER);
    ui->toolbarWidget->oxiclean->setType(OXICLEAN);
    ui->toolbarWidget->nailpolish_remover->setType(NAILPOLISHREMOVER);

    glove->setType(GLOVE);
    rag->setType(RAG);
    bleach->setType(BLEACH);
    water->setType(WATER);
    oxiclean->setType(OXICLEAN);
    nailPolishRemover->setType(NAILPOLISHREMOVER);

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


    // initialize knife
    Evidence* knife = new Evidence();
    knife->setPixmaps(QPixmap(":/art/interactables/knife_bloody"),
                      QPixmap(":/art/interactables/knife_bloody_highlighted"),
                      QPixmap(":/art/interactables/knife_clean"),
                      QPixmap(":/art/interactables/knife_clean_highlighted"),
                      QPixmap(":/art/interactables/knife_clean"),
                      QPixmap(":/art/interactables/knife_clean_highlighted") );
    knifeLabel->setType(KNIFE);
    evidenceLabels.insert(KNIFE, knifeLabel);
    model->addEvidence(KNIFE, knife);
    knifeLabel->setModel(model->getEvidence(KNIFE));
    knife->setStartValues({water, bleach, rag}, "Bloody knife.");

    // initialize blood stain on floor
    Evidence* bloodFloor = new Evidence();
    bloodFloor->setPixmaps(QPixmap(":/art/interactables/blood_floor"),
                           QPixmap(":/art/interactables/blood_floor_highlighted"),
                           QPixmap(),
                           QPixmap(":/art/interactables/blood_floor_clean_highlighted"),
                           QPixmap(),
                           QPixmap(":/art/interactables/blood_floor_clean_highlighted"));
    bloodFloorLabel->setType(BLOOD_TILE);
    evidenceLabels.insert(BLOOD_TILE, bloodFloorLabel);
    model->addEvidence(BLOOD_TILE, bloodFloor);
    bloodFloorLabel->setModel(model->getEvidence(BLOOD_TILE));
    bloodFloor->setStartValues({bleach, oxiclean, rag}, "Bloody stain on the floor");

    // initialize oily handprint
    Evidence* handprint = new Evidence();
    handprint->setPixmaps(QPixmap(":/art/interactables/oily_handprint_01"),
                           QPixmap(":/art/interactables/oily_handprint_highlighted"),
                           QPixmap(),
                           QPixmap(":/art/interactables/oily_handprint_clean_highlighted"),
                           QPixmap(),
                           QPixmap(":/art/interactables/oily_handprint_clean_highlighted"));
    oilyHandLabel->setType(FINGERPRINT_GLASS);
    evidenceLabels.insert(FINGERPRINT_GLASS, oilyHandLabel);
    model->addEvidence(FINGERPRINT_GLASS, handprint);
    oilyHandLabel->setModel(model->getEvidence(FINGERPRINT_GLASS));
    handprint->setStartValues({nailPolishRemover, water, rag}, "Oily handprint on glass");

    // initialize broken plate
    Evidence* brokenPlate = new Evidence();
    brokenPlate->setPixmaps(QPixmap(":/art/interactables/plate_broken"),
                           QPixmap(":/art/interactables/plate_broken_highlighted"),
                           QPixmap(),
                           QPixmap(":/art/interactables/plate_clean_highlighted"),
                           QPixmap(),
                           QPixmap(":/art/interactables/plate_clean_highlighted"));
    brokenPlateLabel->setType(BROKEN_PLATE);
    evidenceLabels.insert(BROKEN_PLATE, brokenPlateLabel);
    model->addEvidence(BROKEN_PLATE, brokenPlate);
    brokenPlateLabel->setModel(model->getEvidence(BROKEN_PLATE));
    brokenPlate->setStartValues({bleach, rag, rag}, "Broken plate");

    // initialize bloody footprints
    Evidence* bloodyFootprints = new Evidence();
    bloodyFootprints->setPixmaps(QPixmap(":/art/interactables/blood_footprint"),
                           QPixmap(":/art/interactables/blood_footprint_highlighted"),
                           QPixmap(),
                           QPixmap(":/art/interactables/blood_footprint_clean_highlighted"),
                           QPixmap(),
                           QPixmap(":/art/interactables/blood_footprint_clean_highlighted"));
    bloodFootprintsLabel->setType(BLOOD_FOOTPRINT);
    evidenceLabels.insert(BLOOD_FOOTPRINT, bloodFootprintsLabel);
    model->addEvidence(BLOOD_FOOTPRINT, bloodyFootprints);
    bloodFootprintsLabel->setModel(model->getEvidence(BLOOD_FOOTPRINT));
    bloodyFootprints->setStartValues({bleach, oxiclean, rag}, "Bloody footprints on floor");

    // initialize bloody wall
    Evidence* bloodyWall = new Evidence();
    bloodyWall->setPixmaps(QPixmap(":/art/interactables/blood_wall"),
                           QPixmap(":/art/interactables/blood_wall_highlighted"),
                           QPixmap(),
                           QPixmap(":/art/interactables/blood_wall_clean_highlighted"),
                           QPixmap(),
                           QPixmap(":/art/interactables/blood_wall_clean_highlighted"));
    bloodWallLabel->setType(BLOOD_WALL_WOOD);
    evidenceLabels.insert(BLOOD_WALL_WOOD, bloodWallLabel);
    model->addEvidence(BLOOD_WALL_WOOD, bloodyWall);
    bloodWallLabel->setModel(model->getEvidence(BLOOD_WALL_WOOD));
    bloodyWall->setStartValues({bleach, oxiclean, rag}, "Blood splatter on wooden wall");

}

void KitchenScene::initializeEvidence(){
    knifeLabel = ui->knifeLabel;
    bloodFloorLabel = ui->bloodFloorLabel;
    oilyHandLabel = ui->oilyHandLabel;
    bloodFootprintsLabel = ui->bloodFootprintLabel;
    brokenPlateLabel = ui->plateLabel;
    bloodWallLabel = ui->bloodWallLabel;
}

void KitchenScene::unselectTool(){

}


void KitchenScene::deselectEvidenceSlot(EvidenceEnum selectedEvidence){
    evidenceLabels[selectedEvidence]->unhighlightEvidence();

}

void KitchenScene::setSelectedEvidenceSlot(EvidenceEnum selectedEvidence){
    evidenceLabels[selectedEvidence]->highlightEvidence();
}

void KitchenScene::on_exitButton_clicked()
{
    emit changeScene(ENDING);

}
