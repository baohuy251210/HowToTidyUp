#include "mainmenuscene.h"
#include "ui_mainmenuscene.h"
#include <kitchenscene.h>
#include <QDebug>
#include "Box2D/Box2D.h"


MainMenuScene::MainMenuScene(QWidget *parent) :
    IScene(parent),
    world(b2Vec2(0.0f, 0.0f)),
    ui(new Ui::MainMenuScene)
{
    ui->setupUi(this);
    ui->maskLabel->setFixedSize(QSize(1024,768));

    drawTextLabel(ui->nameLabel, 50,"SF Cartoonist Hand", "Bold Italic");
    drawTextPushButton(ui->newGameButton, 40,"SF Cartoonist Hand");
    drawTextPushButton(ui->continueButton, 40,"SF Cartoonist Hand");


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

    //Start Box2D

    // Define the ground body.
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
    bodyDef.type = bodyDef2.type = bodyDef3.type = b2_dynamicBody;
    bodyDef.position.Set(900.0f, 50.0f);
    bodyDef2.position.Set(950.0f, 60.0f);
    bodyDef3.position.Set(700.0f, 100.0f);
    bodyDef3.linearVelocity = bodyDef2.linearVelocity = bodyDef.linearVelocity = b2Vec2(0.0f, 0.0f);
    bodyDef3.angularVelocity = bodyDef2.angularVelocity = bodyDef.angularVelocity = 0.0f;

    body = world.CreateBody(&bodyDef);
    body2 = world.CreateBody(&bodyDef2);
    body3 = world.CreateBody(&bodyDef3);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    b2FixtureDef fixtureDef2, fixtureDef3;
    fixtureDef3.shape = fixtureDef2.shape = fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef3.density = fixtureDef2.density = fixtureDef.density = 1.0f;

    // Override the default friction.
    //fixtureDef.friction = 0.3f;

    //fixtureDef.restitution = 0.9f;
    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);
    body2->CreateFixture(&fixtureDef2);
    body3->CreateFixture(&fixtureDef3);


    srand(time(0));

    connect(this, &MainMenuScene::newPosition, this, &MainMenuScene::changeGeometry);    

    QTimer::singleShot(30,this, &MainMenuScene::updateWorld);


}

MainMenuScene::~MainMenuScene()
{
    delete ui;
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
    emit changeScene(INTRO1);
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
            QTimer::singleShot(1, this, [this] () {showFootprintSlot(ui->footprint1); });
            QTimer::singleShot(500, this, [this] () {showFootprintSlot(ui->footprint2); });
            QTimer::singleShot(1000, this, [this] () {showFootprintSlot(ui->footprint3); });
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
    updates ++;

    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios.
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;


    // Now print the position and angle of the body.
    b2Vec2 position = body->GetWorldCenter();
    b2Vec2 position2 = body2->GetWorldCenter();
    b2Vec2 position3 = body3->GetWorldCenter();

    //qDebug() << "Position X: " << position.x << " Y: " << position.y;

    //Experimenting with apply force
    //Idea gained here:
    //https://www.youtube.com/watch?v=bJJbQIoJeFc
    //https://natureofcode.com/book/chapter-5-physics-libraries/#chapter05_section12
    int frc = rand() % 5000;
    if(updates % 15 == 0) {
        direction = rand() % 2;
        direction1 = rand() % 2;
        direction2 = rand() % 2;
    }
    //qDebug() << "Frc: " << frc << " dir: " << direction;

    b2Vec2 force(direction?frc:-frc, 500.0f);
    b2Vec2 force2(direction1?frc:-frc, 100.0f);
    b2Vec2 force3(direction2?frc:-frc, 250.0f);

    //body->SetAwake(true);
    if(updates % 7 == 0){

    }
    else if(updates % 5 == 0){

    }
    else if (updates % 9 == 0) {

    }

    body->ApplyForce(force, body->GetWorldCenter(), true);
    body2->ApplyForce(force2, body2->GetWorldCenter(), true);
    body3->ApplyForce(force3, body3->GetWorldCenter(), true);



    // Instruct the world to perform a single step of simulation.
    // It is generally best to keep the time step and iterations fixed.
    world.Step(timeStep, velocityIterations, positionIterations);

    //float32 angle = body->GetAngle();

    emit(newPosition(position, position2, position3));


    QTimer::singleShot(30, this, &MainMenuScene::updateWorld);
    //printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);

}

void MainMenuScene::changeGeometry(b2Vec2 position, b2Vec2 position2, b2Vec2 position3){
    ui->leaf1->setGeometry(position.x, position.y, ui->leaf1->width(),ui->leaf1->height());
    ui->leaf2->setGeometry(position2.x, position2.y, ui->leaf2->width(),ui->leaf2->height());
    ui->leaf3->setGeometry(position3.x, position3.y, ui->leaf3->width(),ui->leaf3->height());

}

void MainMenuScene::showFootprintSlot(QLabel* footprint) {
    footprint->setVisible(true);
}







