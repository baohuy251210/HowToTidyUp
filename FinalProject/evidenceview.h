#ifndef EVIDENCEVIEW_H
#define EVIDENCEVIEW_H

#include <QLabel>
#include "evidence.h"

class EvidenceView : public QLabel
{
    Q_OBJECT
public:
    EvidenceView(QWidget* parent);

    void setModel(Evidence*);
    void setType(EvidenceEnum type);
    void unhighlightEvidence();
    void highlightEvidence();
public slots:
    void setState(EvidenceEnum evidence, CleanState state);
    void setSelected(EvidenceEnum evidence);
    void clearSelection();
    void enterEventFromMask();
    void leaveEventFromMask();
    void refreshPixmap();
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;
private:
    Evidence* model;

    EvidenceEnum name;

    bool isSelected;

    void mouseReleaseEvent(QMouseEvent *ev) override;

signals:
    void clickedSignal(EvidenceEnum name);
};



#endif // EVIDENCEVIEW_H
