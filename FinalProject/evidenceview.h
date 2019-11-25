#ifndef EVIDENCEVIEW_H
#define EVIDENCEVIEW_H

#include <QLabel>
#include <CleanStateEnum.cpp>
#include <EvidenceEnum.cpp>

class EvidenceView : public QLabel
{
    Q_OBJECT
public:
    EvidenceView(QWidget* parent);

    void setPixmaps(QPixmap dirty,
                    QPixmap dirtySelected,
                    QPixmap semiclean,
                    QPixmap semicleanSelected,
                    QPixmap clean,
                    QPixmap cleanSelected);

    void setType(EvidenceEnum type);
public slots:
    void setState(EvidenceEnum evidence, CleanState state);
    void setSelected(EvidenceEnum evidence);
    void clearSelection();
private:
    QPixmap dirty;
    QPixmap dirtySelected;
    QPixmap semiclean;
    QPixmap semicleanSelected;
    QPixmap clean;
    QPixmap cleanSelected;

    EvidenceEnum name;

    CleanState cleanState;
    bool isSelected;

    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;

signals:
    void clickedSignal(EvidenceEnum name);
};



#endif // EVIDENCEVIEW_H
