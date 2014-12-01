/********************************************************************************
** Form generated from reading UI file 'vk.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VK_H
#define UI_VK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Vk
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QLineEdit *lineEdit;

    void setupUi(QDialog *Vk)
    {
        if (Vk->objectName().isEmpty())
            Vk->setObjectName(QStringLiteral("Vk"));
        Vk->resize(1080, 640);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Vk->sizePolicy().hasHeightForWidth());
        Vk->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(Vk);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        textBrowser = new QTextBrowser(Vk);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        sizePolicy.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy);
        textBrowser->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout->addWidget(textBrowser);

        lineEdit = new QLineEdit(Vk);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy1);
        lineEdit->setMaximumSize(QSize(16777215, 22));
        lineEdit->setBaseSize(QSize(19999, 0));

        verticalLayout->addWidget(lineEdit);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(Vk);
        QObject::connect(lineEdit, SIGNAL(returnPressed()), Vk, SLOT(onReturn()));

        QMetaObject::connectSlotsByName(Vk);
    } // setupUi

    void retranslateUi(QDialog *Vk)
    {
        Vk->setWindowTitle(QApplication::translate("Vk", "Vk", 0));
    } // retranslateUi

};

namespace Ui {
    class Vk: public Ui_Vk {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VK_H
