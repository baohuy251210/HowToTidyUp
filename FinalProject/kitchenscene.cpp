#include "kitchenscene.h"
#include "ui_kitchenscene.h"


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
    ui->bloodFootprintMaskLabel->raise();
    ui->bloodFloorMaskLabel->raise();
    ui->resetButton->hide();
    this->addFont();
    drawTextLabel(ui->backLabel, 21, "SF Cartoonist Hand SC", "Bold");
    drawTextLabel(ui->endLabel, 23, "SF Cartoonist Hand SC", "Bold");
    drawTextPushButton(ui->resetButton, 17, "SF Cartoonist Hand SC", "Bold");

}

void KitchenScene::loadGameKitchen(){
    model->loadGameSlot();
}

KitchenScene::~KitchenScene()
{
    delete ui;
    delete exitDialog;
}

void KitchenScene::InitializeWidgets(){
    toolbarWidget = ui->toolbarWidget;
    ui->toolbarWidget->raise();
    ui->evidenceDialog->raise();
    ui->educationalPopup->raise();

    ui->exitButton->setAutoRaise(false);
    exitDialog = new ExitDialog(this);
    exitDialog->setWindowTitle("");

}

void KitchenScene::setupConnections(){
    connect(this, &IScene::hideDialogSignal, model, &Model::hideDialogSlot);
    connect(model, &Model::hideDialogSignal, ui->evidenceDialog, &itemDialog::hideDialogSlot );
    connect(model, &Model::hideDialogSignal, ui->educationalPopup, &educationalpopup::hideEducationalDialogSlot );
    connect(knifeLabel, &EvidenceView::clickedSignal, model, &Model::evidenceClicked);
    connect(bloodFloorLabel, &EvidenceView::clickedSignal, model, &Model::evidenceClicked);
    connect(oilyHandLabel, &EvidenceView::clickedSignal, model, &Model::evidenceClicked);
    connect(bloodFootprintsLabel, &EvidenceView::clickedSignal, model, &Model::evidenceClicked);
    connect(bloodWallLabel, &EvidenceView::clickedSignal, model, &Model::evidenceClicked);
    connect(gunpowderWallLabel, &EvidenceView::clickedSignal, model, &Model::evidenceClicked);


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

    connect(model, &Model::updateEducationalPopupSignal, ui->educationalPopup, &educationalpopup::evidenceClickedURLChange);
    connect(exitDialog, SIGNAL(exitSceneSignal()), this, SLOT(exitSceneSlot()));

    /*Popup Overlay attempt */
    //BLOOD FOOTPRINT MASK:
    connect(ui->bloodFootprintMaskLabel, &EvidenceMaskView::enterMaskSignal, bloodFootprintsLabel, &EvidenceView::enterEventFromMask);
    connect(ui->bloodFootprintMaskLabel, &EvidenceMaskView::leaveMaskSignal, bloodFootprintsLabel, &EvidenceView::leaveEventFromMask);
    connect(ui->bloodFootprintMaskLabel, &EvidenceMaskView::clickedMaskSignal, bloodFootprintsLabel, &EvidenceView::clickedSignal);
    //BLOOD ON TILE MASK:
    connect(ui->bloodFloorMaskLabel, &EvidenceMaskView::enterMaskSignal, bloodFloorLabel, &EvidenceView::enterEventFromMask);
    connect(ui->bloodFloorMaskLabel, &EvidenceMaskView::leaveMaskSignal, bloodFloorLabel, &EvidenceView::leaveEventFromMask);
    connect(ui->bloodFloorMaskLabel, &EvidenceMaskView::clickedMaskSignal, bloodFloorLabel, &EvidenceView::clickedSignal);

    connect(ui->exitButton, SIGNAL(clicked()), exitDialog, SLOT(exec()));

    //reset button
    connect(this, &KitchenScene::startOver, model, &Model::retryCleaning);
    connect(model, &Model::clearSteps, ui->evidenceDialog, &itemDialog::clearSteps);
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

    model->addCleaningTool(GLOVE, glove);
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

    knife->setStartValues({water, bleach, rag}, "Bloody knife. I'll probably want to rinse it, then do something about that blood.");
    knife->educationalURL = "https://slate.com/news-and-politics/2007/11/is-it-possible-to-clean-dna-off-a-knife.html";

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
    bloodFloor->setStartValues({bleach, oxiclean, rag}, "Bloody stain on the floor. This is gonna be tough to get out. I need to cleanse this and mop it up fast.");
    bloodFloor->educationalURL = "https://medium.com/@lorensschuler/blood-cleanup-experts-how-to-get-rid-of-blood-stains-from-cement-surfaces-f66439b9a91c";
    ui->bloodFloorMaskLabel->setEvidenceEnum(BLOOD_TILE);

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
    handprint->setStartValues({nailPolishRemover, water, rag}, "Oily handprint on glass. I should make sure I remove the oils before I rinse and dry this mess.");
    handprint->educationalURL = "https://www.youtube.com/watch?v=mc_l1d--0nQ";


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
    bloodyFootprints->setStartValues({bleach, oxiclean, rag}, "Bloody footprints on floor. Ugh, someone stepped in the pool of blood. Ill have to clean this the same way.");
    bloodyFootprints->educationalURL = "https://www.sciencenewsforstudents.org/article/clean-getaway";
    ui->bloodFootprintMaskLabel->setEvidenceEnum(BLOOD_FOOTPRINT);

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
    bloodyWall->setStartValues({bleach, oxiclean, rag}, "Blood splatter on wooden wall. Man, this made a huge mess. I should probably cleanse and treat the stain.");
    bloodyWall->educationalURL = "https://www.youtube.com/watch?v=u73H-5-RP5Y";

    // initialize gunpowder residue
    Evidence* gunpowderWall = new Evidence();
    gunpowderWall->setPixmaps(QPixmap(":/art/interactables/gunpowder_wall_01"),
                           QPixmap(":/art/interactables/gunpowder_wall_highlighted_01"),
                           QPixmap(),
                           QPixmap(":/art/interactables/gunpowder_wall_clean_highlighted_01"),
                           QPixmap(),
                           QPixmap(":/art/interactables/gunpowder_wall_clean_highlighted_01"));
    gunpowderWallLabel->setType(GUNPOWDER_WALL);
    evidenceLabels.insert(GUNPOWDER_WALL, gunpowderWallLabel);
    model->addEvidence(GUNPOWDER_WALL, gunpowderWall);
    gunpowderWallLabel->setModel(model->getEvidence(GUNPOWDER_WALL));
    gunpowderWall->setStartValues({rag, water, nailPolishRemover}, "Gunpowder on painted wood and ceramic. Ill bet I can wipe most of it, but It will probably need a rinse and something else for the residue.");
    gunpowderWall->educationalURL = "https://www.youtube.com/watch?v=FgoKZgSCsYY";

}

