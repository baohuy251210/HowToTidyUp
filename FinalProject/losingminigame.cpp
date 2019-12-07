#include "losingminigame.h"
#include "ui_losingminigame.h"
#include <QTimer>

LosingMinigame::LosingMinigame(QWidget *parent) :
    IScene(parent),
    ui(new Ui::LosingMinigame), score(0), questionIndex(0)
{
    ui->setupUi(this);
    questions = new QList<QString>();
    answers = new QList<QPair<QString, bool>>();
    delay = new QTimer(this);
    charIndex = 1;
    connect(delay, &QTimer::timeout, this, &LosingMinigame::updateQuestion);

    initializeAnswers();
    initializeQuestions();

    ui->dialogLabel->lower();
    ui->faceLabel->lower();
    ui->bgLabel->lower();

    enableButtons(false);

    nextQuestion();

}

LosingMinigame::~LosingMinigame()
{
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
    questions->append("q11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
    questions->append("q2");
    questions->append("q3");

}

void LosingMinigame::nextQuestion(){
    if (questionIndex / 4 == 3) {
        endGame();
    } else {
        delay->start(100);
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
    delay->stop();
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

void LosingMinigame::endGame(){
    ui->option1Button->setText("...");
    ui->option2Button->setText("...");
    ui->option3Button->setText("...");
    ui->option4Button->setText("...");

    if (score > 0) {
        ui->questionLabel->setText("Alright, youu're going to jail!!!!");
    } else {
        ui->questionLabel->setText("Okay then, you're free to go..");

    }

    emit changeScene(ENDING);
}

void LosingMinigame::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
            if (delay->isActive())
                updateAnswers();
            }
}
