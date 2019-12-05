#include "endscene01.h"
#include "ui_endscene01.h"

EndScene01::EndScene01(QWidget *parent, Model* model) :
    IScene(parent),
    ui(new Ui::EndScene01),
    model(model)

{
    ui->setupUi(this);

    QCursor cursor = Qt::ArrowCursor;
    QApplication::setOverrideCursor(cursor);

    updateScore();
    QList<QLabel *> list = this->findChildren<QLabel *>();
    foreach(QLabel *Lbl, list)
    {
      drawTextLabel(Lbl, Lbl->font().pointSize()+9, "SF Cartoonist Hand", "");
    }
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
}
