#include "cleaningtoolview.h"
#include "ToolsEnum.cpp"
#include <qdebug.h>
#include <qcursor.h>
#include <QMouseEvent>
#include <QApplication>

CleaningToolView::CleaningToolView(QWidget *parent) : QLabel(parent)
{

}

void CleaningToolView::setModel(CleaningTool *tool){
    model = tool;
}

void CleaningToolView::enterEvent(QEvent* event){
    qDebug() << "enter event" << endl;
   // this->setPixmap(model->icon_selected);
}

void CleaningToolView::leaveEvent(QEvent* event){
    qDebug() << "leave event" << endl;
    if (!this->model->isSelected){
      //  this->setPixmap(model->icon);
    }
}

void CleaningToolView::mousePressEvent(QMouseEvent* event){
    qDebug() << "click event" << endl;
    if(event->button() == Qt::LeftButton && this->model->isSelected == false){
        highlightTool();
    }
    else if (event->button() == Qt::LeftButton && this->model->isSelected == true) {
        unhighlightTool();
    }
//    this->model->isSelected = !this->model->isSelected;
//    if (this->model->isSelected){
//        highlightTool();
//    } else {
//        this->setPixmap(model->icon);
//    }

    emit toolClickedSignal(name);
}

void CleaningToolView::setType(Tools type){
    this->name = type;
}

void CleaningToolView::highlightTool(){
    this->setPixmap(model->icon_selected);
    this->model->isSelected = true;

    QCursor cursor(model->icon);
    QApplication::setOverrideCursor(cursor);
}

void CleaningToolView::unhighlightTool(){
    this->setPixmap(model->icon);
    this->model->isSelected = false;
    //QApplication::restoreOverrideCursor();
}
