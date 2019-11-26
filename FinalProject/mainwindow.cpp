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
    ui->setupUi(this);
    initializeModel();
    initializeScenes();
    startThemeMusic();
    currentScene = mainmenuScene;
    setupConnections();
    ui->SceneContainer->addWidget(currentScene);
}

void MainWindow::initializeScenes(){
    mainmenuScene = new MainMenuScene(this);
}

void MainWindow::setupConnections(){
    connect(currentScene, &IScene::changeScene, this, &MainWindow::ChangeScene);

}

MainWindow::~MainWindow(){
    delete ui;
    delete currentScene;
}

void MainWindow::initializeModel(){
    model = new Model(this);
}

void MainWindow::startThemeMusic(){
    QResource musicfile(":/introdata/theme");
    mainThemeMusic.openFromMemory(musicfile.data(), musicfile.size());
    mainThemeMusic.setVolume(100);
    mainThemeMusic.play();
}

void MainWindow::ChangeScene(Scene sceneEnum){
    ui->SceneContainer->removeWidget(currentScene);
    delete currentScene;
    switch (sceneEnum){
    case INTRO1:
        introScene = new IntroScene(this);
        currentScene = introScene;
        break;
    case KITCHEN:
        kitchenScene = new KitchenScene(this, model);
        currentScene = kitchenScene;
        break;
    case MAINMENU:
        mainmenuScene = new MainMenuScene(this);
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
