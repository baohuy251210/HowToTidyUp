#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainmenuscene.h"
#include "introscene.h"
#include "kitchenscene.h"
#include "model.h"
#include <QDebug>
#include <QResource>
#include <SFML/Audio.hpp>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){

    qDebug() << "MAINWINDOW";
    ui->setupUi(this);
    initializeModel();
    initializeScenes();
    startThemeMusic();
    currentScene = introScene;
    setupConnections();
    ui->SceneContainer->addWidget(currentScene);
//    qDebug() << currentScene;
}

void MainWindow::initializeScenes(){
    introScene = new IntroScene(this);
//   mainmenuScene = new MainMenuScene(this);
//    mainmenuScene->hide();
//    kitchenScene = new KitchenScene(this);
//    kitchenScene->hide();
}

void MainWindow::setupConnections(){
    connect(currentScene, &IScene::changeScene, this, &MainWindow::ChangeScene);
    //connect(currentScene, SIGNAL(KitchenScene::signalUseToolAndEvidence(Tools, QString)), model, SLOT(signalUseToolAndEvidence(Tools, QString)));
//    connect(kitchenScene, &KitchenScene::signalUseToolAndEvidence, model, &Model::slotUsedToolAndEvidence);

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
    qDebug() << "MW:Changescene";
    ui->SceneContainer->removeWidget(currentScene);
    delete currentScene;
    switch (sceneEnum){
    case INTRO1:
        currentScene = introScene;
        break;
    case KITCHEN:
        qDebug() <<"MW:change to kitchen";
        kitchenScene = new KitchenScene(this);
//        kitchenScene->show();
        currentScene = kitchenScene;
        connect(kitchenScene, &KitchenScene::signalUseToolAndEvidence, model, &Model::slotUsedToolAndEvidence);
        break;
    case MAINMENU:
        mainmenuScene = new MainMenuScene(this);
//        mainmenuScene->show();
        currentScene = mainmenuScene;
        break;
    default:
        break;
    }
    connect(currentScene, &IScene::changeScene, this, &MainWindow::ChangeScene);
    ui->SceneContainer->addWidget(currentScene);
}

void MainWindow::evidenceInteractionSlot(){

}
