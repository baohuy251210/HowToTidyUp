/********************************************************************************
** Form generated from reading UI file 'mainmenuscene.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINMENUSCENE_H
#define UI_MAINMENUSCENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainMenuScene
{
public:
    QLabel *bgLabel;
    QPushButton *newGameButton;
    QLabel *maskLabel;
    QLabel *nameLabel;

    void setupUi(QWidget *MainMenuScene)
    {
        if (MainMenuScene->objectName().isEmpty())
            MainMenuScene->setObjectName(QStringLiteral("MainMenuScene"));
        MainMenuScene->resize(1024, 768);
        bgLabel = new QLabel(MainMenuScene);
        bgLabel->setObjectName(QStringLiteral("bgLabel"));
        bgLabel->setGeometry(QRect(0, 0, 1024, 768));
        bgLabel->setPixmap(QPixmap(QString::fromUtf8(":/art/backgrounds/Art/Backgrounds/MainScreen_BG_01.png")));
        newGameButton = new QPushButton(MainMenuScene);
        newGameButton->setObjectName(QStringLiteral("newGameButton"));
        newGameButton->setGeometry(QRect(60, 560, 291, 71));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        QBrush brush1(QColor(164, 166, 168, 96));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        newGameButton->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu"));
        font.setPointSize(36);
        font.setBold(true);
        font.setWeight(75);
        newGameButton->setFont(font);
        newGameButton->setFlat(true);
        maskLabel = new QLabel(MainMenuScene);
        maskLabel->setObjectName(QStringLiteral("maskLabel"));
        maskLabel->setGeometry(QRect(0, 0, 71, 31));
        nameLabel = new QLabel(MainMenuScene);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));
        nameLabel->setGeometry(QRect(50, 20, 481, 81));
        QFont font1;
        font1.setPointSize(46);
        nameLabel->setFont(font1);
        nameLabel->setStyleSheet(QStringLiteral("color: rgb(46, 52, 54);"));
        bgLabel->raise();
        newGameButton->raise();
        nameLabel->raise();
        maskLabel->raise();

        retranslateUi(MainMenuScene);

        QMetaObject::connectSlotsByName(MainMenuScene);
    } // setupUi

    void retranslateUi(QWidget *MainMenuScene)
    {
        MainMenuScene->setWindowTitle(QApplication::translate("MainMenuScene", "Form", Q_NULLPTR));
        bgLabel->setText(QString());
        newGameButton->setText(QApplication::translate("MainMenuScene", "New Game", Q_NULLPTR));
        maskLabel->setText(QString());
        nameLabel->setText(QApplication::translate("MainMenuScene", "How to Tidy Up", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainMenuScene: public Ui_MainMenuScene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINMENUSCENE_H
