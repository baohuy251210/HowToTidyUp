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

void CleaningTool::setPixmaps(QPixmap icon, QPixmap icon_selected){
    this->icon = icon;
    this->icon_selected = icon_selected;
}

Tools CleaningTool::getType(){
    return type;
}

void CleaningTool::setType(Tools type){
    this->type = type;
}
