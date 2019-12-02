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
    currentScene = introScene;
    setupConnections();
    ui->SceneContainer->addWidget(currentScene);
}

void MainWindow::initializeScenes(){
    introScene = new IntroScene(this);
    //    mainmenuScene = new MainMenuScene(this);
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
    mainThemeMusic.setLoop(true);
    QResource overlayfile(":/introdata/windsound.ogg");
    overlayMusic.openFromMemory(overlayfile.data(), overlayfile.size());
    overlayMusic.setVolume(50);
    overlayMusic.play();
    overlayMusic.setLoop(true);
}
void MainWindow::startInGameMusic(){
    QResource musicfile(":/introdata/jazzpiano");
    mainThemeMusic.openFromMemory(musicfile.data(), musicfile.size());
    mainThemeMusic.setVolume(30);
    mainThemeMusic.play();
    mainThemeMusic.setLoop(true);
    overlayMusic.setVolume(10);
}


void MainWindow::ChangeScene(Scene sceneEnum){
    ui->SceneContainer->removeWidget(currentScene);
    delete currentScene;
    switch (sceneEnum){
    case INTRO:
        introScene = new IntroScene(this);
        currentScene = introScene;
        break;
    case KITCHEN:
        kitchenScene = new KitchenScene(this, model);
        startInGameMusic();
        currentScene = kitchenScene;
        break;
    case MAINMENU:
        mainmenuScene = new MainMenuScene(this);
        currentScene = mainmenuScene;
        break;
    case BEGIN:
        beginScene = new BeginScene(this);
        currentScene = beginScene;
    default:
        break;
    }
    connect(currentScene, &IScene::changeScene, this, &MainWindow::ChangeScene);
    ui->SceneContainer->addWidget(currentScene);
}

void MainWindow::evidenceInteractionSlot(){

}
