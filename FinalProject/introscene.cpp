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
IntroScene::IntroScene(QWidget *parent) :
    IScene(parent),
    ui(new Ui::IntroScene)
{
    ui->setupUi(this);
    /*Read resources*/
    QFile file(":/introdata/intro");
    file.open(QIODevice::ReadOnly);
    QResource fontfile(":/introdata/SF_Cartoonist_Hand");
    QByteArray content = file.readAll();
    introReader.readFromFile(QJsonDocument().fromJson(content));
    /*Timers*/
    timer = new QTimer(this);
    delayTimer = new QTimer(this);
    connect(delayTimer, &QTimer::timeout, this, &IntroScene::displayNextContext);
    connect(timer, &QTimer::timeout, this, &IntroScene::fadeText);
    delayTimer->start(1);
    qDebug() << "constructor intro";
    /*inits*/
    ui->textLbl->setAlignment(Qt::AlignCenter);
}

IntroScene::~IntroScene()
{
    delete ui;
}

void IntroScene::renderDefaultBlack(){
    ui->sceneLbl->setStyleSheet("background-color: rgb(0, 0, 0);");
}

void IntroScene::displayNextContext(){
    if (introReader.reachEndOfText()){
        delayTimer->stop();
        timer->stop();
        qDebug() << "intro done";
        emit changeScene(KITCHEN);
        return;
    }
    else delayTimer->setInterval(5000);
    renderDefaultBlack();
    fadeOpacity = 1;
    currentText = introReader.nextText();
    timer->start(20);
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
        timer->stop();
    }
}


void IntroScene::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
            displayNextContext();
        }
}
