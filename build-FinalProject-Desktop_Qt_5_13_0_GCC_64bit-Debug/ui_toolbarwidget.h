/********************************************************************************
** Form generated from reading UI file 'toolbarwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOOLBARWIDGET_H
#define UI_TOOLBARWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ToolbarWidget
{
public:
    QPushButton *gloveButton;
    QPushButton *pushButton;
    QLabel *bgLabel;

    void setupUi(QWidget *ToolbarWidget)
    {
        if (ToolbarWidget->objectName().isEmpty())
            ToolbarWidget->setObjectName(QString::fromUtf8("ToolbarWidget"));
        ToolbarWidget->resize(873, 146);
        gloveButton = new QPushButton(ToolbarWidget);
        gloveButton->setObjectName(QString::fromUtf8("gloveButton"));
        gloveButton->setGeometry(QRect(18, 20, 111, 91));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/art/tools/Art/Tools/tool_glove_01.png"), QSize(), QIcon::Normal, QIcon::Off);
        gloveButton->setIcon(icon);
        gloveButton->setIconSize(QSize(128, 128));
        gloveButton->setFlat(true);
        pushButton = new QPushButton(ToolbarWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(148, 20, 111, 101));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/art/tools/Art/Tools/tool_rag_01.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon1);
        pushButton->setIconSize(QSize(128, 128));
        pushButton->setFlat(true);
        bgLabel = new QLabel(ToolbarWidget);
        bgLabel->setObjectName(QString::fromUtf8("bgLabel"));
        bgLabel->setGeometry(QRect(13, 6, 841, 121));
        bgLabel->setAutoFillBackground(false);
        bgLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(136, 138, 133);"));
        bgLabel->raise();
        gloveButton->raise();
        pushButton->raise();

        retranslateUi(ToolbarWidget);

        QMetaObject::connectSlotsByName(ToolbarWidget);
    } // setupUi

    void retranslateUi(QWidget *ToolbarWidget)
    {
        ToolbarWidget->setWindowTitle(QCoreApplication::translate("ToolbarWidget", "Form", nullptr));
        gloveButton->setText(QString());
        pushButton->setText(QString());
        bgLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ToolbarWidget: public Ui_ToolbarWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOOLBARWIDGET_H
