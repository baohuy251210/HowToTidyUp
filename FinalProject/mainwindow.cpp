#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainmenuscene.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){

    ui->setupUi(this);
    currentScene = new MainMenuScene(this);
    ui->SceneContainer->addWidget(currentScene);
}

MainWindow::~MainWindow(){
    delete ui;
    delete currentScene;
}

void MainWindow::ChangeScene(IScene* scene){
    ui->SceneContainer->removeWidget(currentScene);
    currentScene = scene;
    connect(scene, &IScene::changeScene, this, &MainWindow::ChangeScene);
    ui->SceneContainer->addWidget(scene);
}
