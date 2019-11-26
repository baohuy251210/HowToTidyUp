#include "evidenceview.h"

EvidenceView::EvidenceView(QWidget* parent) : QLabel(parent),
    cleanState(DIRTY),
    name(NONE),
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
    this->model->isSelected = !this->model->isSelected;
    if (this->model->isSelected){
        highlightEvidence();
    } else {
        unhighlightEvidence();
    }

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
