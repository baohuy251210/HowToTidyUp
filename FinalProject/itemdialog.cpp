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
}

void itemDialog::clearEvidenceSlot(){
    ui->itemDescription->setText("");
    ui->itemPicture->clear();
}
