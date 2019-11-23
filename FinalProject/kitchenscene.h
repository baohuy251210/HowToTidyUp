#ifndef KITCHENSCENE_H
#define KITCHENSCENE_H

#include <QWidget>
#include <iscene.h>
#include <toolbarwidget.h>

namespace Ui {
class KitchenScene;
}

class KitchenScene : public IScene
{
    Q_OBJECT

public:
    explicit KitchenScene(QWidget *parent = nullptr);
    ~KitchenScene();

public slots:
    void toolSelectedSlot(QString);

private:
    Ui::KitchenScene *ui;
    QString selectedCleaningTool;
    QString selectedEvidence;
    ToolbarWidget* cleaningTools;

    void InitializeWidgets();
    void setupConnections();
};

#endif // KITCHENSCENE_H
