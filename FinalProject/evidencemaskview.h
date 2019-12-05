#ifndef EVIDENCEMASKVIEW_H
#define EVIDENCEMASKVIEW_H
#include <QLabel>
#include <CleanStateEnum.cpp>
#include <EvidenceEnum.cpp>
#include <evidence.h>


class EvidenceMaskView : public QLabel
{
    Q_OBJECT
public:
    EvidenceMaskView(QWidget* parent);
    void setEvidenceEnum(EvidenceEnum);
private:
    EvidenceEnum evidenceName;
    void enterEvent(QEvent * event) override;
    void leaveEvent(QEvent * event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
signals:
    void enterMaskSignal();
    void leaveMaskSignal();
    void clickedMaskSignal(EvidenceEnum);
public slots:

};

#endif // EVIDENCEMASKVIEW_H
