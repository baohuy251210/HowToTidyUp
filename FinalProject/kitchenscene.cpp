#include "kitchenscene.h"
#include "ui_kitchenscene.h"
#include "ToolsEnum.cpp"
#include <QDebug>

KitchenScene::KitchenScene(QWidget *parent) :
    IScene(parent),
    ui(new Ui::KitchenScene)
{
    ui->setupUi(this);
    QImage cleanKnife = QImage(":/art/interactables/Art/Interactables/knife_bloody_01.png");
    QPixmap pm = QPixmap::fromImage(cleanKnife);
    ui->knifeLabel->setPixmap(pm);
    /*connect add knife (test)*/
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
