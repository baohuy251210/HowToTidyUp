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
    setupMusic();
    //startThemeMusic();
    currentScene = introScene;
    setupConnections();
    ui->SceneContainer->addWidget(currentScene);


    musicPlaylistTimer = new QTimer(this);
    connect(musicPlaylistTimer, &QTimer::timeout, this, &MainWindow::musicPlayNext);
    musicPlaylistTimer->start(20);
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

/**MUSIC:*/
void MainWindow::setupMusic(){
    musicFiles.push_back(new QResource(":/introdata/theme"));
    musicFiles.push_back(new QResource(":/introdata/theme2"));
    /*current starts at the first music*/
    currentMusicIndex = 0;
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
    mainThemeMusic.stop();
    QResource musicfile(":/introdata/theme2");
    mainThemeMusic.openFromMemory(musicfile.data(), musicfile.size());
    mainThemeMusic.setVolume(7);
    mainThemeMusic.play();
    mainThemeMusic.setLoop(true);
    overlayMusic.setVolume(2);
}

void MainWindow::musicPlayNext(){
    mainThemeMusic.openFromMemory(musicFiles[currentMusicIndex]->data(), musicFiles[currentMusicIndex]->size());
    mainThemeMusic.setVolume(10);
    mainThemeMusic.play();
    mainThemeMusic.setLoop(true);
    musicPlaylistTimer->start(mainThemeMusic.getDuration().asMilliseconds());
    currentMusicIndex++;
    if (currentMusicIndex == musicFiles.size()){
        currentMusicIndex = 0;
    }
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
        currentScene = kitchenScene;

        overlayMusic.setVolume(1);
        mainThemeMusic.setVolume(5);
        break;
    case KITCHEN_LOAD:
        kitchenScene = new KitchenScene(this, model);
        currentScene = kitchenScene;
        kitchenScene->loadGameKitchen();
        overlayMusic.setVolume(1);
        mainThemeMusic.setVolume(5);
        break;
    case MAINMENU:
        mainmenuScene = new MainMenuScene(this);
        mainThemeMusic.setVolume(20);
        overlayMusic.setVolume(10);
        currentScene = mainmenuScene;
        break;
    case BEGIN:
        beginScene = new BeginScene(this);
        musicPlayNext();
        currentScene = beginScene;
        break;
    case ENDING:
        endScene = new EndScene01(this, model);
        currentScene = endScene;
        break;
    default:
        break;
    }
    connect(currentScene, &IScene::changeScene, this, &MainWindow::ChangeScene);
    ui->SceneContainer->addWidget(currentScene);


}

void MainWindow::evidenceInteractionSlot(){

}
