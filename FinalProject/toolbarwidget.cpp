#include "toolbarwidget.h"
#include "ui_toolbarwidget.h"

ToolbarWidget::ToolbarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolbarWidget)
{
    ui->setupUi(this);
}

ToolbarWidget::~ToolbarWidget()
{
    delete ui;

}

void ToolbarWidget::on_gloveButton_clicked()
{
    emit toolSelectedSignal("glove");
}

void ToolbarWidget::on_ragButton_clicked()
{
    emit toolSelectedSignal("rag");
}
