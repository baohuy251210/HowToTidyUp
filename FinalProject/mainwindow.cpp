#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainmenuscene.h"
#include "introscene.h"
#include "kitchenscene.h"
#include "model.h"
#include <QResource>
#include <SFML/Audio.hpp>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){

    ui->setupUi(this);
    initializeModel();
    startThemeMusic();
    currentScene = new IntroScene(this);
    connect(currentScene, &IScene::changeScene, this, &MainWindow::ChangeScene);
    ui->SceneContainer->addWidget(currentScene);
}

MainWindow::~MainWindow(){
    delete ui;
    delete currentScene;
}

void MainWindow::initializeModel(){
    model = new Model(this);
    model->addEvidenceObject("Knife",{WATER, BLEACH}, "It's a knife");
}

void MainWindow::startThemeMusic(){
    QResource musicfile(":/introdata/IntroData/theme.ogg");
    mainThemeMusic.openFromMemory(musicfile.data(), musicfile.size());
    mainThemeMusic.setVolume(100);
    mainThemeMusic.play();
}

void MainWindow::ChangeScene(IScene* scene){
    ui->SceneContainer->removeWidget(currentScene);
    delete currentScene;
    currentScene = scene;
    connect(scene, &IScene::changeScene, this, &MainWindow::ChangeScene);
    ui->SceneContainer->addWidget(scene);
}

void MainWindow::evidenceInteractionSlot(){

}
