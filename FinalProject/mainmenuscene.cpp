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

//    QUrl url = QUrl::fromLocalFile("fingerprints");
//    QUrl baseUrl = QUrl("");
//    QUrl fixed = baseUrl.resolved(url);

//    player->setMedia(url);

//    QString a = QFileInfo("fingerprints").absoluteFilePath();
//    QUrl url = QUrl::fromLocalFile(a);
//    player->setMedia(url);

//    vw->setGeometry(100,100,300,400);
//    vw->show();
//    player->play();

    drawTextLabel(ui->nameLabel, 65,"Hollows Free");
    drawTextPushButton(ui->newGameButton, 50,"Hollows Free");
    drawTextPushButton(ui->continueButton, 50,"Hollows Free");



    fadeOpacity = 100; //percentage
    ui->maskLabel->setStyleSheet("background-color: rgb(0,0,0)");
    fadeTimer = new QTimer(this);
    connect(fadeTimer, &QTimer::timeout, this, &MainMenuScene::fadeWhiteFlash);
    fadeTimer->start(20);

    //gained from the same SO entry.
    ui->newGameButton->installEventFilter(this);
    ui->aMurder->setVisible(false);
    drawTextLabel(ui->aMurder, 50, "Fiendish", "Italic");

   // connect(this, &MainMenuScene::showFootprint, this, &MainMenuScene::showFootprintSlot);

    ui->continueButton->installEventFilter(this);

    ui->footprint1->setVisible(false);
    ui->footprint2->setVisible(false);
    ui->footprint3->setVisible(false);

    srand(time(0));
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

}



MainMenuScene::~MainMenuScene()
{
    delete ui;
}


void MainMenuScene::initializeBox2D(){
    //Start Box2D
    //initialize labels:
//    leafBodies.clear();
//    numLeaves+=3;
//    leafLabels.clear();
    if (isLastLeavesRow){
//        updateLeafTimer->stop();
//        qDebug() << "init";
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


//    hlayout->addWidget(ui->leaf1);
//    hlayout->addWidget(ui->leaf2);
//    hlayout->addWidget(ui->leaf3);
    int currentLblsSize = leafLabels.size();
    for (int i = 0; i<numLeaves; i+=3){
        leafLabels.push_back(new QLabel());
        leafLabels.last()->setPixmap(*ui->leaf1->pixmap());
        leafLabels.last()->setFixedSize(ui->leaf1->size());
        hlayout->addWidget(leafLabels.last());
//        leafLabels.last()->hide();

        leafLabels.push_back(new QLabel());
        leafLabels.last()->setPixmap(*ui->leaf2->pixmap());
        leafLabels.last()->setFixedSize(ui->leaf2->size());
        hlayout->addWidget(leafLabels.last());
//        leafLabels.last()->hide();

        leafLabels.push_back(new QLabel());
        leafLabels.last()->setPixmap(*ui->leaf3->pixmap());
        leafLabels.last()->setFixedSize(ui->leaf3->size());
        hlayout->addWidget(leafLabels.last());
//        leafLabels.last()->hide();
    }
    for (int i = 0; i < leafLabels.size();i++){
        leafLabels[i] ->hide();
    }
//    qDebug() <<"leaflbls:"<<leafLabels.size();
//    setLayout(hlayout);


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
    b2BodyDef bodyDef2, bodyDef3;
    QVector<b2BodyDef> leafBodiesDef;
    bodyDef.type = bodyDef2.type = bodyDef3.type = b2_dynamicBody;
    for (int i = 0; i < leafLabels.size(); i++){
        b2BodyDef newbodyDef;
        newbodyDef.type = b2_dynamicBody;
        leafBodiesDef.push_back(newbodyDef);
    }


    //init position
    bodyDef.position.Set(900.0f, 50.0f);
    bodyDef2.position.Set(950.0f, 60.0f);
    bodyDef3.position.Set(700.0f, 100.0f);
    bodyDef3.linearVelocity = bodyDef2.linearVelocity = bodyDef.linearVelocity = b2Vec2(0.0f, 0.0f);
    bodyDef3.angularVelocity = bodyDef2.angularVelocity = bodyDef.angularVelocity = 0.0f;

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
    body = world.CreateBody(&bodyDef);
    body2 = world.CreateBody(&bodyDef2);
    body3 = world.CreateBody(&bodyDef3);
    for (int i = 0; i < numLeaves; i++){
        leafBodies.push_back(world.CreateBody(&leafBodiesDef[i]));
    }
    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    b2FixtureDef fixtureDef2, fixtureDef3;
    fixtureDef3.shape = fixtureDef2.shape = fixtureDef.shape = &dynamicBox;
    QVector<b2FixtureDef> fixtureDefs;
    for (int i = 0; i < numLeaves; i++){
         b2FixtureDef newfixtureDef;
         newfixtureDef.shape = &dynamicBox;
        fixtureDefs.push_back(newfixtureDef);
        fixtureDefs[i].density = 1.0f;
    }
    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef3.density = fixtureDef2.density = fixtureDef.density = 1.0f;

    // Override the default friction.
    //fixtureDef.friction = 0.3f;

    //fixtureDef.restitution = 0.9f;
    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);
    body2->CreateFixture(&fixtureDef2);
    body3->CreateFixture(&fixtureDef3);

    for (int i = 0 ; i < leafLabels.size(); i++){
        leafBodies[i]->CreateFixture(&fixtureDefs[i%numLeaves]);
    }
    updateWorld();
    updateWorld();
//    updateLeafTimer->start(30);
//    qDebug() << "?";
//    updateWorld();
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

    if(obj == (QObject*)target){
        if(e->type() == QEvent::Enter) {

            ui->aMurder->setVisible(true);

        }else if(e->type() == QEvent::Leave){

            ui->aMurder->setVisible(false);
        }
    }
    else if (obj == (QObject*) continueButton)
    {
        if(e->type() == QEvent::Enter){//change event to MouseButtonRelease to get click functionality

            //QTimer::singleShot(500, this, SLOT(showFootprintSlot()));
            QTimer::singleShot(1, this, [this] () {ui->footprint1->raise(); showFootprintSlot(ui->footprint1); });
            QTimer::singleShot(500, this, [this] () {ui->footprint2->raise(); showFootprintSlot(ui->footprint2); });
            QTimer::singleShot(1000, this, [this] () {ui->footprint3->raise(); showFootprintSlot(ui->footprint3); });
            //uncomment to change scene to kitchen at end of animation
            //QTimer::singleShot(1500, this, [this] () {emit changeScene(KITCHEN); });
        }
    }
    else
    {
        return QWidget::eventFilter(obj, e);
    }
}

