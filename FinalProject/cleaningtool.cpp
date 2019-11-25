#include "cleaningtool.h"

CleaningTool::CleaningTool(QString description)
    : description(description), isSelected(false)
{

}

void CleaningTool::setSelected(bool isSelected){
   this->isSelected = isSelected;
}
