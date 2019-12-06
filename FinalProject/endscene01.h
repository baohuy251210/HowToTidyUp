#ifndef ENDSCENE01_H
#define ENDSCENE01_H

#include <QWidget>
#include <iscene.h>
#include "model.h"
#include <QPainter>

namespace Ui {
class EndScene01;
}

class EndScene01 : public IScene
{
    Q_OBJECT

public:
    explicit EndScene01(QWidget *parent, Model* model);
    ~EndScene01();

private slots:
    void on_continueButton_clicked();
    void advanceCreditsPosition();
    void darkenBackdrop();

private:
    void updateScore();
    Ui::EndScene01 *ui;
    Model* model;
    int creditsFPS;
    int pixelsMovedPerFrame;
    int creditsStartY;
    int creditsEndY;
    int creditsSpeedUpFactor;
    int backdropDarknessPerFrame;
    int backdropOpacity;
    bool creditsStarted;
    void initializeCredits();
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // ENDSCENE01_H
