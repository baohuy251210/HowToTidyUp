#ifndef LOSINGMINIGAME_H
#define LOSINGMINIGAME_H

#include <QWidget>
#include <iscene.h>
#include <QList>
#include <QString>
#include <QPair>



QT_BEGIN_NAMESPACE
namespace Ui {
class LosingMinigame;
}
QT_END_NAMESPACE
class LosingMinigame : public IScene
{
    Q_OBJECT

public:
    explicit LosingMinigame(QWidget *parent = nullptr);
    ~LosingMinigame();
private slots:
    void exitSceneSlot();
    void on_option1Button_clicked();

    void on_option2Button_clicked();

    void on_option3Button_clicked();

    void on_option4Button_clicked();

    void updateQuestion();
protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::LosingMinigame *ui;
    int score;
    int questionIndex;
    QList<QString>* questions;
    QTimer* delay;
    int charIndex;
    QList<QPair<QString, bool>>* answers;

    void initializeQuestions();
    void initializeAnswers();
    void nextQuestion();
    void updateFace();
    void endGame();
    void enableButtons(bool);
    void updateAnswers();


};

#endif // LOSINGMINIGAME_H
