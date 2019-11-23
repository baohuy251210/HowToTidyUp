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
