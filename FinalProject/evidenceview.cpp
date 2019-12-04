#include "evidenceview.h"
#include "Box2D/Box2D.h"

EvidenceView::EvidenceView(QWidget* parent) : QLabel(parent),
    name(EvidenceEnum::NONE),
    cleanState(DIRTY),
    isSelected(false)
{

}

void EvidenceView::setModel(Evidence* evidence){
    model = evidence;
}

void EvidenceView::setType(EvidenceEnum type){
    name = type;
}

void EvidenceView::enterEvent ( QEvent * event )
{

    highlightEvidence();
}

void EvidenceView::leaveEvent ( QEvent * event )
{
    if (!this->model->isSelected){
        unhighlightEvidence();
    }

}

void EvidenceView::mouseReleaseEvent ( QMouseEvent * event )
{
    emit clickedSignal(name);
}

void EvidenceView::highlightEvidence(){
    switch(cleanState){
    case CLEAN:
        this->setPixmap(model->clean_highlighted);
        break;
    case SEMICLEAN:
        this->setPixmap(model->semiclean_highlighted);
        break;
    case DIRTY:
        this->setPixmap(model->dirty_highlighted);
        break;
    }
}

void EvidenceView::unhighlightEvidence(){
    switch(cleanState){
    case CLEAN:
        this->setPixmap(model->clean);
        break;
    case SEMICLEAN:
        this->setPixmap(model->semiclean);
        break;
    case DIRTY:
        this->setPixmap(model->dirty);
        break;
    }
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

void EvidenceView::bloodDrip(){
//intialize a world, QLable vector, and some set amount of drops.
//essentially call the same code that we use to drop the leaves down, minus the position changes
//current issue: getting the location of the item in question so that it only falls from that particular one.
}
