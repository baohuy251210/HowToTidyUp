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
#include <SFML/Audio.hpp>
#include <QMouseEvent>
IntroScene::IntroScene(QWidget *parent) :
    IScene(parent),
    ui(new Ui::IntroScene)
{
    ui->setupUi(this);
    texture.create(1280,1024);
    /*Read resources*/
    QFile file(":/introdata/IntroData/intro.json");
    file.open(QIODevice::ReadOnly);
    QResource fontfile(":/introdata/IntroData/SF_Cartoonist_Hand.ttf");
    QByteArray content = file.readAll();
    introReader.readFromFile(QJsonDocument().fromJson(content));
    mainFont.loadFromMemory(fontfile.data(), fontfile.size());
    //renderDefaultBlack();
    /*Timers*/
    timer = new QTimer(this);
    delayTimer = new QTimer(this);
    connect(delayTimer, &QTimer::timeout, this, &IntroScene::displayNextContext);
    connect(timer, &QTimer::timeout, this, &IntroScene::fadeText);
    delayTimer->start(1);

}

IntroScene::~IntroScene()
{
    delete ui;
}

void IntroScene::renderDefaultBlack(){
    texture.clear(sf::Color::Black);
    texture.display();
    updateImage();
}

void IntroScene::displayNextContext(){
    if (introReader.reachEndOfText()){
        delayTimer->stop();
        timer->stop();
//        qDebug()<<"What";
        MainMenuScene * mainMenuScene = new MainMenuScene();
        emit changeScene(mainMenuScene);
        return;
    }
    else delayTimer->setInterval(5000);
    renderDefaultBlack();
    fadeOpacity = 10;
    currentText = introReader.nextText();
    timer->start(10);
}

void IntroScene::fadeText(){
    texture.clear(sf::Color::Black);
    sf::Text displayText;
    displayText.setFont(mainFont);
    displayText.setString(currentText.toStdString());
    displayText.setCharacterSize(80);
    displayText.move(100,200);
    if (fadeOpacity < 255){
        displayText.setFillColor(sf::Color(255, 255, 255, fadeOpacity));
        fadeOpacity+=1;
    }
    else{
        timer->stop();
    }
    texture.draw(displayText);
    texture.display();
    updateImage();
}

void IntroScene::updateImage(){
    sf::Texture rt = texture.getTexture();
    sf::Image irt = rt.copyToImage();
    const uint8_t *pp = irt.getPixelsPtr();
    QImage qi(pp, 1280, 1024, QImage::Format_ARGB32);
    qi = qi.rgbSwapped();
    ui->sceneLbl->setPixmap(QPixmap::fromImage(qi));
}


void IntroScene::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
            displayNextContext();
        }
}
