#include "itemdialog.h"
#include "ui_itemdialog.h"

itemDialog::itemDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::itemDialog)
{
    ui->setupUi(this);
}

itemDialog::~itemDialog()
{
    delete ui;
}

void itemDialog::setEvidence(Evidence* evidence){
    ui->itemDescription->setText(evidence->description);
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
    ui->itemPicture->clear();
}
