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

