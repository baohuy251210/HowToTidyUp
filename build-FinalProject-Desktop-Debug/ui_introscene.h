/********************************************************************************
** Form generated from reading UI file 'introscene.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTROSCENE_H
#define UI_INTROSCENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IntroScene
{
public:
    QLabel *sceneLbl;

    void setupUi(QWidget *IntroScene)
    {
        if (IntroScene->objectName().isEmpty())
            IntroScene->setObjectName(QStringLiteral("IntroScene"));
        IntroScene->resize(1280, 1024);
        sceneLbl = new QLabel(IntroScene);
        sceneLbl->setObjectName(QStringLiteral("sceneLbl"));
        sceneLbl->setGeometry(QRect(0, 0, 1280, 1024));

        retranslateUi(IntroScene);

        QMetaObject::connectSlotsByName(IntroScene);
    } // setupUi

    void retranslateUi(QWidget *IntroScene)
    {
        IntroScene->setWindowTitle(QApplication::translate("IntroScene", "Form", Q_NULLPTR));
        sceneLbl->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class IntroScene: public Ui_IntroScene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTROSCENE_H
