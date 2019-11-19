#ifndef INTROSCENE_H
#define INTROSCENE_H

#include <QWidget>
#include <iscene.h>
#include <QTimer>
#include "introreader.h"
namespace Ui {
class IntroScene;
}

class IntroScene : public IScene
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
    IntroReader introReader;
    QTimer *timer;
    QTimer *delayTimer;
    void renderDefaultBlack();
    void displayNextContext();
    void updateImage();
    void fadeText();
    int fadeOpacity;
    QString currentText;
};

#endif // INTROSCENE_H