void MainMenuScene::on_continueButton_clicked()
{
    emit changeScene(KITCHEN);
}

void MainMenuScene::updateWorld(){


    static int updates = 0;
    static int direction = 1;
    static int direction1 = 1;
    static int direction2 = 1;
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


    // Now print the position and angle of the body.
    b2Vec2 position = body->GetWorldCenter();
    b2Vec2 position2 = body2->GetWorldCenter();
    b2Vec2 position3 = body3->GetWorldCenter();
    QVector<b2Vec2> positions(leafLabels.size());
    for (int i = 0; i < positions.size(); i++){
        positions[i]= leafBodies[i]->GetWorldCenter();
       // qDebug() << "positions[" << i << "]:" << positions[i].x << positions[i].y;
    }

    //qDebug() << "Position X: " << position.x << " Y: " << position.y;

    //Experimenting with apply force
    //Idea gained here:
    //https://www.youtube.com/watch?v=bJJbQIoJeFc
    //https://natureofcode.com/book/chapter-5-physics-libraries/#chapter05_section12
    int frc = rand() % 4000;
    if(updates % 15 == 0) {
        direction = rand() % 2;
        direction1 = rand() % 2;
        direction2 = rand() % 2;
        for (int i = 0; i < directions.size(); i++){
            directions[i] = rand() % 2;
         //   qDebug() << "directions[" << i << "]:" << directions[i];
        }
    }
    //qDebug() << "Frc: " << frc << " dir: " << direction;

    b2Vec2 force(direction?frc:-frc, 500.0f);
    b2Vec2 force2(direction1?frc:-frc, 100.0f);
    b2Vec2 force3(direction2?frc:-frc, 250.0f);
    QVector<b2Vec2> forces(leafLabels.size());
    for (int i = 0; i < forces.size(); i++){
        int roll1;
        int min = 100; // the min number a die can roll is 1
        int max = 500;// this->dieSize; // the max value is the die size
        roll1 = rand() % (max - min + 1) + min;
//        qDebug() << roll1;
        b2Vec2 tempForce(directions[i]?frc:-frc,  float(roll1));
        forces[i] = tempForce;
    }


    //body->SetAwake(true);
    if(updates % 7 == 0){

    }
    else if(updates % 5 == 0){

    }
    else if (updates % 9 == 0) {

    }

//    if (leafLabels.size() == 30)
//        qDebug() << "?" << leafBodies.size() << forces.size();

    body->ApplyForce(force, body->GetWorldCenter(), true);
    body2->ApplyForce(force2, body2->GetWorldCenter(), true);
    body3->ApplyForce(force3, body3->GetWorldCenter(), true);
    for (int i = 0; i < leafLabels.size(); i++){
        leafBodies[i]->ApplyForce(forces[i], leafBodies[i]->GetWorldCenter(), true);
    }

    // Instruct the world to perform a single step of simulation.
    // It is generally best to keep the time step and iterations fixed.
    world.Step(timeStep, velocityIterations, positionIterations);

    //float32 angle = body->GetAngle();

    emit(newPosition(position, position2, position3, positions));


//    QTimer::singleShot(30, this, &MainMenuScene::updateWorld);
    //printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);

}

void MainMenuScene::changeGeometry(b2Vec2 position, b2Vec2 position2, b2Vec2 position3, QVector<b2Vec2> positions){
   // ui->leaf1->setGeometry(position.x, position.y, ui->leaf1->width(),ui->leaf1->height());
  //  ui->leaf2->setGeometry(position2.x, position2.y, ui->leaf2->width(),ui->leaf2->height());
  //  ui->leaf3->setGeometry(position3.x, position3.y, ui->leaf3->width(),ui->leaf3->height());
    for (int i = 0; i < positions.size(); i++){
//        leafLabels[i]->hide();
        leafLabels[i]->setGeometry(positions[i].x, positions[i].y, leafLabels[i]->width(), leafLabels[i]->height());
   //r qDebug() << "positions[" << i << "]:" << positions[i].x << positions[i].y;
        leafLabels[i]->show();
    }
}

void MainMenuScene::showFootprintSlot(QLabel* footprint) {
    footprint->raise();
    qDebug() << "?";
    footprint->setVisible(true);
}







