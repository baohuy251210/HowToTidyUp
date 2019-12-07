#include "cleaningtoolview.h"

CleaningToolView::CleaningToolView(QWidget *parent) : QLabel(parent)
{

}

void CleaningToolView::setModel(CleaningTool *tool){
    model = tool;
}

void CleaningToolView::enterEvent(QEvent* event){
    emit displayDescription(name);
}

void CleaningToolView::leaveEvent(QEvent* event){
    emit hideDescription(name);
}

void CleaningToolView::mousePressEvent(QMouseEvent* event){
    emit toolClickedSignal(name);
}

void CleaningToolView::setType(Tools type){
    this->name = type;
}

void CleaningToolView::highlightTool(){
    this->setPixmap(model->getIconHighlighted());
    this->model->isSelected = true;

    QCursor cursor;
    if(name == GLOVE){
        cursor = QCursor(model->getCursor(), 87,26);
    }else{
        cursor = QCursor(model->getCursor(), 17, 18);
    }

    QApplication::setOverrideCursor(cursor);
}

void CleaningToolView::clearSelectionSlot(){
    unhighlightTool();
}

void CleaningToolView::unhighlightTool(){
    this->setPixmap(model->getIcon());
    this->model->isSelected = false;
}

void CleaningToolView::setSelectedSlot(Tools tool){
    if(this->name == tool){
        highlightTool();
    }
}
