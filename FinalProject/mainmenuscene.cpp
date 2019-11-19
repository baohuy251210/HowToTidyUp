#include "mainmenuscene.h"
#include "ui_mainmenuscene.h"
#include <kitchenscene.h>

MainMenuScene::MainMenuScene(QWidget *parent) :
    IScene(parent),
    ui(new Ui::MainMenuScene)
{
    ui->setupUi(this);
}

MainMenuScene::~MainMenuScene()
{
    delete ui;
}

void MainMenuScene::on_newGameButton_clicked()
{
    KitchenScene* kitchen = new KitchenScene();
    emit changeScene(kitchen);
}

void MainMenuScene::on_continueButton_clicked()
{
    KitchenScene* kitchen = new KitchenScene();
    emit changeScene(kitchen);
}
