#include "introscene.h"
#include "ui_introscene.h"
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
IntroScene::IntroScene(QWidget *parent) :
    IScene(parent),
    ui(new Ui::IntroScene)
{
    ui->setupUi(this);
    /*Logo*/
    logo = QPixmap(":/introdata/IntroData/Senary10_logo.png");
    ui->logoLbl->setFixedSize(1024, 768);
    ui->logoLbl->setStyleSheet("background-color: rgb(15, 15, 15);");
    isLogoDisplayed = false;
    logoSize = QSize(10, 10);
    drawTextLabel(ui->continueLbl, 15, "SF Cartoonist Hand", "Italic");
    ui->continueLbl->hide();
    /*Read resources*/
    QFile file(":/introdata/intro");
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
    connect(textStartTimer, &QTimer::timeout, this, &IntroScene::displayNextContext);
    connect(fadeTimer, &QTimer::timeout, this, &IntroScene::fadeText);
    connect(logoTimer, &QTimer::timeout, this, &IntroScene::displayLogo);
    connect(creditFadeTimer, &QTimer::timeout, this, &IntroScene::displayCredit);
    connect(flashContinueTimer, &QTimer::timeout, this, &IntroScene::flashContinueLabel);
    flashContinueTimer->start(400);
    logoTimer->start(1);
    /*inits*/
    ui->textLbl->setAlignment(Qt::AlignCenter);
}

IntroScene::~IntroScene()
{
    delete ui;
}

void IntroScene::flashContinueLabel(){
    ui->continueLbl->setText("TAP TO CONTINUE");
    if (ui->continueLbl->styleSheet() == "color: rgb(250, 80, 80)"){
        ui->continueLbl->setStyleSheet("color: rgb(200, 200, 200)");
    }
    else {
         ui->continueLbl->setStyleSheet("color: rgb(250, 80, 80)");
    }
}

void IntroScene::renderDefaultBlack(){
    ui->sceneLbl->setStyleSheet("background-color: rgb(0, 0, 0);");
}

void IntroScene::displayLogo(){
    if (logoSize.width() >= 500){
        logoTimer->stop();
        fadeOpacity = 5;
        creditFadeTimer->start(1);
        isLogoDisplayed = true;

    }
    else {
        logoTimer->setInterval(10);
        zoomLogo();
    }
}

void IntroScene::displayCredit(){
    creditFadeTimer->setInterval(50);
    if (fadeOpacity < 100){
        drawTextLabel(ui->creditLbl, 55, "Black Night");
        ui->creditLbl->setText("THE SENARY TEN\nPRESENTS");
        ui->creditLbl->setStyleSheet("color: rgba(255, 255, 255,"+QString::number(fadeOpacity)+"%);");
        fadeOpacity += 1;
    }
    else {
        textStartTimer->start(1000);
        ui->continueLbl->setStyleSheet("color: rgb(250, 80, 80)");
        ui->continueLbl->show();

        creditFadeTimer->stop();

    }
}

void IntroScene::zoomLogo(){
    logoSize.setWidth(logoSize.width()+2);
    logoSize.setHeight(logoSize.height()+2);
    if (logoSize.width() <=400){
        ui->logoLbl->setPixmap(logo.scaled(logoSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->logoLbl->setAlignment(Qt::AlignCenter);
    }
    else isLogoDisplayed = true;
}

void IntroScene::displayNextContext(){
    if (introReader.reachEndOfText()){
        textStartTimer->stop();
        fadeTimer->stop();
        emit changeScene(MAINMENU);
        return;
    }
    else textStartTimer->setInterval(introReader.nextMsDelay());
    ui->continueLbl->show();
    ui->logoLbl->setPixmap(QPixmap(0,0));
    ui->logoLbl->setVisible(false);
    ui->creditLbl->setVisible(false);
    renderDefaultBlack();
    fadeOpacity = 1;
    currentText = introReader.nextText();
    fadeTimer->start(20);
}

void IntroScene::fadeText(){
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


void IntroScene::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
            if (isLogoDisplayed)
                displayNextContext();
            }
}
