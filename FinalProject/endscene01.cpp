#include "endscene01.h"
#include "ui_endscene01.h"

EndScene01::EndScene01(QWidget *parent, Model* model) :
    IScene(parent),
    ui(new Ui::EndScene01),
    model(model),
    creditsFPS(30),
    pixelsMovedPerFrame(3),
    creditsStartY(1000),
    creditsEndY(-1500),    
    creditsSpeedUpFactor(5),
    backdropDarknessPerFrame(2),        
    backdropOpacity(0),
    creditsStarted(false)

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

    qDebug() << ui->knifeLabel->styleSheet();
}

void EndScene01::initializeCredits(){
    ui->creditsBackdrop->setGeometry(0,0,1024,768);
    ui->creditsBackdrop->raise();
    ui->creditsBackdrop->setStyleSheet("background-color: rgba(0,0,0,0)");
    ui->creditsBackdrop->hide();

    ui->creditsWidget->raise();
    ui->creditsWidget->setGeometry(62,768,900,4000);

    QVBoxLayout* creditsLayout = new QVBoxLayout();
    creditsLayout->setSpacing(1);
    creditsLayout->setGeometry(QRect(62,768,900,4000));
    creditsLayout->setAlignment(Qt::AlignTop);


    QFile file(":/text/credits");
    if(!file.exists() || !file.open(QIODevice::ReadOnly)){
        qDebug() << "Error loading file";
        return;
    }
    QTextStream input(&file);

    while(!input.atEnd()){
        QString line = input.readLine();
        QLabel* creditsLabel = new QLabel();
        creditsLabel->setAlignment(Qt::AlignHCenter);
        creditsLabel->setMinimumHeight(50);
        creditsLabel->setText(line);
        creditsLabel->setStyleSheet("color: rgb(240,240,240)");
        creditsLabel->setFont(QFont("SF Cartoonist Hand",36));
        creditsLayout->addWidget(creditsLabel);
    }

    ui->creditsWidget->setLayout(creditsLayout);

    file.close();

}

void EndScene01::updateScore(){
    double finalScore = model->getFinalScorePercentage();

    // WIN
    if(finalScore >= 99){
        ui->endTitleLabel->setText("Spick and span!");
        ui->endDescriptionLabel->setText("Your party went off without a hitch! Great job! Nobody had a clue.");
        ui->bgLabel->setPixmap(QPixmap(":/art/backgrounds/Endgame1"));
    }
    else if (finalScore > 70){//70%
        ui->endTitleLabel->setText("Cleaned up good!");
        ui->endDescriptionLabel->setText("It was an amazing Thanksgiving Night! But someone noticed blood marks and might report you...");
        ui->bgLabel->setPixmap(QPixmap(":/art/backgrounds/Endgame1"));
    }
    else if (finalScore >20){
        ui->endTitleLabel->setText("You're new to the game");
        ui->endDescriptionLabel->setText("10 minutes into your party, the guests discovered a dreadful murder scene...");
        ui->bgLabel->setPixmap(QPixmap(":/art/backgrounds/Endgame2"));
    }
    else{ // LOSS
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
    QTimer::singleShot(1000 / creditsFPS, this, &EndScene01::advanceCreditsPosition);
    QTimer::singleShot(1000 / creditsFPS, this, &EndScene01::darkenBackdrop);
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
