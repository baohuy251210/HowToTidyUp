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
    QVector<b2Body*> leafBodies;
    QVector<QLabel*> leafLabels;
    QVector<QString> soundFiles;

public: signals:
    void newPosition(QVector<b2Vec2>);
    void loadGameSignal();
private slots:
    void on_newGameButton_clicked();
    void on_continueButton_clicked();
    void updateWorld();
    void changeGeometry(QVector<b2Vec2>);
    void showFootprintSlot(QLabel* footprint);
    void playNextSnowCrunchSound();



protected:
    bool eventFilter(QObject* obj,QEvent* e);

private:
    Ui::MainMenuScene *ui;
    QTimer * replayLeafTimer;
    QTimer * updateLeafTimer;
    bool isLastLeavesRow;
    int numLeaves;
    void fadeWhiteFlash();
    void initializeBox2D();
    int fadeOpacity;
    QTimer * fadeTimer;
    sf::Music backgroundMusic;
    int soundCount;

};

#endif // MAINMENUSCENE_H
