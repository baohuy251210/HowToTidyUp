#ifndef ISCENE_H
#define ISCENE_H

#include <QWidget>
#include <QTimer>
#include <QFont>
#include <QPushButton>
#include <QLabel>
#include <QFontDatabase>
#include "SceneEnum.cpp"
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
                       QString fontName="SF Cartoonist Hand",QString style="");

signals:
    void changeScene(Scene sceneName);
public slots:

private:
    /*Font database for the app*/
    QFontDatabase fontFamily;
};

#endif // ISCENE_H
