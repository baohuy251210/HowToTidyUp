#include "iscene.h"
#include <QFont>
#include <QDebug>
#include <QFontDatabase>
#include <QLabel>
IScene::IScene(QWidget *parent) : QWidget(parent)
{
    fontFamily.removeAllApplicationFonts();
    fontFamily.addApplicationFont(":/introdata/IntroData/SF_Cartoonist_Hand.ttf");
    fontFamily.addApplicationFont(":/introdata/IntroData/SF_Cartoonist_Hand_Bold.ttf");
    fontFamily.addApplicationFont(":/introdata/IntroData/SF_Cartoonist_Hand_Bold_Italic.ttf");
    fontFamily.addApplicationFont(":/introdata/IntroData/SF_Cartoonist_Hand_Italic.ttf");
    fontFamily.addApplicationFont(":/introdata/IntroData/SF_Cartoonist_Hand_SC.ttf");
    fontFamily.addApplicationFont(":/introdata/IntroData/SF_Cartoonist_Hand_SC_Bold.ttf");
    fontFamily.addApplicationFont(":/introdata/IntroData/SF_Cartoonist_Hand_SC_Bold_Italic.ttf");
    fontFamily.addApplicationFont(":/introdata/IntroData/SF_Cartoonist_Hand_SC_Italic.ttf");
}

void IScene::drawTextPushButton(QPushButton * pushBtn, int size, QString fontName,QString fontStyle){
    appFont = fontFamily.font(fontName, fontStyle, size);
    appFont.setPointSize(size);
    pushBtn->setFont(appFont);
}

void IScene::drawTextLabel(QLabel * textLbl, int size, QString fontName,QString fontStyle){
    appFont = fontFamily.font(fontName,fontStyle, size);
    appFont.setPointSize(size);
    textLbl->setFont(appFont);
}
