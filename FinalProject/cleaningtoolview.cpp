#include "cleaningtoolview.h"

CleaningToolView::CleaningToolView(QWidget *parent) : QLabel(parent)
{

}

void CleaningToolView::setModel(CleaningTool *tool){
    model = tool;
}

void CleaningToolView::enterEvent(QEvent* event){
    this->setPixmap(model->icon_selected);
}

void CleaningToolView::leaveEvent(QEvent* event){
    this->setPixmap(model->icon);
}

void CleaningToolView::mouseReleaseEvent(QMouseEvent* event){

}
