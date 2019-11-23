#include "kitchenscene.h"
#include "ui_kitchenscene.h"
#include <QDebug>

KitchenScene::KitchenScene(QWidget *parent) :
    IScene(parent),
    ui(new Ui::KitchenScene)
{
    ui->setupUi(this);
    selectedEvidence = "";
    selectedCleaningTool = "";
    InitializeWidgets();
    setupConnections();
}

KitchenScene::~KitchenScene()
{
    delete ui;
}

void KitchenScene::InitializeWidgets(){
    cleaningTools = ui->toolbarWidget;

}

void KitchenScene::setupConnections(){
    connect(cleaningTools, SIGNAL(toolSelectedSignal(QString)), this, SLOT(toolSelectedSlot(QString)));
}

void KitchenScene::toolSelectedSlot(QString tool){
    qDebug() << tool << " selected" << endl;
    selectedCleaningTool = tool;
}
