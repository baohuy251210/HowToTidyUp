/********************************************************************************
** Form generated from reading UI file 'endscene02.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENDSCENE02_H
#define UI_ENDSCENE02_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EndScene02
{
public:
    QLabel *bgLabel;

    void setupUi(QWidget *EndScene02)
    {
        if (EndScene02->objectName().isEmpty())
            EndScene02->setObjectName(QString::fromUtf8("EndScene02"));
        EndScene02->resize(1024, 768);
        bgLabel = new QLabel(EndScene02);
        bgLabel->setObjectName(QString::fromUtf8("bgLabel"));
        bgLabel->setGeometry(QRect(0, 0, 1024, 768));
        bgLabel->setPixmap(QPixmap(QString::fromUtf8(":/art/backgrounds/Art/Backgrounds/Endgame_BG_02.png")));

        retranslateUi(EndScene02);

        QMetaObject::connectSlotsByName(EndScene02);
    } // setupUi

    void retranslateUi(QWidget *EndScene02)
    {
        EndScene02->setWindowTitle(QCoreApplication::translate("EndScene02", "Form", nullptr));
        bgLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class EndScene02: public Ui_EndScene02 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENDSCENE02_H
