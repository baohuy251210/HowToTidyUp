#include "kitchenscene.h"
#include "ui_kitchenscene.h"
#include "ToolsEnum.cpp"
KitchenScene::KitchenScene(QWidget *parent) :
    IScene(parent),
    ui(new Ui::KitchenScene)
{
    ui->setupUi(this);
    QImage cleanKnife = QImage(":/art/interactables/Art/Interactables/knife_bloody_01.png");
    QPixmap pm = QPixmap::fromImage(cleanKnife);
    ui->knifeLabel->setPixmap(pm);
    /*connect add knife (test)*/

}

KitchenScene::~KitchenScene()
{
    delete ui;
}
