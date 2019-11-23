/********************************************************************************
** Form generated from reading UI file 'intro.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTRO_H
#define UI_INTRO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Intro
{
public:
    QLabel *label;

    void setupUi(QWidget *Intro)
    {
        if (Intro->objectName().isEmpty())
            Intro->setObjectName(QString::fromUtf8("Intro"));
        Intro->resize(800, 600);
        label = new QLabel(Intro);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 800, 600));

        retranslateUi(Intro);

        QMetaObject::connectSlotsByName(Intro);
    } // setupUi

    void retranslateUi(QWidget *Intro)
    {
        Intro->setWindowTitle(QCoreApplication::translate("Intro", "Form", nullptr));
        label->setText(QCoreApplication::translate("Intro", "YOOOOO", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Intro: public Ui_Intro {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTRO_H
