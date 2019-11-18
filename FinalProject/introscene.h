#ifndef INTROSCENE_H
#define INTROSCENE_H

#include <QWidget>
#include <iscene.h>

namespace Ui {
class IntroScene;
}

class IntroScene : public IScene
{
    Q_OBJECT

public:
    explicit IntroScene(QWidget *parent = nullptr);
    ~IntroScene();

private:
    Ui::IntroScene *ui;
};

#endif // INTROSCENE_H
