#ifndef INTROSCENE_H
#define INTROSCENE_H

#include <QWidget>
#include <iscene.h>
#include <QTimer>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include "introreader.h"
namespace Ui {
class IntroScene;
}

class IntroScene : public IScene, public sf::RenderWindow
{
    Q_OBJECT

public:
    explicit IntroScene(QWidget *parent = nullptr);
    ~IntroScene();

private slots:

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::IntroScene *ui;
    sf::RenderTexture texture;
    sf::Texture sprite_texture;
    sf::Sprite sprite;
    IntroReader introReader;
    QTimer *timer;
    QTimer *delayTimer;
    void renderDefaultBlack();
    void displayNextContext();
    void updateImage();
    void fadeText();
    int fadeOpacity;
    QString currentText;
    sf::Font mainFont;
    sf::Music themeMusic;
};

#endif // INTROSCENE_H
