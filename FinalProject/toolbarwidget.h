#ifndef TOOLBARWIDGET_H
#define TOOLBARWIDGET_H

#include <QWidget>
#include "ToolsEnum.cpp"
#include "cleaningtoolview.h"

namespace Ui {
class ToolbarWidget;
}

class ToolbarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ToolbarWidget(QWidget *parent = nullptr);
    ~ToolbarWidget();

    CleaningToolView* glove;
    CleaningToolView* water;
    CleaningToolView* bleach;
    CleaningToolView* nailpolish_remover;
    CleaningToolView* lye;
    CleaningToolView* borax;
    CleaningToolView* oxiclean;
    Ui::ToolbarWidget *ui;

signals:
    void toolSelectedSignal(Tools);

private slots:
    void on_gloveButton_clicked();

    void on_ragButton_clicked();

private:

};

#endif // TOOLBARWIDGET_H
