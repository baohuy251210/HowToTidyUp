#ifndef ITEMDIALOG_H
#define ITEMDIALOG_H

#include <QWidget>
#include <ToolsEnum.cpp>
#include <evidence.h>
#include <iscene.h>
namespace Ui {
class itemDialog;
}

class itemDialog : public IScene
{
    Q_OBJECT
public slots:
    void setEvidence(Evidence* evidence);
    void clearEvidenceSlot();
    void hideDialogSlot();
    void toggleHintVisibleSlot();

public:
    explicit itemDialog(QWidget *parent = nullptr);
    ~itemDialog();
    void setDescription(QString description);
    void setUsedTools(QList<Tools> tools);


private:
    Ui::itemDialog *ui;
    void setupTextFonts();
};

#endif // ITEMDIALOG_H
