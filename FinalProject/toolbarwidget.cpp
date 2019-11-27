#include "toolbarwidget.h"
#include "ui_toolbarwidget.h"
#include "ToolsEnum.cpp"
ToolbarWidget::ToolbarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolbarWidget)
{
    ui->setupUi(this);

    glove = ui->gloveButton;
    bleach = ui->bleachButton;
    oxiclean = ui->oxicleanButton;
    water = ui->waterButton;
    nailpolish_remover = ui->nailPolishRemoverButton;
    rag = ui->ragButton;

}

void ToolbarWidget::setModel(Model * model){
    this->model = model;


}

ToolbarWidget::~ToolbarWidget()
{
    delete ui;

}


