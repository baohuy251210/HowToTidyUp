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
//    qDebug() << "maskviewenter::" << evidenceName;
    emit enterMaskSignal();

}

void EvidenceMaskView::leaveEvent(QEvent *event){
//    qDebug() << "maskviewleave::" << evidenceName;
    emit leaveMaskSignal();
}

void EvidenceMaskView::mouseReleaseEvent(QMouseEvent *event){
    emit clickedMaskSignal(evidenceName);
}
