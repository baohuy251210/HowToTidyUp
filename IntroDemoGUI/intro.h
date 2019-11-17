#ifndef INTRO_H
#define INTRO_H

#include <QWidget>
#include <QTimer>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <QMediaPlayer>
#include "introreader.h"
namespace Ui {
class Intro;
}

class Intro : public QWidget, public sf::RenderWindow
{
    Q_OBJECT

public:
    explicit Intro(QWidget *parent = nullptr);
    ~Intro();

private:
    Ui::Intro *ui;
    sf::RenderTexture texture;
    sf::Texture sprite_texture;
    sf::Sprite sprite;
    IntroReader introReader;
    QTimer *timer;
    QTimer *delayTimer;
    void renderTexture();
    void displayNext();
    void startThemeMusic();
    void updateImage();
    void fadeText();
    int fadeOpacity;
    QString currentText;
    sf::Font mainFont;
    sf::Music themeMusic;
    QMediaPlayer * backgroundMusic;
};

#endif // INTRO_H
