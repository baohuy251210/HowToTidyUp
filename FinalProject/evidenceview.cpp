#include "evidenceview.h"
#include "Box2D/Box2D.h"
#include <QDebug>
EvidenceView::EvidenceView(QWidget* parent) : QLabel(parent),
    name(EvidenceEnum::NONE),
    isSelected(false)
{

}

void EvidenceView::setModel(Evidence* evidence){
    model = evidence;
    connect(evidence, &Evidence::cleanStateChangedSignal, this, &EvidenceView::refreshPixmap);
}

void EvidenceView::setType(EvidenceEnum type){
    name = type;
}

void EvidenceView::enterEvent ( QEvent * event )
{
    //remove for only bloodtile/footprint display
    if (name == BLOOD_TILE || name == BLOOD_FOOTPRINT) {
        return;
    }
    highlightEvidence();
}

void EvidenceView::enterEventFromMask(){
    highlightEvidence();
}

void EvidenceView::refreshPixmap(){
    highlightEvidence();
}

void EvidenceView::leaveEvent ( QEvent * event )
{
    //remove for only bloodtile/footprint display
    if (name == BLOOD_TILE || name == BLOOD_FOOTPRINT) {
        return;
    }
    if (!this->model->isSelected){
        unhighlightEvidence();
    }
}
void EvidenceView::leaveEventFromMask(){
    if (!this->model->isSelected){
//        qDebug() << "leaveEventFromMask::"<<this->model->getType();
        unhighlightEvidence();
    }
}

void EvidenceView::mouseReleaseEvent ( QMouseEvent * event )
{
    //override bloodtile/footprint display
    if (name == BLOOD_TILE || name == BLOOD_FOOTPRINT) {
        return;
    }
    emit clickedSignal(name);
}

void EvidenceView::highlightEvidence(){
    switch(model->getCleanState()){
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
    switch(model->getCleanState()){
    case CLEAN:
        this->setPixmap(model->clean);
        break;
    case SEMICLEAN:
        this->setPixmap(model->semiclean);
        break;
    case DIRTY:
        this->setPixmap(model->dirty);
//        qDebug() << name << " " << "dirty leave";
        break;
    }
}

void EvidenceView::setState(EvidenceEnum evidence, CleanState state){
    if(evidence == name){
        model->setCleanState(state);
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
