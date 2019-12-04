#ifndef EVIDENCEVIEW_H
#define EVIDENCEVIEW_H

#include <QLabel>
#include <CleanStateEnum.cpp>
#include <EvidenceEnum.cpp>
#include <evidence.h>

class EvidenceView : public QLabel
{
    Q_OBJECT
public:
    EvidenceView(QWidget* parent);

    void setModel(Evidence*);
    void setType(EvidenceEnum type);
    void highlightEvidence();
    void unhighlightEvidence();
public slots:
    void setState(EvidenceEnum evidence, CleanState state);
    void setSelected(EvidenceEnum evidence);
    void clearSelection();
private:
    Evidence* model;

    EvidenceEnum name;

    CleanState cleanState;
    bool isSelected;


    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void bloodDrip();

signals:
    void clickedSignal(EvidenceEnum name);
};



#endif // EVIDENCEVIEW_H
