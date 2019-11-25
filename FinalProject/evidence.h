#ifndef EVIDENCE_H
#define EVIDENCE_H

#include <QVector>
#include <QString>
#include "ToolsEnum.cpp"
#include <EvidenceEnum.cpp>
#include <CleanStateEnum.cpp>
#include <QPixmap>
#include <QLabel>

class Evidence : public QLabel
{
    Q_OBJECT

public:
    Evidence(QWidget* parent);
    ~Evidence() override;

    void setStartValues(EvidenceEnum name, QVector<Tools> correctTools, QString description);

    void setPixmaps(QPixmap dirty,
                    QPixmap dirtySelected,
                    QPixmap semiclean,
                    QPixmap semicleanSelected,
                    QPixmap clean,
                    QPixmap cleanSelected);
    void addUsedTool(Tools usedTool);
signals:
    void clickedSignal(EvidenceEnum name);

private:
     void nothing();
    EvidenceEnum name;
    QVector<Tools> correctTools;
    QList<Tools> usedTools;
    QString description;
    QString evidenceName;

    QPixmap dirty;
    QPixmap dirtySelected;
    QPixmap semiclean;
    QPixmap semicleanSelected;
    QPixmap clean;
    QPixmap cleanSelected;

    CleanState cleanState;

    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
};

#endif // EVIDENCE_H
