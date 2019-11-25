#ifndef KITCHENSCENE_H
#define KITCHENSCENE_H

#include <QWidget>
#include <iscene.h>
#include <toolbarwidget.h>
#include "ToolsEnum.cpp"
#include <EvidenceEnum.cpp>
#include <evidence.h>
#include <model.h>

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
    void evidenceClickedSlot(EvidenceEnum);
private:
    Ui::KitchenScene *ui;
    ToolbarWidget* cleaningTools;
    Model* model;

    void InitializeWidgets();
    void setupConnections();
    void evidenceHovered(EvidenceEnum evidenceName);
    void setupPixmaps();
    void setupEvidence();
    void initializeEvidence();
};

#endif // KITCHENSCENE_H
