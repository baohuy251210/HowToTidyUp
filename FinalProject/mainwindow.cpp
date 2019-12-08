#include "mainwindow.h"
#include "ui_mainwindow.h"

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

}

void MainWindow::setupConnections(){
    connect(currentScene, &IScene::changeScene, this, &MainWindow::ChangeScene);

}

MainWindow::~MainWindow(){
    delete ui;
    delete currentScene;
    delete introScene;
    delete endScene;
    delete losingMinigame;
    delete mainmenuScene;
    delete kitchenScene;
}

void MainWindow::initializeModel(){
    model = new Model(this);
}

/**MUSIC:*/
void MainWindow::setupMusic(){
    musicFiles.push_back(new QResource(":/introdata/theme"));
    musicFiles.push_back(new QResource(":/introdata/theme2"));
    musicFiles.push_back(new QResource(":/introdata/theme3"));
    musicFiles.push_back(new QResource(":/introdata/theme4"));
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
        musicPlayNext();
        overlayMusic.setVolume(1);
        mainThemeMusic.setVolume(5);
        break;
    case KITCHEN_LOAD:
        kitchenScene = new KitchenScene(this, model);
        currentScene = kitchenScene;
        kitchenScene->loadGameKitchen();
        musicPlayNext();
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
    case MINIGAME:
        losingMinigame = new LosingMinigame(this);
        currentScene = losingMinigame;
        break;

    }
    connect(currentScene, &IScene::changeScene, this, &MainWindow::ChangeScene);
    ui->SceneContainer->addWidget(currentScene);


}

