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
    QTimer *fadeTimer;
    QTimer *creditFadeTimer;
    QTimer *logoTimer;
    QTimer *textStartTimer;
    QTimer *flashContinueTimer;
    void flashContinueLabel();
    void renderDefaultBlack();
    void displayNextContext();
    void updateImage();
    void displayLogo();
    void zoomLogo();
    void displayCredit();
    void fadeText();
    int fadeOpacity;
    QSize logoSize;
    QString currentText;
    bool isLogoDisplayed;
    QPixmap logo;
    QPixmap logoMask;
};

#endif // INTROSCENE_H
