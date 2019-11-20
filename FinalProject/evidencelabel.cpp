#include "evidencelabel.h"
#include <QDebug>

EvidenceLabel::EvidenceLabel(QWidget * parent) : QLabel(parent)
{
}

EvidenceLabel::~EvidenceLabel()
{
}

void EvidenceLabel::enterEvent ( QEvent * event )
{
    qDebug() << "Entered";
}

void EvidenceLabel::leaveEvent ( QEvent * event )
{
    qDebug() << "Left";
}

void EvidenceLabel::mouseMoveEvent ( QMouseEvent * event )
{
    qDebug() << "Moved";
}

void EvidenceLabel::mousePressEvent ( QMouseEvent * event )
{
    qDebug() << "Pressed";
}

void EvidenceLabel::mouseReleaseEvent ( QMouseEvent * event )
{
    qDebug() << "Released";
}
