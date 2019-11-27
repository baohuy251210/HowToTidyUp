#include "cleaningtoolview.h"
#include "ToolsEnum.cpp"
#include <qdebug.h>

CleaningToolView::CleaningToolView(QWidget *parent) : QLabel(parent)
{

}

void CleaningToolView::setModel(CleaningTool *tool){
    model = tool;
}

void CleaningToolView::enterEvent(QEvent* event){
    qDebug() << "enter event" << endl;
    this->setPixmap(model->icon_selected);
    emit displayDescription(name);
}

void CleaningToolView::leaveEvent(QEvent* event){
    qDebug() << "leave event" << endl;
    if (!this->model->isSelected){
        this->setPixmap(model->icon);
    }
    emit hideDescription(name);
}

void CleaningToolView::mouseReleaseEvent(QMouseEvent* event){
    qDebug() << "click event" << endl;
    this->model->isSelected = !this->model->isSelected;
    if (this->model->isSelected){
        highlightTool();
    } else {
        this->setPixmap(model->icon);
    }

    emit toolClickedSignal(name);
}

void CleaningToolView::setType(Tools type){
    this->name = type;
}

void CleaningToolView::highlightTool(){
    this->setPixmap(model->icon_selected);
}

void CleaningToolView::unhighlightTool(){
    this->setPixmap(model->icon);
}
