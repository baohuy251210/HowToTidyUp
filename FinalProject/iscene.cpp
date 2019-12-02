#include "iscene.h"
#include <QFont>
#include <QDebug>
#include <QFontDatabase>
#include <QLabel>
IScene::IScene(QWidget *parent) : QWidget(parent)
{
    fontFamily.removeAllApplicationFonts();
    fontFamily.addApplicationFont(":/introdata/SF_Cartoonist_Hand");
    fontFamily.addApplicationFont(":/introdata/SF_Cartoonist_Hand_Bold");
    fontFamily.addApplicationFont(":/introdata/SF_Cartoonist_Hand_Bold_Italic");
    fontFamily.addApplicationFont(":/introdata/SF_Cartoonist_Hand_Italic");
    fontFamily.addApplicationFont(":/introdata/SF_Cartoonist_Hand_SC");
    fontFamily.addApplicationFont(":/introdata/SF_Cartoonist_Hand_SC_Bold");
    fontFamily.addApplicationFont(":/introdata/SF_Cartoonist_Hand_SC_Bold_Italic");
    fontFamily.addApplicationFont(":/introdata/SF_Cartoonist_Hand_SC_Italic");
    fontFamily.addApplicationFont(":/art/fonts/Fiendish");
    fontFamily.addApplicationFont(":/art/fonts/Hollows Free");
    fontFamily.addApplicationFont(":/art/fonts/Black Night");
//    qDebug() << fontFamily.bold("SF Cartoonist Hand", "Bold");
//    qDebug() << fontFamily.families();
}

void IScene::drawTextPushButton(QPushButton * pushBtn, int size, QString fontName,QString fontStyle){
    appFont = fontFamily.font(fontName, fontStyle, size);
    appFont.setPointSize(size);
    pushBtn->setFont(appFont);
}

void IScene::drawTextLabel(QLabel * textLbl, int size, QString fontName,QString fontStyle){
//    qDebug() << fontFamily.font("Fiendish", "", 10);
    appFont = fontFamily.font(fontName,fontStyle, size);
    appFont.setPointSize(size);
    textLbl->setFont(appFont);
}

void IScene::mouseReleaseEvent(QMouseEvent *event){
    //emit hideDialogSignal();
}
