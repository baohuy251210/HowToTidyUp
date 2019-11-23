#ifndef TOOLBARWIDGET_H
#define TOOLBARWIDGET_H

#include <QWidget>
#include "ToolsEnum.cpp"
namespace Ui {
class ToolbarWidget;
}

class ToolbarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ToolbarWidget(QWidget *parent = nullptr);
    ~ToolbarWidget();



signals:
    void toolSelectedSignal(Tools);

private slots:
    void on_gloveButton_clicked();

    void on_ragButton_clicked();

private:
    Ui::ToolbarWidget *ui;
};

#endif // TOOLBARWIDGET_H
