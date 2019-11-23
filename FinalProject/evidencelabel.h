#ifndef EVIDENCELABEL_H
#define EVIDENCELABEL_H

#include <QLabel>

class EvidenceLabel: public QLabel
{
    Q_OBJECT

public:
    EvidenceLabel(QWidget * parent);
    ~EvidenceLabel();
    QString name;

signals:
    void interactionSignal(QString sender, QString interaction);


protected slots:

    virtual void enterEvent ( QEvent * event );
    virtual void leaveEvent ( QEvent * event );
    virtual void mouseMoveEvent ( QMouseEvent * event );
    virtual void mousePressEvent ( QMouseEvent * event );
    virtual void mouseReleaseEvent ( QMouseEvent * event );
};

#endif // EVIDENCELABEL_H
