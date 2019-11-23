#ifndef KITCHENSCENE_H
#define KITCHENSCENE_H

#include <QWidget>
#include <iscene.h>
#include <toolbarwidget.h>
#include "ToolsEnum.cpp"
QT_BEGIN_NAMESPACE
namespace Ui {
class KitchenScene;
}
QT_END_NAMESPACE

class KitchenScene : public IScene
{
    Q_OBJECT
public:
    explicit KitchenScene(QWidget *parent = nullptr);
    ~KitchenScene();
signals:
    void signalUseToolAndEvidence(Tools, QString);

public slots:
    void toolSelectedSlot(Tools);
    void evidenceActionSlot(QString, QString);
private:
    Ui::KitchenScene *ui;
    Tools selectedCleaningTool;
    QString selectedEvidence;
    ToolbarWidget* cleaningTools;

    void InitializeWidgets();
    void setupConnections();
    void evidencePressed(QString evidenceName);
    void evidenceHovered(QString evidenceName);
};

#endif // KITCHENSCENE_H