void KitchenScene::initializeEvidence(){
    knifeLabel = ui->knifeLabel;
    bloodFloorLabel = ui->bloodFloorLabel;
    oilyHandLabel = ui->oilyHandLabel;
    bloodFootprintsLabel = ui->bloodFootprintLabel;
    bloodWallLabel = ui->bloodWallLabel;
    gunpowderWallLabel = ui->gunpowderLabel;
}

void KitchenScene::deselectEvidenceSlot(EvidenceEnum selectedEvidence){
    evidenceLabels[selectedEvidence]->unhighlightEvidence();
    ui->resetButton->hide();
}

void KitchenScene::setSelectedEvidenceSlot(EvidenceEnum selectedEvidence){
    QHash<EvidenceEnum, EvidenceView*>::iterator it;
    for (it = evidenceLabels.begin(); it != evidenceLabels.end(); it++){
        it.value()->unhighlightEvidence();
    }
    evidenceLabels[selectedEvidence]->highlightEvidence();
    ui->resetButton->show();
}

void KitchenScene::exitSceneSlot(){
    double finalScore = model->getFinalScorePercentage();
    if (finalScore > 70){
        emit changeScene(ENDING);
    } else {
        emit changeScene(MINIGAME);
    }
}

void KitchenScene::on_resetButton_clicked()
{
    emit(startOver());
}
void KitchenScene::on_backButton_clicked()
{
    emit changeScene(MAINMENU);
}
