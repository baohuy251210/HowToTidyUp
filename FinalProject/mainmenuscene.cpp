#include "mainmenuscene.h"
#include "ui_mainmenuscene.h"

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
