#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include <QWidget>
#include <iscene.h>

namespace Ui {
class MainMenuScene;
}

class MainMenuScene : public IScene
{
    Q_OBJECT

public:
    explicit MainMenuScene(QWidget *parent = nullptr);
    ~MainMenuScene();

private:
    Ui::MainMenuScene *ui;
};

#endif // MAINMENUSCENE_H
