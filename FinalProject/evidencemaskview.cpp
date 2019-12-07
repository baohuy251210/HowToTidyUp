#include "evidencemaskview.h"
#include <QDebug>
EvidenceMaskView::EvidenceMaskView(QWidget * parent):
    QLabel(parent)
{
}

void EvidenceMaskView::setEvidenceEnum(EvidenceEnum eviEnum){
    evidenceName = eviEnum;
}
void EvidenceMaskView::enterEvent(QEvent *event){
    emit enterMaskSignal();

}

void EvidenceMaskView::leaveEvent(QEvent *event){
    emit leaveMaskSignal();
}

void EvidenceMaskView::mouseReleaseEvent(QMouseEvent *event){
    emit clickedMaskSignal(evidenceName);
}
