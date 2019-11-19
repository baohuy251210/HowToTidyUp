/********************************************************************************
** Form generated from reading UI file 'mainmenuscene.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINMENUSCENE_H
#define UI_MAINMENUSCENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
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
    QLabel *aMurder;

    void setupUi(QWidget *MainMenuScene)
    {
        if (MainMenuScene->objectName().isEmpty())
            MainMenuScene->setObjectName(QString::fromUtf8("MainMenuScene"));
        MainMenuScene->resize(1024, 768);
        bgLabel = new QLabel(MainMenuScene);
        bgLabel->setObjectName(QString::fromUtf8("bgLabel"));
        bgLabel->setGeometry(QRect(0, 0, 1024, 768));
        bgLabel->setPixmap(QPixmap(QString::fromUtf8(":/art/backgrounds/Art/Backgrounds/MainScreen_BG_01.png")));
        newGameButton = new QPushButton(MainMenuScene);
        newGameButton->setObjectName(QString::fromUtf8("newGameButton"));
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
        font.setFamily(QString::fromUtf8("Ubuntu"));
        font.setPointSize(36);
        font.setBold(true);
        font.setWeight(75);
        newGameButton->setFont(font);
        newGameButton->setFlat(true);
        maskLabel = new QLabel(MainMenuScene);
        maskLabel->setObjectName(QString::fromUtf8("maskLabel"));
        maskLabel->setGeometry(QRect(0, 0, 71, 31));
        nameLabel = new QLabel(MainMenuScene);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        nameLabel->setGeometry(QRect(50, 20, 481, 81));
        QFont font1;
        font1.setPointSize(46);
        nameLabel->setFont(font1);
        nameLabel->setStyleSheet(QString::fromUtf8("color: rgb(46, 52, 54);"));
        aMurder = new QLabel(MainMenuScene);
        aMurder->setObjectName(QString::fromUtf8("aMurder"));
        aMurder->setGeometry(QRect(50, 50, 421, 181));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Fiendish"));
        font2.setPointSize(34);
        font2.setBold(true);
        font2.setItalic(true);
        font2.setWeight(75);
        aMurder->setFont(font2);
        aMurder->setStyleSheet(QString::fromUtf8("color: rgb(204, 0, 0);"));
        aMurder->setAlignment(Qt::AlignCenter);
        bgLabel->raise();
        newGameButton->raise();
        nameLabel->raise();
        maskLabel->raise();
        aMurder->raise();

        retranslateUi(MainMenuScene);

        QMetaObject::connectSlotsByName(MainMenuScene);
    } // setupUi

    void retranslateUi(QWidget *MainMenuScene)
    {
        MainMenuScene->setWindowTitle(QCoreApplication::translate("MainMenuScene", "Form", nullptr));
        bgLabel->setText(QString());
        newGameButton->setText(QCoreApplication::translate("MainMenuScene", "New Game", nullptr));
        maskLabel->setText(QString());
        nameLabel->setText(QCoreApplication::translate("MainMenuScene", "How to Tidy Up", nullptr));
        aMurder->setText(QCoreApplication::translate("MainMenuScene", "a Murder", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainMenuScene: public Ui_MainMenuScene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINMENUSCENE_H
