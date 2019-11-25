#include "evidence.h"

#include <QVector>
#include <QString>
#include "ToolsEnum.cpp"
#include <QDebug>

Evidence::Evidence(QWidget* parent)
    : QLabel(parent),
      cleanState(DIRTY)
{
    usedTools.clear();
}

Evidence::~Evidence(){

}

void Evidence::setStartValues(EvidenceEnum name, QVector<Tools> correctTools, QString description){
    this->name = name;
    this->correctTools = correctTools;
    this->description = description;
}

void Evidence::addUsedTool(Tools usedTool){
    usedTools.append(usedTool);
    if(usedTools.size() > 3){
        usedTools.removeFirst();
    }
}

void Evidence::setPixmaps(QPixmap dirty,
                          QPixmap dirtySelected,
                          QPixmap semiclean,
                          QPixmap semicleanSelected,
                          QPixmap clean,
                          QPixmap cleanSelected){
    this->dirty = dirty;
    this->dirtySelected = dirtySelected;
    this->semiclean = semiclean;
    this->semicleanSelected = semicleanSelected;
    this->clean = clean;
    this->cleanSelected = cleanSelected;

    this->setPixmap(dirty);
}

void Evidence::enterEvent ( QEvent * event )
{
    switch(cleanState){
    case CLEAN:
        this->setPixmap(cleanSelected);
        break;
    case SEMICLEAN:
        this->setPixmap(semicleanSelected);
        break;
    case DIRTY:
        this->setPixmap(dirtySelected);
        break;
    }
}

void Evidence::leaveEvent ( QEvent * event )
{
    switch(cleanState){
    case CLEAN:
        this->setPixmap(clean);
        break;
    case SEMICLEAN:
        this->setPixmap(semiclean);
        break;
    case DIRTY:
        this->setPixmap(dirty);
        break;
    }
}

void Evidence::mouseReleaseEvent ( QMouseEvent * event )
{
    emit clickedSignal(name);
}
