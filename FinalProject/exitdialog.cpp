#include "exitdialog.h"
#include "ui_exitdialog.h"
#include "ToolsEnum.cpp"
#include <QResource>
#include <QFont>
#include <QDebug>
#include <QFontDatabase>
#include <QLabel>

#include <evidenceview.h>

ExitDialog::ExitDialog(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::ExitDialog)
{
    ui->setupUi(this);

    QFontDatabase fontFamily;
    fontFamily.removeAllApplicationFonts();
    fontFamily.addApplicationFont(":/art/fonts/Fiendish");
    fontFamily.addApplicationFont(":/introdata/SF_Cartoonist_Hand");
    QFont appFont = fontFamily.font("Fiendish","Italic", 25);
    appFont.setPointSize(25);
    ui->continueLabel->setFont(appFont);

    appFont = fontFamily.font("SF Cartoonist Hand", "Bold", 20);
    ui->exitButton->setFont(appFont);
    ui->cancelButton->setFont(appFont);
    this->setWindowTitle("");

}

ExitDialog::~ExitDialog()
{
    delete ui;
}

void ExitDialog::on_exitButton_clicked()
{
    emit exitSceneSignal();
}

void ExitDialog::on_cancelButton_clicked()
{
    this->close();
}
