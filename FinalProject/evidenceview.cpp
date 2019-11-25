#include "evidenceview.h"

EvidenceView::EvidenceView(QWidget* parent) : QLabel(parent),
    cleanState(DIRTY),
    name(NONE),
    isSelected(false)
{

}

void EvidenceView::setType(EvidenceEnum type){
    name = type;
}

void EvidenceView::setPixmaps(QPixmap dirty,
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

void EvidenceView::enterEvent ( QEvent * event )
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

void EvidenceView::leaveEvent ( QEvent * event )
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

void EvidenceView::mouseReleaseEvent ( QMouseEvent * event )
{
    emit clickedSignal(name);
}

void EvidenceView::setState(EvidenceEnum evidence, CleanState state){
    if(evidence == name){
        cleanState = state;
    }
}

void EvidenceView::setSelected(EvidenceEnum evidence){
    if(evidence == name){
        this->isSelected = true;
    }
}

void EvidenceView::clearSelection(){
    this->isSelected = false;
}
