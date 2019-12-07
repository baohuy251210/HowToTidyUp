#ifndef KITCHENSCENE_H
#define KITCHENSCENE_H

#include "iscene.h"
#include "toolbarwidget.h"
#include "evidenceview.h"
#include "exitdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class KitchenScene;
}
QT_END_NAMESPACE

class KitchenScene : public IScene
{
    Q_OBJECT
public:
    explicit KitchenScene(QWidget *parent, Model* model);
    ~KitchenScene();
    void loadGameKitchen();

signals:
    void signalUseToolAndEvidence(EvidenceEnum);
    void startOver();
public slots:
    void deselectEvidenceSlot(EvidenceEnum);
    void setSelectedEvidenceSlot(EvidenceEnum);
    void unselectTool();



private slots:
    void exitSceneSlot();
    void on_resetButton_clicked();
    void on_backButton_clicked();

private:
    Ui::KitchenScene *ui;
    QHash<EvidenceEnum, EvidenceView*> evidenceLabels;
    ToolbarWidget* toolbarWidget;
    EvidenceView* knifeLabel;
    EvidenceView* bloodFloorLabel;
    EvidenceView* oilyHandLabel;
    EvidenceView* bloodFootprintsLabel;
    EvidenceView* brokenPlateLabel;
    EvidenceView* bloodWallLabel;
    EvidenceView* gunpowderWallLabel;
    ExitDialog* exitDialog;
    Model* model;
    void InitializeWidgets();
    void setupConnections();
    void evidenceHovered(EvidenceEnum evidenceName);
    void setupPixmaps();
    void setupEvidence();
    void initializeTools();
    void initializeEvidence();
};

#endif // KITCHENSCENE_H
