#include "intro.h"
#include "ui_intro.h"
#include "introreader.h"
#include <QTimer>
#include <QImage>
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <QResource>
#include <SFML/Audio.hpp>
#include <QMediaPlayer>
Intro::Intro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Intro)
{
    ui->setupUi(this);
    texture.create(800,600);
   // sprite.setColor(sf::Color(0, 0,0));
    timer = new QTimer(this);
    QFile file(":/text/intro.json");
    file.open(QIODevice::ReadOnly);
    QByteArray content = file.readAll();
    qDebug() << 0;
    delayTimer = new QTimer(this);
    introReader.readFromFile(QJsonDocument().fromJson(content));
    QResource fontfile(":/fonts/SF_Cartoonist_Hand.ttf");
    mainFont.loadFromMemory(fontfile.data(), fontfile.size());
    QResource musicfile(":/audio/theme.ogg");
    themeMusic.openFromMemory(musicfile.data(), musicfile.size());
    themeMusic.setVolume(100);
    themeMusic.play();
    renderTexture();
    startThemeMusic();
    connect(delayTimer, &QTimer::timeout, this, &Intro::displayNext);
    connect(timer, &QTimer::timeout, this, &Intro::fadeText);
    delayTimer->start(1000);
}

void Intro::renderTexture(){
    texture.clear(sf::Color::Black);
    //texture.draw(sprite);
    texture.display();
    updateImage();
}
void Intro::startThemeMusic(){
}

void Intro::displayNext(){
    if (introReader.reachEndOfText){
        delayTimer->stop();
        timer->stop();
        return;
    }
    else delayTimer->setInterval(5000);
    renderTexture();
    fadeOpacity = 10;
    currentText = introReader.nextText();
    timer->start(10);
}

void Intro::fadeText(){
    texture.clear(sf::Color::Black);
    sf::Text displayText;
    displayText.setFont(mainFont);
    displayText.setString(currentText.toStdString());
    displayText.setCharacterSize(50);
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

void Intro::updateImage(){
    sf::Texture rt = texture.getTexture();
    sf::Image irt = rt.copyToImage();
    const uint8_t *pp = irt.getPixelsPtr();
    QImage qi(pp, 800, 600, QImage::Format_ARGB32);
    qi = qi.rgbSwapped();
    ui->label->setPixmap(QPixmap::fromImage(qi));
}

Intro::~Intro()
{
    delete ui;
}
