#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include <QWidget>
#include <iscene.h>
#include <QTimer>
#include "Box2D/Box2D.h"


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

public: signals:
    void newPosition(b2Vec2 vector, b2Vec2 vector2, b2Vec2 vector3);

private slots:
    void on_newGameButton_clicked();
    void on_continueButton_clicked();
    void updateWorld();
    void changeGeometry(b2Vec2 vector, b2Vec2 vector2, b2Vec2 vector3);
    void showFootprintSlot(QLabel* footprint);




protected:
    bool eventFilter(QObject* obj,QEvent* e);

private:
    Ui::MainMenuScene *ui;

    void fadeWhiteFlash();
    int fadeOpacity;
    QTimer * fadeTimer;
};

#endif // MAINMENUSCENE_H
