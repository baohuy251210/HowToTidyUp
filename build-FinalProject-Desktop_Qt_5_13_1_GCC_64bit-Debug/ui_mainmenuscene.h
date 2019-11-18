/********************************************************************************
** Form generated from reading UI file 'mainmenuscene.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINMENUSCENE_H
#define UI_MAINMENUSCENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainMenuScene
{
public:

    void setupUi(QWidget *MainMenuScene)
    {
        if (MainMenuScene->objectName().isEmpty())
            MainMenuScene->setObjectName(QString::fromUtf8("MainMenuScene"));
        MainMenuScene->resize(637, 501);

        retranslateUi(MainMenuScene);

        QMetaObject::connectSlotsByName(MainMenuScene);
    } // setupUi

    void retranslateUi(QWidget *MainMenuScene)
    {
        MainMenuScene->setWindowTitle(QCoreApplication::translate("MainMenuScene", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainMenuScene: public Ui_MainMenuScene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINMENUSCENE_H
