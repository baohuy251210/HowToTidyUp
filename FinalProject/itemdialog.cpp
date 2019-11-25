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

void itemDialog::setDescription(QString description){
    ui->itemDescription->setText(description);
}

void itemDialog::setUsedTools(QList<Tools> tools){
    //ui->step1->setPixmap()
}
