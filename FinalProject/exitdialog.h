#ifndef EXITDIALOG_H
#define EXITDIALOG_H

#include <QDialog>

namespace Ui {
class ExitDialog;
}

class ExitDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExitDialog(QWidget *parent = nullptr);
    ~ExitDialog();

signals:
    void exitSceneSignal();

private slots:
    void on_exitButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::ExitDialog *ui;
};

#endif // EXITDIALOG_H
