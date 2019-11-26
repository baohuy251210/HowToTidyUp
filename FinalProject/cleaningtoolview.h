#ifndef CLEANINGTOOLVIEW_H
#define CLEANINGTOOLVIEW_H

#include <QLabel>
#include <cleaningtool.h>

class CleaningToolView : public QLabel
{
    Q_OBJECT
    CleaningTool* model;
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
public:
    explicit CleaningToolView(QWidget *parent = nullptr);
    void setModel(CleaningTool* tool);
    void highlightTool();
signals:

public slots:
};

#endif // CLEANINGTOOLVIEW_H
