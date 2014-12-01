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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Vk
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout2;
    QTextBrowser *textBrowser;
    QLineEdit *lineEdit;
    QListWidget *listWidget;

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
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout2 = new QVBoxLayout();
        verticalLayout2->setSpacing(6);
        verticalLayout2->setObjectName(QStringLiteral("verticalLayout2"));
        textBrowser = new QTextBrowser(Vk);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        sizePolicy.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy);
        textBrowser->setMaximumSize(QSize(16777215, 16777215));
        textBrowser->setFocusPolicy(Qt::NoFocus);

        verticalLayout2->addWidget(textBrowser);

        lineEdit = new QLineEdit(Vk);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy1);
        lineEdit->setMaximumSize(QSize(16777215, 22));
        lineEdit->setBaseSize(QSize(19999, 0));

        verticalLayout2->addWidget(lineEdit);


        horizontalLayout->addLayout(verticalLayout2);

        listWidget = new QListWidget(Vk);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(listWidget);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(Vk);
        QObject::connect(lineEdit, SIGNAL(returnPressed()), Vk, SLOT(onReturn()));
        QObject::connect(listWidget, SIGNAL(itemActivated(QListWidgetItem*)), Vk, SLOT(onItemDoubleClicked(QListWidgetItem*)));

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
