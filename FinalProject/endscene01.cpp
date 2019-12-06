#include "endscene01.h"
#include "ui_endscene01.h"

EndScene01::EndScene01(QWidget *parent, Model* model) :
    IScene(parent),
    ui(new Ui::EndScene01),
    model(model),
    creditsFPS(30),
    pixelsMovedPerFrame(3),
    creditsStartY(1000),
    creditsEndY(-2000),
    creditsStarted(false),
    backdropDarknessPerFrame(2),
    backdropOpacity(0),
    creditsSpeedUpFactor(5)

{
    ui->setupUi(this);

    QList<QLabel *> list = this->findChildren<QLabel *>();
    foreach(QLabel *Lbl, list)
    {
      drawTextLabel(Lbl, Lbl->font().pointSize()+9, "SF Cartoonist Hand", "");
    }

    QCursor cursor = Qt::ArrowCursor;
    QApplication::setOverrideCursor(cursor);

    initializeCredits();

    updateScore();

}

void EndScene01::initializeCredits(){
    ui->creditsBackdrop->setGeometry(0,0,1024,768);
    ui->creditsBackdrop->raise();
    ui->creditsBackdrop->setStyleSheet("background-color: rgba(0,0,0,0)");
    ui->creditsBackdrop->hide();

    ui->creditsWidget->raise();

    QString credits = QString("\n\nCreated By\nThe Senary Ten\n\nHuy Tran\nCam Davie\nEli Hebdon\nJohn Duffy\nDominic Utter\nNathan Gordon");

    QLabel* creditsLabel = new QLabel();
    creditsLabel->setAlignment(Qt::AlignHCenter);
    creditsLabel->setText(credits);
    creditsLabel->setStyleSheet("color: rgb(240,240,240)");
    creditsLabel->setFont(QFont("SF Cartoonist Hand",36));

    ui->creditsLayout->addWidget(creditsLabel);
}

void EndScene01::updateScore(){
    double finalScore = model->getFinalScorePercentage();

    // WIN
    if(finalScore > 80){
        ui->endTitleLabel->setText("Spick and span!");
        ui->endDescriptionLabel->setText("Your party went off without a hitch! Great job! Nobody had a clue.");
        ui->bgLabel->setPixmap(QPixmap(":/art/backgrounds/Endgame1"));
    }else{ // LOSS
        ui->endTitleLabel->setText("Disaster!");
        ui->endDescriptionLabel->setText("Someone noticed your mess! What an embarassment! Maybe next year...");
        ui->bgLabel->setPixmap(QPixmap(":/art/backgrounds/Endgame2"));
    }

    ui->totalPercentLabel->setText(QString::number(finalScore, 'f',1));
    ui->knifePercentLabel->setText(QString::number(model->getEvidenceScorePercentage(KNIFE), 'f',1));
    ui->bloodWallPercentLabel->setText(QString::number(model->getEvidenceScorePercentage(BLOOD_WALL_WOOD), 'f',1));
    ui->bloodFootprintPercentLabel->setText(QString::number(model->getEvidenceScorePercentage(BLOOD_FOOTPRINT), 'f',1));
    ui->bloodFloorPercentLabel->setText(QString::number(model->getEvidenceScorePercentage(BLOOD_TILE), 'f',1));
    ui->oilyHandprintPercentLabel->setText(QString::number(model->getEvidenceScorePercentage(FINGERPRINT_GLASS), 'f',1));
    ui->gunpowderWallPercentLabel->setText(QString::number(model->getEvidenceScorePercentage(GUNPOWDER_WALL), 'f',1));
}

EndScene01::~EndScene01()
{
    delete ui;
}

void EndScene01::on_continueButton_clicked()
{
    ui->endingStatsWidget->hide();
    ui->creditsBackdrop->show();
    creditsStarted = true;
    QTimer::singleShot(1000 / creditsFPS, this, &EndScene01::advanceCreditsPosition );
    //QTimer::singleShot(1000 / creditsFPS, this, &EndScene01::darkenBackdrop);
}

void EndScene01::advanceCreditsPosition(){
    QRect position = ui->creditsWidget->geometry();
    position.setY(position.y() - pixelsMovedPerFrame);
    ui->creditsWidget->setGeometry(position);

    position.setY(position.y() - pixelsMovedPerFrame);

    if(position.y() > creditsEndY){
        QTimer::singleShot(1000 / creditsFPS, this, &EndScene01::advanceCreditsPosition );
    }else{
        changeScene(MAINMENU);
    }
}

void EndScene01::darkenBackdrop(){
    backdropOpacity += backdropDarknessPerFrame;
    if(backdropOpacity > 255){
        backdropOpacity = 255;
    }
    QString script("background-color: rgba(0,0,0," + QString::number(backdropOpacity) + ")");
    ui->creditsBackdrop->setStyleSheet(script);

    if(backdropOpacity != 255){
        QTimer::singleShot(1000 / creditsFPS, this, &EndScene01::darkenBackdrop);
    }
}

void EndScene01::mousePressEvent(QMouseEvent *event){
    if(creditsStarted){
        pixelsMovedPerFrame *= creditsSpeedUpFactor;
    }
}

void EndScene01::mouseReleaseEvent(QMouseEvent *event){
    if(creditsStarted){
        pixelsMovedPerFrame /= creditsSpeedUpFactor;
    }
}
