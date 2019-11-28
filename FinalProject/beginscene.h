#ifndef BEGINSCENE_H
#define BEGINSCENE_H

#include <QWidget>
#include <iscene.h>
#include <QTimer>
#include "introreader.h"
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

#endif // BEGINSCENE_H
