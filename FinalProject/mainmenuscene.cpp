#include "mainmenuscene.h"
#include "ui_mainmenuscene.h"
#include <kitchenscene.h>
#include <QDebug>
#include "Box2D/Box2D.h"
#include <QResource>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileInfo>
#include <QHBoxLayout>
#include<QNetworkProxyFactory>
#include <QSound>

MainMenuScene::MainMenuScene(QWidget *parent) :
    IScene(parent),
    world(b2Vec2(0.0f, 0.0f)),
    ui(new Ui::MainMenuScene)
{
    ui->setupUi(this);
    ui->maskLabel->setFixedSize(QSize(1024,768));

    //Video widget test
    QMediaPlayer* player = new QMediaPlayer;
    QVideoWidget* vw = new QVideoWidget;
    player->setVideoOutput(vw);

    fadeOpacity = 100; //percentage
    ui->maskLabel->setStyleSheet("background-color: rgb(0,0,0)");
    fadeTimer = new QTimer(this);
    connect(fadeTimer, &QTimer::timeout, this, &MainMenuScene::fadeWhiteFlash);
    fadeTimer->start(20);

    //gained from the same SO entry.
    ui->newGameButton->installEventFilter(this);
    ui->aMurder->setVisible(false);
    drawTextLabel(ui->aMurder, 50, "Fiendish", "Italic");
    drawTextLabel(ui->nameLabel, 45, "SF Cartoonist Hand SC", "Bold");
    drawTextPushButton(ui->newGameButton, 40, "SF Cartoonist Hand", "Bold");
    drawTextPushButton(ui->continueButton, 40, "SF Cartoonist Hand", "Bold");
    ui->continueButton->installEventFilter(this);

    ui->footprint1->setVisible(false);
    ui->footprint2->setVisible(false);
    ui->footprint3->setVisible(false);

    srand(time(nullptr));
    //Init Box2d
    numLeaves = 15;
    hlayout = new QHBoxLayout();
    setLayout(hlayout);
    isLastLeavesRow = false;


    replayLeafTimer = new QTimer(this);
    updateLeafTimer = new QTimer(this);
    initializeBox2D();
    connect(this, &MainMenuScene::newPosition, this, &MainMenuScene::changeGeometry);
    connect(replayLeafTimer, &QTimer::timeout, this, &MainMenuScene::initializeBox2D);
    connect(updateLeafTimer, &QTimer::timeout, this ,&MainMenuScene::updateWorld);
    updateLeafTimer->start(30);
    replayLeafTimer->start(7000);

    //add snow crunching sounds from resource paths
    soundCount = 0;
    soundFiles = {":/soundeffects/soundeffects/BootCrunchA.wav",
                  ":/soundeffects/soundeffects/BootCrunchB.wav",
                  ":/soundeffects/soundeffects/BootCrunchC.wav"};
}



MainMenuScene::~MainMenuScene()
{
    delete ui;
}


void MainMenuScene::initializeBox2D(){
    //Start Box2D
    //initialize labels:
    if (isLastLeavesRow){
        isLastLeavesRow = true;
        for (int i = 0; i < leafLabels.size(); i++)
            delete leafLabels[i];
        leafLabels.clear();
        leafBodies.clear();
    }

    if (leafLabels.size() >45){
        replayLeafTimer->setInterval(13000);
        isLastLeavesRow = true;
        return;
    }
    else{
        if (!updateLeafTimer->isActive()){
            updateLeafTimer->start(30);
        }
        isLastLeavesRow=false;
    }

   // int currentLblsSize = leafLabels.size();
    for (int i = 0; i<numLeaves; i+=3){
        leafLabels.push_back(new QLabel());
        leafLabels.last()->setPixmap(*ui->leaf1->pixmap());
        leafLabels.last()->setFixedSize(ui->leaf1->size());
        hlayout->addWidget(leafLabels.last());

        leafLabels.push_back(new QLabel());
        leafLabels.last()->setPixmap(*ui->leaf2->pixmap());
        leafLabels.last()->setFixedSize(ui->leaf2->size());
        hlayout->addWidget(leafLabels.last());

        leafLabels.push_back(new QLabel());
        leafLabels.last()->setPixmap(*ui->leaf3->pixmap());
        leafLabels.last()->setFixedSize(ui->leaf3->size());
        hlayout->addWidget(leafLabels.last());
    }

//    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 0.0f);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(1.0f, 1.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    QVector<b2BodyDef> leafBodiesDef;
    for (int i = 0; i < leafLabels.size(); i++){
        b2BodyDef newbodyDef;
        newbodyDef.type = b2_dynamicBody;
        leafBodiesDef.push_back(newbodyDef);
    }


    //init position

    for (int i = 0; i < leafBodiesDef.size(); i++){
        int rollx, rolly;
        int min = 700; // the min number a die can roll is 1
        int max = 950;// this->dieSize; // the max value is the die size
        rollx = rand() % (max - min + 1) + min;
        rolly = rand() % (150 - 20 + 1) + 20;
        leafBodiesDef[i].position.Set(rollx, rolly);
        leafBodiesDef[i].linearVelocity = b2Vec2(0.0f, 0.0f);
        leafBodiesDef[i].angularVelocity = 0.0f;
    }

    for (int i = 0; i < numLeaves; i++){
        leafBodies.push_back(world.CreateBody(&leafBodiesDef[i]));
    }
    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture.
    QVector<b2FixtureDef> fixtureDefs;
    for (int i = 0; i < numLeaves; i++){
         b2FixtureDef newfixtureDef;
         newfixtureDef.shape = &dynamicBox;
        fixtureDefs.push_back(newfixtureDef);
        fixtureDefs[i].density = 1.0f;
    }
    // Set the box density to be non-zero, so it will be dynamic.

    for (int i = 0 ; i < leafLabels.size(); i++){
        leafBodies[i]->CreateFixture(&fixtureDefs[i%numLeaves]);
    }
    updateWorld();
    updateWorld();
    updateWorld();
    updateWorld();
    updateWorld();
}

