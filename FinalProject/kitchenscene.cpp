#include "kitchenscene.h"
#include "ui_kitchenscene.h"

KitchenScene::KitchenScene(QWidget *parent) :
    IScene(parent),
    ui(new Ui::KitchenScene)
{
    ui->setupUi(this);
    QImage cleanKnife = QImage(":/art/interactables/Art/Interactables/knife_bloody_01.png");
    QPixmap pm = QPixmap::fromImage(cleanKnife);
    ui->knifeLabel->setPixmap(pm);
//    connect(ui->knifeLabel);
}

KitchenScene::~KitchenScene()
{
    delete ui;
}
