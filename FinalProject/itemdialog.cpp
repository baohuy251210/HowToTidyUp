#include "itemdialog.h"
#include "ui_itemdialog.h"

itemDialog::itemDialog(QWidget *parent) :
    IScene(parent),
    ui(new Ui::itemDialog)
{
    ui->setupUi(this);
    this->hide();
    //connect(hintButton, &QToolButton::pressed, model, &Model::hideDialogSlot);
    connect(ui->hintButton, &QToolButton::clicked, this, &itemDialog::toggleHintVisibleSlot);

    initDictionary();
}

itemDialog::~itemDialog()
{
    delete ui;
}

void itemDialog::setEvidence(Evidence* evidence){
    clearEvidenceSlot();
    this->show();
    ui->itemDescription->setText(evidence->description);
    QString hintText = "";

    for(int i = 0; i < 3; i++){
        hintText += mapToolsString[evidence->getCorrectTools().at(i)->getType()];
        if(i < 2){hintText += ", ";}
    }


    ui->itemHint->setText(hintText);
    ui->itemHint->setVisible(false);
    drawTextLabel(ui->itemDescription, 13, "SF Cartoonist Hand");
    drawTextLabel(ui->itemHint, 10, "SF Cartoonist Hand");
    ui->itemPicture->setPixmap(*evidence->getIcon());

    QList<CleaningTool*>* usedTools = evidence->getUsedTools();

    if(usedTools->size() > 0 && usedTools->at(0) != nullptr && usedTools->at(0)->getType() != EMPTY){
       ui->step1->setPixmap(usedTools->at(0)->getIcon());
    }

    if(usedTools->size() > 1 && usedTools->at(0) != nullptr && usedTools->at(1)->getType() != EMPTY){
       ui->step2->setPixmap(usedTools->at(1)->getIcon());
    }

    if(usedTools->size() > 2 && usedTools->at(0) != nullptr && usedTools->at(2)->getType() != EMPTY){
       ui->step3->setPixmap(usedTools->at(2)->getIcon());
    }
}

void itemDialog::clearEvidenceSlot(){
    ui->itemDescription->setText("");
    ui->itemHint->setText("");
    ui->itemPicture->clear();
    ui->step1->clear();
    ui->step2->clear();
    ui->step3->clear();
}
void itemDialog::clearSteps(){
    ui->step1->clear();
    ui->step2->clear();
    ui->step3->clear();
}

void itemDialog::hideDialogSlot(){
    this->hide();
}

void itemDialog::initDictionary(){
    mapToolsString.insert(EMPTY, "EMPTY");
    mapToolsString.insert(GLOVE, "GLOVE");
    mapToolsString.insert(WATER, "WATER");
    mapToolsString.insert(NAILPOLISHREMOVER, "NAILPOLISHREMOVER");
    mapToolsString.insert(BLEACH, "BLEACH");
    mapToolsString.insert(RAG, "RAG");
    mapToolsString.insert(OXICLEAN, "OXICLEAN");
}

void itemDialog::toggleHintVisibleSlot(){
    ui->itemHint->setVisible(!(ui->itemHint->isVisible()));
}
