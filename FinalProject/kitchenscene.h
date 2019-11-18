#ifndef KITCHENSCENE_H
#define KITCHENSCENE_H

#include <QWidget>
#include <iscene.h>

namespace Ui {
class KitchenScene;
}

class KitchenScene : public IScene
{
    Q_OBJECT

public:
    explicit KitchenScene(QWidget *parent = nullptr);
    ~KitchenScene();

private:
    Ui::KitchenScene *ui;
};

#endif // KITCHENSCENE_H
