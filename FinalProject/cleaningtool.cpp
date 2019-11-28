#include "cleaningtool.h"

CleaningTool::CleaningTool(QString description)
    : description(description), isSelected(false)
{

}

void CleaningTool::setSelected(bool isSelected){
   this->isSelected = isSelected;
}

QPixmap CleaningTool::getIcon(){
    return icon;
}

void CleaningTool::setPixmaps(QPixmap icon, QPixmap icon_selected, QPixmap cursor){
    this->icon = icon;
    this->icon_selected = icon_selected;
    this->cursor = cursor;
}

QPixmap CleaningTool::getIconHighlighted(){
    return icon_selected;
}

QPixmap CleaningTool::getCursor(){
    return cursor;
}

Tools CleaningTool::getType(){
    return type;
}

void CleaningTool::setType(Tools type){
    this->type = type;
}
