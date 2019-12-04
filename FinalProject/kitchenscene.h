#ifndef KITCHENSCENE_H
#define KITCHENSCENE_H

#include <QWidget>
#include <iscene.h>
#include <toolbarwidget.h>
#include "ToolsEnum.cpp"
#include <EvidenceEnum.cpp>
#include <evidence.h>
#include <model.h>
#include <cleaningtoolview.h>
#include <evidenceview.h>

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
signals:
    void signalUseToolAndEvidence(EvidenceEnum);
public slots:
    void deselectEvidenceSlot(EvidenceEnum);
    void setSelectedEvidenceSlot(EvidenceEnum);
    void unselectTool();

private slots:
    void on_exitButton_clicked();


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
