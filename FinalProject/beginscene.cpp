#include "beginscene.h"
#include "ui_beginscene.h"
#include "introreader.h"
#include "mainmenuscene.h"
#include <QTimer>
#include <QImage>
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <QResource>
#include <QMouseEvent>
#include <QPixmap>
BeginScene::BeginScene(QWidget *parent) :
    IScene(parent),
    ui(new Ui::BeginScene)
{
    ui->setupUi(this);
    /*Logo*/
    //logo = QPixmap(":/introdata/IntroData/Senary10_logo.png");
    ui->logoLbl->setFixedSize(1024, 768);
    ui->logoLbl->setStyleSheet("background-color: rgb(15, 15, 15);");
    isLogoDisplayed = false;
    logoSize = QSize(10, 10);
    drawTextLabel(ui->continueLbl, 15, "SF Cartoonist Hand", "Italic");
    ui->continueLbl->hide();
    /*Read resources*/
    QFile file(":/introdata/begin");
    file.open(QIODevice::ReadOnly);
    QResource fontfile(":/introdata/SF_Cartoonist_Hand");
    QByteArray content = file.readAll();
    introReader.readFromFile(QJsonDocument().fromJson(content));
    /*Timers*/
    fadeTimer = new QTimer(this);
    textStartTimer = new QTimer(this);
    logoTimer=new QTimer(this);
    creditFadeTimer = new QTimer(this);
    flashContinueTimer = new QTimer(this);
    fadeOpacity=100;
    connect(textStartTimer, &QTimer::timeout, this, &BeginScene::displayNextContext);
    connect(fadeTimer, &QTimer::timeout, this, &BeginScene::fadeText);
    connect(logoTimer, &QTimer::timeout, this, &BeginScene::displayLogo);
    connect(creditFadeTimer, &QTimer::timeout, this, &BeginScene::displayCredit);
    connect(flashContinueTimer, &QTimer::timeout, this, &BeginScene::flashContinueLabel);
    flashContinueTimer->start(500);
    logoTimer->start(2);
    /*inits*/
    ui->textLbl->setAlignment(Qt::AlignCenter);
}

BeginScene::~BeginScene()
{
    delete ui;
}


void BeginScene::flashContinueLabel(){
    if (ui->continueLbl->styleSheet() == "color: rgb(250, 80, 80)"){
        ui->continueLbl->setStyleSheet("color: rgb(200, 200, 200)");
    }
    else {
         ui->continueLbl->setStyleSheet("color: rgb(250, 80, 80)");
    }
}


void BeginScene::renderDefaultBlack(){
    ui->sceneLbl->setStyleSheet("background-color: rgb(0, 0, 0);");
}

void BeginScene::displayLogo(){
    if (logoSize.width() >= 100){
        logoTimer->stop();
        fadeOpacity = 5;
        creditFadeTimer->start(1);
        isLogoDisplayed=true;
    }
    else {
        logoTimer->setInterval(50);
        zoomLogo();
    }
}

void BeginScene::displayCredit(){
    creditFadeTimer->setInterval(50);
    if (fadeOpacity < 100){
        drawTextLabel(ui->creditLbl, 60, "Hollows Free");
        ui->creditLbl->setText("A MURDER");
        ui->creditLbl->setStyleSheet("color: rgba(255, 255, 255,"+QString::number(fadeOpacity)+"%);");
        fadeOpacity += 2;
    }
    else {
        textStartTimer->start(2000);
        ui->continueLbl->show();
        ui->creditLbl->setStyleSheet("color: rgba(255, 80, 80, 90%);");
        ui->logoLbl->setStyleSheet("background-color: black;color: rgb(255, 80, 80);");
        creditFadeTimer->stop();

    }
}

void BeginScene::zoomLogo(){
    logoSize.setWidth(logoSize.width()+2);
    logoSize.setHeight(logoSize.height()+2);
    if (logoSize.width() <=100){
        drawTextLabel(ui->logoLbl, logoSize.width(),"Hollows Free");
        ui->logoLbl->setText("HOW TO TIDY UP");
        ui->logoLbl->setStyleSheet("background-color: black;color: rgb(240, 240, 240);");
    }
    else isLogoDisplayed = true;
}

void BeginScene::displayNextContext(){
    if (introReader.reachEndOfText()){
        textStartTimer->stop();
        fadeTimer->stop();
        emit changeScene(KITCHEN);
        return;
    }
    else textStartTimer->setInterval(introReader.nextMsDelay());
    ui->logoLbl->setPixmap(QPixmap(0,0));
    ui->logoLbl->setVisible(false);
    ui->creditLbl->setVisible(false);
    renderDefaultBlack();
    fadeOpacity = 1;
    currentText = introReader.nextText();
    if (currentText == "..."){
        playCrimeEffects();
    }
    if (currentText == "10:30AM"){
        playWakeEffects();
    }
    fadeTimer->start(20);
}

void BeginScene::fadeText(){
    QString displayText = currentText;
    if (fadeOpacity <100){
        ui->textLbl->setText(displayText);
        drawTextLabel(ui->textLbl, 40);
        ui->textLbl->setStyleSheet("color: rgba(255, 255, 255,"+QString::number(fadeOpacity)+"%);");
        fadeOpacity++;
    }
    else {
        fadeTimer->stop();
    }
}

void BeginScene::playCrimeEffects(){
    QResource fxDragFile(":/soundeffects/dragoverwood2");
    QResource fxStabFile(":/soundeffects/knifestab");
    fxDrag.openFromMemory(fxDragFile.data(), fxDragFile.size());
    fxStab.openFromMemory(fxStabFile.data(), fxStabFile.size());
    fxDrag.setVolume(100);
    fxStab.setVolume(40);
    fxStab.setLoop(false);
    fxDrag.setLoop(false);
    fxStab.play();
    fxDrag.play();
}
void BeginScene::playWakeEffects(){
    fxStab.stop();
    fxDrag.stop();
    QResource fxYawnFile(":/soundeffects/maleyawn");
    fxYawn.openFromMemory(fxYawnFile.data(), fxYawnFile.size());
    fxYawn.setVolume(10);
    fxYawn.setLoop(false);
    fxYawn.play();
}

void BeginScene::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
            if (isLogoDisplayed)
                displayNextContext();
            }
}
