#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iscene.h>
#include <SFML/Audio.hpp>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void ChangeScene(IScene* scene);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    IScene* currentScene;

    void startThemeMusic();
    sf::Music mainThemeMusic;
};
#endif // MAINWINDOW_H
