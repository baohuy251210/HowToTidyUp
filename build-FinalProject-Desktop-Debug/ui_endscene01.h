/********************************************************************************
** Form generated from reading UI file 'endscene01.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENDSCENE01_H
#define UI_ENDSCENE01_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
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
            EndScene01->setObjectName(QStringLiteral("EndScene01"));
        EndScene01->resize(1024, 768);
        bgLabel = new QLabel(EndScene01);
        bgLabel->setObjectName(QStringLiteral("bgLabel"));
        bgLabel->setGeometry(QRect(0, 0, 1024, 768));
        bgLabel->setPixmap(QPixmap(QString::fromUtf8(":/art/backgrounds/Art/Backgrounds/Endgame_BG_01.png")));
        bgLabel->setScaledContents(false);

        retranslateUi(EndScene01);

        QMetaObject::connectSlotsByName(EndScene01);
    } // setupUi

    void retranslateUi(QWidget *EndScene01)
    {
        EndScene01->setWindowTitle(QApplication::translate("EndScene01", "Form", Q_NULLPTR));
        bgLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class EndScene01: public Ui_EndScene01 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENDSCENE01_H
