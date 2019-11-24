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


public: signals:
    void newPosition(b2Vec2 vector);

private slots:
    void on_newGameButton_clicked();
    void on_continueButton_clicked();
    void updateWorld();
    void changeGeometry(b2Vec2 vector);


protected:
    bool eventFilter(QObject* obj,QEvent* e);

private:
    Ui::MainMenuScene *ui;

    void fadeWhiteFlash();
    int fadeOpacity;
    QTimer * fadeTimer;
};

#endif // MAINMENUSCENE_H
