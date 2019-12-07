#include "losingminigame.h"
#include "ui_losingminigame.h"

LosingMinigame::LosingMinigame(QWidget *parent) :
    IScene(parent),
    ui(new Ui::LosingMinigame), score(0), questionIndex(0)
{
    ui->setupUi(this);
    questions = new QList<QString>();
    answers = new QList<QPair<QString, bool>>();

    initializeAnswers();
    initializeQuestions();

    ui->faceLabel->lower();
    ui->bgLabel->lower();


    ui->questionLabel->setText(questions->at(0));
    ui->option1Button->setText(answers->at(0).first);
    ui->option2Button->setText(answers->at(1).first);
    ui->option3Button->setText(answers->at(2).first);
    ui->option4Button->setText(answers->at(3).first);

}

LosingMinigame::~LosingMinigame()
{
    delete ui;
}

void LosingMinigame::exitSceneSlot(){
    emit changeScene(MAINMENU);
}

void LosingMinigame::on_option1Button_clicked()
{
    bool goodAnswer = answers->at(questionIndex).second;
    if (goodAnswer){
        score++;
    } else {
        score--;
    }
    questionIndex += 4;
    updateFace();
    nextQuestion();
}

void LosingMinigame::on_option2Button_clicked()
{
    bool goodAnswer = answers->at(questionIndex + 1).second;
    if (goodAnswer){
        score++;
    } else {
        score--;
    }
    questionIndex += 4;
    updateFace();
    nextQuestion();
}

void LosingMinigame::on_option3Button_clicked()
{
    bool goodAnswer = answers->at(questionIndex + 2).second;
    if (goodAnswer){
        score++;
    } else {
        score--;
    }
    questionIndex += 4;
    updateFace();
    nextQuestion();
}

void LosingMinigame::on_option4Button_clicked()
{
    bool goodAnswer = answers->at(questionIndex + 3).second;
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
    answers->append(QPair<QString, bool>("a", false));
    answers->append(QPair<QString, bool>("b", false));
    answers->append(QPair<QString, bool>("c", true));
    answers->append(QPair<QString, bool>("d", true));

    //question 2 answers
    answers->append(QPair<QString, bool>("e", false));
    answers->append(QPair<QString, bool>("f", false));
    answers->append(QPair<QString, bool>("g", true));
    answers->append(QPair<QString, bool>("h", true));

    //question 3 answers
    answers->append(QPair<QString, bool>("i", false));
    answers->append(QPair<QString, bool>("j", false));
    answers->append(QPair<QString, bool>("k", true));
    answers->append(QPair<QString, bool>("l", true));

    //question 4 answers
    answers->append(QPair<QString, bool>("m", false));
    answers->append(QPair<QString, bool>("n", false));
    answers->append(QPair<QString, bool>("o", true));
    answers->append(QPair<QString, bool>("p", true));
}

void LosingMinigame::initializeQuestions(){
    questions->append("q1");
    questions->append("q2");
    questions->append("q3");

}

void LosingMinigame::nextQuestion(){
    if (questionIndex / 4 == 3) {
        endGame();
    } else {
        ui->questionLabel->setText(questions->at(questionIndex / 4));
        ui->option1Button->setText(answers->at(questionIndex).first);
        ui->option2Button->setText(answers->at(questionIndex + 1).first);
        ui->option3Button->setText(answers->at(questionIndex + 2).first);
        ui->option4Button->setText(answers->at(questionIndex + 3).first);
    }

}

void LosingMinigame::updateFace(){
    QString policeman = QString(":/art/minigame/policeman%1").arg(score);
    ui->faceLabel->setPixmap(QPixmap(policeman));
}

void LosingMinigame::endGame(){
    emit changeScene(MAINMENU);
}
