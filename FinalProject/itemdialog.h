#ifndef ITEMDIALOG_H
#define ITEMDIALOG_H

#include <QWidget>
#include <ToolsEnum.cpp>

namespace Ui {
class itemDialog;
}

class itemDialog : public QWidget
{
    Q_OBJECT
public slots:
public:
    explicit itemDialog(QWidget *parent = nullptr);
    ~itemDialog();
    void setDescription(QString description);
    void setUsedTools(QList<Tools> tools);

private:
    Ui::itemDialog *ui;
};

#endif // ITEMDIALOG_H
