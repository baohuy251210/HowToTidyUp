#ifndef ENDSCENE01_H
#define ENDSCENE01_H

#include <QWidget>
#include <iscene.h>
#include "model.h"

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

private:
    void updateScore();
    Ui::EndScene01 *ui;
    Model* model;
};

#endif // ENDSCENE01_H
