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
    initializeScenes();
    startThemeMusic();
    currentScene = introScene;
    ui->SceneContainer->addWidget(currentScene);
    setupConnections();
}

void MainWindow::initializeScenes(){
    introScene = new IntroScene(this);
    kitchenScene = new KitchenScene(this);
    mainmenuScene = new MainMenuScene(this);
}

void MainWindow::setupConnections(){
    connect(currentScene, &IScene::changeScene, this, &MainWindow::ChangeScene);
    //connect(currentScene, SIGNAL(KitchenScene::signalUseToolAndEvidence(Tools, QString)), model, SLOT(signalUseToolAndEvidence(Tools, QString)));
    //connect(currentScene, &KitchenScene::signalUseToolAndEvidence, model, &Model::slotUsedToolAndEvidence);
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
    QResource musicfile(":/introdata/theme");
    mainThemeMusic.openFromMemory(musicfile.data(), musicfile.size());
    mainThemeMusic.setVolume(100);
    mainThemeMusic.play();
}

void MainWindow::ChangeScene(Scene sceneEnum){
    ui->SceneContainer->removeWidget(currentScene);
//    delete currentScene;
    switch (sceneEnum){
    case INTRO1:
        currentScene = introScene;
        break;
    case KITCHEN:
        currentScene = kitchenScene;
        break;
    case MAINMENU:
        currentScene = mainmenuScene;
        break;
    default:
        break;
    }
//    connect(scene, &IScene::changeScene, this, &MainWindow::ChangeScene);
    ui->SceneContainer->addWidget(currentScene);
}

void MainWindow::evidenceInteractionSlot(){

}
