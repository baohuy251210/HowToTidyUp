#ifndef ITEMDIALOG_H
#define ITEMDIALOG_H

#include <QWidget>

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

private:
    Ui::itemDialog *ui;
};

#endif // ITEMDIALOG_H
