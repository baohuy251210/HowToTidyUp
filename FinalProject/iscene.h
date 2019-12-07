#ifndef ISCENE_H
#define ISCENE_H

#include <QPushButton>
#include "evidence.h"
#include "SceneEnum.cpp"
#include <QFontDatabase>
#include <QLabel>

class IScene : public QWidget
{
    Q_OBJECT
public:
    explicit IScene(QWidget *parent = nullptr);
    QFont appFont;
    /*Draw Text for a PushButton passed in a size, Font name and style*/
    void drawTextPushButton(QPushButton*, int size,
                            QString fontName="SF Cartoonist Hand",QString style = "");
    /*Draw Text for a PushButton passed in a size, Font name and style*/
    void drawTextLabel(QLabel*, int size,
                       QString fontName="SF Cartoonist Hand",QString style= "");

    void addFont(){
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
    }
signals:
    void changeScene(Scene sceneName);
    void addEvidence(Evidence* evidenceName);
    void hideDialogSignal();
public slots:

private:

    /*Font database for the app*/
    QFontDatabase  fontFamily;

};

#endif // ISCENE_H
