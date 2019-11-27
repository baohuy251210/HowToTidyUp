#ifndef TOOLBARWIDGET_H
#define TOOLBARWIDGET_H

#include <QWidget>
#include "ToolsEnum.cpp"
#include "cleaningtoolview.h"
#include "model.h"

namespace Ui {
class ToolbarWidget;
}

class ToolbarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ToolbarWidget(QWidget *parent = nullptr);
    ~ToolbarWidget();

    void setModel(Model*);

    CleaningToolView* glove;
    CleaningToolView* water;
    CleaningToolView* bleach;
    CleaningToolView* nailpolish_remover;
    CleaningToolView* lye;
    CleaningToolView* borax;
    CleaningToolView* oxiclean;
    CleaningToolView* rag;
    Ui::ToolbarWidget *ui;

signals:

private slots:


private:
    Model* model;
};

#endif // TOOLBARWIDGET_H
