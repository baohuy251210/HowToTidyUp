#include "mainmenuscene.h"
#include "ui_mainmenuscene.h"
#include <kitchenscene.h>
#include <QDebug>


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
    fadeTimer->start(30);

    //gained from the same SO entry.
    ui->newGameButton->installEventFilter(this);
    ui->aMurder->setVisible(false);
    QFontDatabase::addApplicationFont(":/fonts/Fiendish.ttf");
    QFont creepy = QFont("Fiendish", 36, 1);
    ui->aMurder->setFont(creepy);

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
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(900.0f, 20.0f);
    bodyDef.linearVelocity = b2Vec2(0.0f, 0.0f);
    bodyDef.angularVelocity = 0.0f;

    body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    //fixtureDef.friction = 0.3f;

    //fixtureDef.restitution = 0.9f;
    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

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
//    qDebug() <<maskStyleSheet;
    ui->maskLabel->setStyleSheet(maskStyleSheet);
    fadeOpacity-=2;
    if (fadeOpacity <= 0){
        fadeTimer->stop();
        ui->maskLabel->setVisible(false);
    }

}

void MainMenuScene::on_newGameButton_clicked()
{
    KitchenScene* kitchen = new KitchenScene();
    emit changeScene(kitchen);
}

//Method gained from this Stack overflow entry:
//https://stackoverflow.com/questions/9261175/how-to-emit-a-signal-from-a-qpushbutton-when-the-mouse-hovers-over-it
bool MainMenuScene::eventFilter(QObject *obj, QEvent *e){
    QPushButton* target = ui->newGameButton;
    if(obj == (QObject*)target){
        if(e->type() == QEvent::Enter){

            ui->aMurder->setVisible(true);
        }else if(e->type() == QEvent::Leave){
            ui->aMurder->setVisible(false);
        }
    }
    else{

        return QWidget::eventFilter(obj, e);
    }
}

void MainMenuScene::on_continueButton_clicked()
{
    KitchenScene* kitchen = new KitchenScene();
    emit changeScene(kitchen);
}

void MainMenuScene::updateWorld(){
    static int updates = 0;
    static int direction = 1;
    updates ++;

    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios.
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;


    // Now print the position and angle of the body.
    b2Vec2 position = body->GetWorldCenter();
    qDebug() << "Position X: " << position.x << " Y: " << position.y;

    //Experimenting with apply force
    //Idea gained here:
    //https://www.youtube.com/watch?v=bJJbQIoJeFc
    //https://natureofcode.com/book/chapter-5-physics-libraries/#chapter05_section12
    int frc = rand() % 5000;
    if(updates % 30 == 0) {
        direction = rand() % 2;
    }
    qDebug() << "Frc: " << frc << " dir: " << direction;

    b2Vec2 force(-500.0f, direction?frc:-frc);
    //body->SetAwake(true);
    body->ApplyForce(force, body->GetWorldCenter(), true);

    // Instruct the world to perform a single step of simulation.
    // It is generally best to keep the time step and iterations fixed.
    world.Step(timeStep, velocityIterations, positionIterations);

    //float32 angle = body->GetAngle();

    emit(newPosition(position));
    QTimer::singleShot(30, this, &MainMenuScene::updateWorld);
    //printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);

}

void MainMenuScene::changeGeometry(b2Vec2 position){
    ui->leaf1->setGeometry(position.x, position.y, ui->leaf1->width(),ui->leaf1->height());


}



