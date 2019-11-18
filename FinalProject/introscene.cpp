#include "introscene.h"
#include "ui_introscene.h"

IntroScene::IntroScene(QWidget *parent) :
    IScene(parent),
    ui(new Ui::IntroScene)
{
    ui->setupUi(this);
}

IntroScene::~IntroScene()
{
    delete ui;
}
