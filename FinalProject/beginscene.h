#ifndef BEGINSCENE_H
#define BEGINSCENE_H

#include <QWidget>
#include <iscene.h>
#include <QTimer>
#include <SFML/Audio.hpp>
#include <QResource>
#include <QMouseEvent>
#include <introreader.h>

namespace Ui {
class BeginScene;
}

class BeginScene : public IScene
{
    Q_OBJECT

public:
    explicit BeginScene(QWidget *parent = nullptr);
    ~BeginScene();

private slots:

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::BeginScene *ui;

    IntroReader introReader;
    QTimer *fadeTimer;
    QTimer *creditFadeTimer;
    QTimer *logoTimer;
    QTimer *textStartTimer;
    QTimer *flashContinueTimer;
    void renderDefaultBlack();
    void displayNextContext();
    void flashContinueLabel();
    void updateImage();
    void displayLogo();
    void zoomLogo();
    void displayCredit();
    void playCrimeEffects();
    void playWakeEffects();
    void fadeText();
    int fadeOpacity;
    QSize logoSize;
    QString currentText;
    bool isLogoDisplayed;
    QPixmap logo;
    QPixmap logoMask;
    sf::Music fxStab;
    sf::Music fxDrag;
    sf::Music fxYawn;
};

#endif // BEGINSCENE_H
