#ifndef CLEANINGTOOLVIEW_H
#define CLEANINGTOOLVIEW_H
#include "ToolsEnum.cpp"
#include <QLabel>
#include <cleaningtool.h>

class CleaningToolView : public QLabel
{
    Q_OBJECT

public:
    explicit CleaningToolView(QWidget *parent = nullptr);
    void setModel(CleaningTool* tool);
    void highlightTool();
    void unhighlightTool();
    void setType(Tools type);
    QCursor curCursor;

    CleaningTool* model;
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
private:
    Tools name;
signals:
    void  toolClickedSignal(Tools);
    void displayDescription(Tools);
    void hideDescription(Tools);
public slots:
};

#endif // CLEANINGTOOLVIEW_H
