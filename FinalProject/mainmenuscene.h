#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include <QWidget>
#include <iscene.h>
#include <QTimer>
#include "Box2D/Box2D.h"
#include "SFML/Audio.hpp"
#include <QHBoxLayout>
namespace Ui {
class MainMenuScene;
}

class MainMenuScene : public IScene
{
    Q_OBJECT

public:
    explicit MainMenuScene(QWidget *parent = nullptr);
    ~MainMenuScene();
    b2World world;
    b2Body* body;
    b2Body* body2;
    b2Body* body3;
    QVector<b2Body*> leafBodies;
    QVector<QLabel*> leafLabels;
    QHBoxLayout * hlayout;
public: signals:
    void newPosition(b2Vec2 vector, b2Vec2 vector2, b2Vec2 vector3, QVector<b2Vec2>);

private slots:
    void on_newGameButton_clicked();
    void on_continueButton_clicked();
    void updateWorld();
    void changeGeometry(b2Vec2 vector, b2Vec2 vector2, b2Vec2 vector3, QVector<b2Vec2>);
    void showFootprintSlot(QLabel* footprint);



protected:
    bool eventFilter(QObject* obj,QEvent* e);

private:
    Ui::MainMenuScene *ui;
    QTimer * replayLeafTimer;
    int numLeaves;
    void fadeWhiteFlash();
    void initializeBox2D();
    int fadeOpacity;
    QTimer * fadeTimer;
    sf::Music backgroundMusic;
};

#endif // MAINMENUSCENE_H
