#include "iscene.h"
#include <QFont>
#include <QDebug>
#include <QFontDatabase>
#include <QLabel>

IScene::IScene(QWidget *parent) : QWidget(parent)
{
    fontFamily.removeAllApplicationFonts();
    addFont();
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

void IScene::mouseReleaseEvent(QMouseEvent *event){
    //emit hideDialogSignal();
}
