#include "kitchenscene.h"
#include "ui_kitchenscene.h"

KitchenScene::KitchenScene(QWidget *parent) :
    IScene(parent),
    ui(new Ui::KitchenScene)
{
    ui->setupUi(this);
}

KitchenScene::~KitchenScene()
{
    delete ui;
}
