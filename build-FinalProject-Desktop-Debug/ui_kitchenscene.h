/********************************************************************************
** Form generated from reading UI file 'kitchenscene.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KITCHENSCENE_H
#define UI_KITCHENSCENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include "toolbarwidget.h"

QT_BEGIN_NAMESPACE

class Ui_KitchenScene
{
public:
    QLabel *bgLabel;
    ToolbarWidget *toolbarWidget;

    void setupUi(QWidget *KitchenScene)
    {
        if (KitchenScene->objectName().isEmpty())
            KitchenScene->setObjectName(QStringLiteral("KitchenScene"));
        KitchenScene->resize(1024, 768);
        bgLabel = new QLabel(KitchenScene);
        bgLabel->setObjectName(QStringLiteral("bgLabel"));
        bgLabel->setGeometry(QRect(0, 0, 1024, 768));
        bgLabel->setPixmap(QPixmap(QString::fromUtf8(":/art/backgrounds/Art/Backgrounds/Kitchen_BG_01.png")));
        toolbarWidget = new ToolbarWidget(KitchenScene);
        toolbarWidget->setObjectName(QStringLiteral("toolbarWidget"));
        toolbarWidget->setGeometry(QRect(70, 590, 1018, 151));

        retranslateUi(KitchenScene);

        QMetaObject::connectSlotsByName(KitchenScene);
    } // setupUi

    void retranslateUi(QWidget *KitchenScene)
    {
        KitchenScene->setWindowTitle(QApplication::translate("KitchenScene", "Form", Q_NULLPTR));
        bgLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class KitchenScene: public Ui_KitchenScene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KITCHENSCENE_H
