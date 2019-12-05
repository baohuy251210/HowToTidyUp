#include "toolbarwidget.h"
#include "ui_toolbarwidget.h"
#include "ToolsEnum.cpp"

ToolbarWidget::ToolbarWidget(QWidget *parent) :
    IScene(parent),
    ui(new Ui::ToolbarWidget)
{
    ui->setupUi(this);

    glove = ui->gloveButton;
    bleach = ui->bleachButton;
    oxiclean = ui->oxicleanButton;
    water = ui->waterButton;
    nailpolish_remover = ui->nailPolishRemoverButton;
    rag = ui->ragButton;

    // hide popups
    ui->glovePopup->setVisible(false);
    ui->bleachPopup->setVisible(false);
    ui->oxicleanPopup->setVisible(false);
    ui->waterBucketPopup->setVisible(false);
    ui->ragPopup->setVisible(false);
    ui->nailPolishRemoverPopup->setVisible(false);
    setupTextFonts();
    setupConnections();

}

void ToolbarWidget::setModel(Model * model){
    this->model = model;


}

ToolbarWidget::~ToolbarWidget()
{
    delete ui;

}

void ToolbarWidget::displayDescriptionSlot(Tools tool){
    switch(tool){
    case GLOVE:
        ui->glovePopup->setText(glove->model->description);
        ui->glovePopup->hide();
        ui->glovePopup->show();
        break;
    case WATER:
        ui->waterBucketPopup->setText(water->model->description);
        ui->waterBucketPopup->setVisible(true);
        break;
    case NAILPOLISHREMOVER:
        ui->nailPolishRemoverPopup->setText(nailpolish_remover->model->description);
        ui->nailPolishRemoverPopup->setVisible(true);
        break;
    case BLEACH:
        ui->bleachPopup->setText(bleach->model->description);
        ui->bleachPopup->setVisible(true);
        break;
    case RAG:
        ui->ragPopup->setText(rag->model->description);
        ui->ragPopup->setVisible(true);
        break;
    case OXICLEAN:
        ui->oxicleanPopup->setText(oxiclean->model->description);
        ui->oxicleanPopup->setVisible(true);
        break;
    case EMPTY:
        break;

    }
}

void ToolbarWidget::hideDescriptionSlot(Tools tool){
    switch(tool){
    case GLOVE:
        ui->glovePopup->setVisible(false);
        break;
    case WATER:
        ui->waterBucketPopup->setVisible(false);
        break;
    case NAILPOLISHREMOVER:
        ui->nailPolishRemoverPopup->setVisible(false);
        break;
    case BLEACH:
        ui->bleachPopup->setVisible(false);
        break;
    case RAG:
        ui->ragPopup->setVisible(false);
        break;
    case OXICLEAN:
        ui->oxicleanPopup->setVisible(false);
        break;
    case EMPTY:
        break;

    }


}

void ToolbarWidget::setupTextFonts(){
    drawTextLabel(ui->glovePopup, 16, "SF Cartoonist Hand");
    drawTextLabel(ui->waterBucketPopup, 16, "SF Cartoonist Hand");
    drawTextLabel(ui->nailPolishRemoverPopup, 16, "SF Cartoonist Hand");
    drawTextLabel(ui->bleachPopup, 16, "SF Cartoonist Hand");
    drawTextLabel(ui->ragPopup, 16, "SF Cartoonist Hand");
    drawTextLabel(ui->oxicleanPopup, 16, "SF Cartoonist Hand");
}

void ToolbarWidget::setupConnections(){
    connect(glove, &CleaningToolView::displayDescription, this, &ToolbarWidget::displayDescriptionSlot);
    connect(glove, &CleaningToolView::hideDescription, this, &ToolbarWidget::hideDescriptionSlot);
    connect(water, &CleaningToolView::displayDescription, this, &ToolbarWidget::displayDescriptionSlot);
    connect(water, &CleaningToolView::hideDescription, this, &ToolbarWidget::hideDescriptionSlot);
    connect(rag, &CleaningToolView::displayDescription, this, &ToolbarWidget::displayDescriptionSlot);
    connect(rag, &CleaningToolView::hideDescription, this, &ToolbarWidget::hideDescriptionSlot);
    connect(nailpolish_remover, &CleaningToolView::displayDescription, this, &ToolbarWidget::displayDescriptionSlot);
    connect(nailpolish_remover, &CleaningToolView::hideDescription, this, &ToolbarWidget::hideDescriptionSlot);
    connect(bleach, &CleaningToolView::displayDescription, this, &ToolbarWidget::displayDescriptionSlot);
    connect(bleach, &CleaningToolView::hideDescription, this, &ToolbarWidget::hideDescriptionSlot);
    connect(oxiclean, &CleaningToolView::displayDescription, this, &ToolbarWidget::displayDescriptionSlot);
    connect(oxiclean, &CleaningToolView::hideDescription, this, &ToolbarWidget::hideDescriptionSlot);

}
