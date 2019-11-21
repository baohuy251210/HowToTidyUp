#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include <QWidget>
#include <iscene.h>
#include <QTimer>
namespace Ui {
class MainMenuScene;
}

class MainMenuScene : public IScene
{
    Q_OBJECT

public:
    explicit MainMenuScene(QWidget *parent = nullptr);
    ~MainMenuScene();
public: signals:

private slots:
    void on_newGameButton_clicked();

    void on_continueButton_clicked();

protected:
    bool eventFilter(QObject* obj,QEvent* e);

private:
    Ui::MainMenuScene *ui;

    void fadeWhiteFlash();
    int fadeOpacity;
    QTimer * fadeTimer;
};

#endif // MAINMENUSCENE_H
