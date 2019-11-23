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
    emit interactionSignal(name, "enter");
}

void EvidenceLabel::leaveEvent ( QEvent * event )
{
    qDebug() << "Left";
    emit interactionSignal(name, "leave");
}

//possibly not needed for our implementation
void EvidenceLabel::mouseMoveEvent ( QMouseEvent * event )
{
    qDebug() << "Moved";
    emit interactionSignal(name, "move");
}

void EvidenceLabel::mousePressEvent ( QMouseEvent * event )
{
    qDebug() << "Pressed";
    emit interactionSignal(name, "press");
}

void EvidenceLabel::mouseReleaseEvent ( QMouseEvent * event )
{
    qDebug() << "Released";
    emit interactionSignal(name, "release");
}
