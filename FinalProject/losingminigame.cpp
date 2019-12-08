#include "losingminigame.h"
#include "ui_losingminigame.h"
#include <QTimer>

LosingMinigame::LosingMinigame(QWidget *parent) :
    IScene(parent),
    ui(new Ui::LosingMinigame), score(0), questionIndex(0)
{
    ui->setupUi(this);
    questions = new QList<QString>();
    infoList = new QList<QString>();
    answers = new QList<QPair<QString, bool>>();
    questionDelay = new QTimer(this);
    charIndex = 1;
    connect(questionDelay, &QTimer::timeout, this, &LosingMinigame::updateQuestion);

    initializeAnswers();
    initializeQuestions();
    initializeInfoList();

    ui->dialogLabel->lower();
    ui->faceLabel->lower();
    ui->bgLabel->lower();
    ui->questionLabel->raise();

    enableButtons(false);

    nextQuestion();
}

LosingMinigame::~LosingMinigame()
{
    delete questions;
    delete infoList;
    delete answers;
    delete questionDelay;
    delete ui;
}

void LosingMinigame::exitSceneSlot(){
    emit changeScene(MAINMENU);
}

void LosingMinigame::enableButtons(bool enabled){
    ui->option1Button->setEnabled(enabled);
    ui->option2Button->setEnabled(enabled);
    ui->option3Button->setEnabled(enabled);
    ui->option4Button->setEnabled(enabled);

}

void LosingMinigame::on_option1Button_clicked()
{
    advanceQuestion(answers->at(questionIndex).second);

}

void LosingMinigame::on_option2Button_clicked()
{
    advanceQuestion(answers->at(questionIndex + 1).second);
}

void LosingMinigame::on_option3Button_clicked()
{
    advanceQuestion(answers->at(questionIndex + 2).second);

}

void LosingMinigame::on_option4Button_clicked()
{
    advanceQuestion(answers->at(questionIndex + 3).second);

}

void LosingMinigame::advanceQuestion(bool goodAnswer){
    if (goodAnswer){
        score++;
    } else {
        score--;
    }

    questionIndex += 4;
    updateFace();
    nextQuestion();
}

void LosingMinigame::initializeAnswers(){
    // question 1 answers
    answers->append(QPair<QString, bool>("Uh yeah, I uh was using a knife and got blood everywhere. I was carving my Thanksgiving turkey.", true));
    answers->append(QPair<QString, bool>("Yeah, everything's fine officer. I accidentally cut myself carving the turkey before dinner.", true));
    answers->append(QPair<QString, bool>("Yes", false));
    answers->append(QPair<QString, bool>("My wife just left me but I'm good thanks.", false));

    //question 2 answers
    answers->append(QPair<QString, bool>("And did he also request a super ugly officer to investigate?", false));
    answers->append(QPair<QString, bool>("I'm not screaming, you're screaming!", false));
    answers->append(QPair<QString, bool>("Yeah, he kind of lost his mind after Vietnam. Did you go over and check in with him before coming over here?", true));
    answers->append(QPair<QString, bool>("I've had my window open all day and didn't hear anything. I'm really busy getting ready for dinner, is it ok if I get back to it?", true));

    //question 3 answers
    answers->append(QPair<QString, bool>("Yes, but I've been playing violin all afternoon since I'm first chair in the orchestra. I've been paying attention to that all afternoon.", true));
    answers->append(QPair<QString, bool>("I .. I don't feel so good..", false));
    answers->append(QPair<QString, bool>("Everything's ok. You can ask any detail about what I've done today. I'm an open book.", true));
    answers->append(QPair<QString, bool>("Yes, trying to copy my mother's pumpkin pie recipe has me all over the place.", false));

    //question 4 answers
    answers->append(QPair<QString, bool>("m", false));
    answers->append(QPair<QString, bool>("n", false));
    answers->append(QPair<QString, bool>("o", true));
    answers->append(QPair<QString, bool>("p", true));

    ui->option1Button->setText("...");
    ui->option2Button->setText("...");
    ui->option3Button->setText("...");
    ui->option4Button->setText("...");
}

void LosingMinigame::initializeQuestions(){
    questions->append("We received a call about some suspicious activity at your house. Is everything ok?");
    questions->append("Your neighbor said he heard someone screaming...?");
    questions->append("Are you sure everything is ok here?");

}

void LosingMinigame::initializeInfoList(){
    infoList->append("The first rule of effective lying is to keep your facts straight. Stay focused and speak naturally. Your story: You cut yourself really bad carving the thanksgiving turkey. Pick an answer that keeps your story coherent.");
    infoList->append("Making a counterattacking statement can be effective in certain situations. Make the officer uncomfortable by making an effective counterattack.");
    infoList->append("Add a small extra detail that's easily maintainable in your lie. Gracefully exit the conversation.");

}

void LosingMinigame::nextQuestion(){

    if (questionIndex / 4 == 3) {
        getGameResult();
    } else {
        ui->infoLabel->setText(infoList->at(questionIndex / 4));
        ui->infoLabel->setVisible(true);
        ui->questionLabel->setText("...");
        ui->option1Button->setText("...");
        ui->option2Button->setText("...");
        ui->option3Button->setText("...");
        ui->option4Button->setText("...");
        QTimer::singleShot(7000, this, &LosingMinigame::hideInfoLabelSlot);
    }

}

void LosingMinigame::updateQuestion(){
    if (charIndex < questions->at(questionIndex / 4).length()){
        ui->questionLabel->setText(questions->at(questionIndex / 4).left(charIndex));
        charIndex++;
    } else {
        updateAnswers();
    }
}

void LosingMinigame::updateAnswers(){
    questionDelay->stop();
    charIndex = 1;
    enableButtons(true);
    ui->questionLabel->setText(questions->at(questionIndex / 4));
    ui->option1Button->setText(answers->at(questionIndex).first);
    ui->option2Button->setText(answers->at(questionIndex + 1).first);
    ui->option3Button->setText(answers->at(questionIndex + 2).first);
    ui->option4Button->setText(answers->at(questionIndex + 3).first);
}

void LosingMinigame::updateFace(){
    QString policeman = QString(":/art/minigame/policeman%1").arg(score);
    ui->faceLabel->setPixmap(QPixmap(policeman));
}

void LosingMinigame::hideInfoLabelSlot(){
    ui->infoLabel->setVisible(false);
    questionDelay->start(50);
}

void LosingMinigame::getGameResult(){
    ui->option1Button->setText("...");
    ui->option2Button->setText("...");
    ui->option3Button->setText("...");
    ui->option4Button->setText("...");

    if (score > 0) {
        QString policeman = QString(":/art/minigame/policeman%1").arg(2);
        ui->questionLabel->setText("Okay then, you're free to go..");
    } else {
        QString policeman = QString(":/art/minigame/policeman%1").arg(-2);
        ui->questionLabel->setText("Alright, you're going to jail!!!!");

    }

    QTimer::singleShot(3000, this, &LosingMinigame::endMiniGameSlot);

}

void LosingMinigame::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
            if (questionDelay->isActive()){
                updateAnswers();
            }
    }
}

void LosingMinigame::endMiniGameSlot(){
    emit changeScene(ENDING);
}