void MainMenuScene::fadeWhiteFlash(){
    QString maskStyleSheet ="background-color: rgba(255, 255, 255, "+QString::number(fadeOpacity)+"%);";
    ui->maskLabel->setStyleSheet(maskStyleSheet);
    fadeOpacity-=2;
    if (fadeOpacity <= 0){
        fadeTimer->stop();
        ui->maskLabel->setVisible(false);
    }
}

void MainMenuScene::on_newGameButton_clicked()
{
    emit changeScene(BEGIN);
}

//Method gained from this Stack overflow entry:
//https://stackoverflow.com/questions/9261175/how-to-emit-a-signal-from-a-qpushbutton-when-the-mouse-hovers-over-it
bool MainMenuScene::eventFilter(QObject *obj, QEvent *e){

    QPushButton* target = ui->newGameButton;
    QPushButton* continueButton = ui->continueButton;

    if(obj == dynamic_cast<QObject*>(target)){
        if(e->type() == QEvent::Enter) {

            ui->aMurder->setVisible(true);

        }else if(e->type() == QEvent::Leave){

            ui->aMurder->setVisible(false);
        }
    }
    else if (obj == dynamic_cast<QObject*>(continueButton))
    {
        if(e->type() == QEvent::Enter){//change event to MouseButtonRelease to get click functionality

            //QTimer::singleShot(500, this, SLOT(showFootprintSlot()));
            QTimer::singleShot(1, this, [this] () {ui->footprint1->raise(); showFootprintSlot(ui->footprint1); });
            QTimer::singleShot(750, this, [this] () {ui->footprint2->raise(); showFootprintSlot(ui->footprint2); });
            QTimer::singleShot(1500, this, [this] () {ui->footprint3->raise(); showFootprintSlot(ui->footprint3); });
            //uncomment to change scene to kitchen at end of animation
            //QTimer::singleShot(1500, this, [this] () {emit changeScene(KITCHEN); });
        }
    }
    else
    {
        return QWidget::eventFilter(obj, e);
    }
    updateWorld();
   return QWidget::eventFilter(obj, e);
}

void MainMenuScene::on_continueButton_clicked()
{
    emit changeScene(KITCHEN);
}

void MainMenuScene::updateWorld(){


    static int updates = 0;
    static QVector<int> directions;
    for (int i = 0; i < numLeaves; i++){
        directions.push_back(1);
    }
    updates++;

    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios.
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 12;
    int32 positionIterations = 4;

    //get the position of each leaf, to determine where to apply force.
    QVector<b2Vec2> positions(leafLabels.size());
    for (int i = 0; i < positions.size(); i++){
        positions[i]= leafBodies[i]->GetWorldCenter();
    }


    //Experimenting with apply force
    //Idea gained here:
    //https://www.youtube.com/watch?v=bJJbQIoJeFc
    //https://natureofcode.com/book/chapter-5-physics-libraries/#chapter05_section12

    int frc = rand() % 4000;
    //We update the direction every quarter second.
    if(updates % 15 == 0) {
        for (int i = 0; i < directions.size(); i++){
            //each leaf is given a direction, either 0,1 or in other words left/right.
            directions[i] = rand() % 2;
        }
    }

    //determine the force and direction of the force that will be applied to each leaf.
    QVector<b2Vec2> forces(leafLabels.size());
    for (int i = 0; i < forces.size(); i++){
        int roll1;
        int min = 100; // the min number a die can roll is 1
        int max = 500;// this->dieSize; // the max value is the die size
        roll1 = rand() % (max - min + 1) + min;
        b2Vec2 tempForce(directions[i]?frc:-frc,  float(roll1));
        forces[i] = tempForce;
    }


    //apply the forces to each leaf
    for (int i = 0; i < leafLabels.size(); i++){
        leafBodies[i]->ApplyForce(forces[i], leafBodies[i]->GetWorldCenter(), true);
    }

    // Instruct the world to perform a single step of simulation.
    // It is generally best to keep the time step and iterations fixed.
    world.Step(timeStep, velocityIterations, positionIterations);

    //Tell the leaves where to go.
    emit(newPosition(positions));

}

void MainMenuScene::changeGeometry(QVector<b2Vec2> positions){
    for (int i = 0; i < positions.size(); i++){
//        leafLabels[i]->hide();
        leafLabels[i]->setGeometry(positions[i].x, positions[i].y, leafLabels[i]->width(), leafLabels[i]->height());
        //leafLabels[i]->show();
    }
}

void MainMenuScene::showFootprintSlot(QLabel* footprint) {
    footprint->raise();
    playNextSnowCrunchSound();
    footprint->setVisible(true);
}

void MainMenuScene::playNextSnowCrunchSound(){
    if(soundCount < 3){
        QSound::play(soundFiles[soundCount]);
        soundCount++;
    }
}







