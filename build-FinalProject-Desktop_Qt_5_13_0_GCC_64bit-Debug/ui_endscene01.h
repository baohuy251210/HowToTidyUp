/********************************************************************************
** Form generated from reading UI file 'endscene01.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENDSCENE01_H
#define UI_ENDSCENE01_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EndScene01
{
public:
    QLabel *bgLabel;

    void setupUi(QWidget *EndScene01)
    {
        if (EndScene01->objectName().isEmpty())
            EndScene01->setObjectName(QString::fromUtf8("EndScene01"));
        EndScene01->resize(1024, 768);
        bgLabel = new QLabel(EndScene01);
        bgLabel->setObjectName(QString::fromUtf8("bgLabel"));
        bgLabel->setGeometry(QRect(0, 0, 1024, 768));
        bgLabel->setPixmap(QPixmap(QString::fromUtf8(":/art/backgrounds/Art/Backgrounds/Endgame_BG_01.png")));
        bgLabel->setScaledContents(false);

        retranslateUi(EndScene01);

        QMetaObject::connectSlotsByName(EndScene01);
    } // setupUi

    void retranslateUi(QWidget *EndScene01)
    {
        EndScene01->setWindowTitle(QCoreApplication::translate("EndScene01", "Form", nullptr));
        bgLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class EndScene01: public Ui_EndScene01 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENDSCENE01_H
