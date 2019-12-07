#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iscene.h>
#include "model.h"
#include "ToolsEnum.cpp"
#include "introscene.h"
#include "endscene01.h"
#include "beginscene.h"
#include "kitchenscene.h"
#include "SceneEnum.cpp"
#include "mainmenuscene.h"
#include <QResource>
#include <SFML/Audio.hpp>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void ChangeScene(Scene sceneEnum);
    void evidenceInteractionSlot();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    IScene* currentScene;
    IntroScene * introScene;
    BeginScene * beginScene;
    KitchenScene * kitchenScene;
    MainMenuScene * mainmenuScene;
    EndScene01 * endScene;

    Model* model;
    void setupMusic();
    void startThemeMusic();
    void startInGameMusic();
    void musicPlayNext();
    QTimer * musicPlaylistTimer;
    QVector<QResource*> musicFiles;
    int currentMusicIndex;
    sf::Music mainThemeMusic;
    void initializeModel();
    void initializeScenes();
    void setupConnections();
    sf::Music overlayMusic;
};
#endif // MAINWINDOW_H
