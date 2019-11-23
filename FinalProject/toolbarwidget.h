#ifndef TOOLBARWIDGET_H
#define TOOLBARWIDGET_H

#include <QWidget>

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
    void toolSelectedSignal(QString);

private slots:
    void on_gloveButton_clicked();

    void on_ragButton_clicked();

private:
    Ui::ToolbarWidget *ui;
};

#endif // TOOLBARWIDGET_H
