#include "mainmenuscene.h"
#include "ui_mainmenuscene.h"
#include <kitchenscene.h>
#include <QDebug>
MainMenuScene::MainMenuScene(QWidget *parent) :
    IScene(parent),
    ui(new Ui::MainMenuScene)
{
    ui->setupUi(this);
    ui->maskLabel->setFixedSize(QSize(1024,768));

    drawTextLabel(ui->nameLabel, 50,"SF Cartoonist Hand", "Bold Italic");
    drawTextPushButton(ui->newGameButton, 40,"SF Cartoonist Hand");
    drawTextPushButton(ui->continueButton, 40,"SF Cartoonist Hand");


    fadeOpacity = 100; //percentage
    ui->maskLabel->setStyleSheet("background-color: rgb(0,0,0)");
    fadeTimer = new QTimer(this);
    connect(fadeTimer, &QTimer::timeout, this, &MainMenuScene::fadeWhiteFlash);
    fadeTimer->start(30);

    //gained from the same SO entry.
    ui->newGameButton->installEventFilter(this);
    ui->aMurder->setVisible(false);
    QFontDatabase::addApplicationFont(":/fonts/Fiendish.ttf");
    QFont creepy = QFont("Fiendish", 36, 1);
    ui->aMurder->setFont(creepy);

}

MainMenuScene::~MainMenuScene()
{
    delete ui;
}

void MainMenuScene::fadeWhiteFlash(){
    QString maskStyleSheet ="background-color: rgba(255, 255, 255, "+QString::number(fadeOpacity)+"%);";
//    qDebug() <<maskStyleSheet;
    ui->maskLabel->setStyleSheet(maskStyleSheet);
    fadeOpacity-=2;
    if (fadeOpacity <= 0){
        fadeTimer->stop();
        ui->maskLabel->setVisible(false);
    }

}

void MainMenuScene::on_newGameButton_clicked()
{
    KitchenScene* kitchen = new KitchenScene();
    emit changeScene(kitchen);
}

//Method gained from this Stack overflow entry:
//https://stackoverflow.com/questions/9261175/how-to-emit-a-signal-from-a-qpushbutton-when-the-mouse-hovers-over-it
bool MainMenuScene::eventFilter(QObject *obj, QEvent *e){
    QPushButton* target = ui->newGameButton;
    if(obj == (QObject*)target){
        if(e->type() == QEvent::Enter){

            ui->aMurder->setVisible(true);
        }else if(e->type() == QEvent::Leave){
            ui->aMurder->setVisible(false);
        }
    }
    else{

        return QWidget::eventFilter(obj, e);
    }
}

void MainMenuScene::on_continueButton_clicked()
{
    KitchenScene* kitchen = new KitchenScene();
    emit changeScene(kitchen);
}
