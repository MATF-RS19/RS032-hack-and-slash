/********************************************************************************
** Form generated from reading UI file 'LoadingScreen.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADINGSCREEN_H
#define UI_LOADINGSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoadingScreen
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;

    void setupUi(QMainWindow *LoadingScreen)
    {
        if (LoadingScreen->objectName().isEmpty())
            LoadingScreen->setObjectName(QString::fromUtf8("LoadingScreen"));
        LoadingScreen->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LoadingScreen->sizePolicy().hasHeightForWidth());
        LoadingScreen->setSizePolicy(sizePolicy);
        LoadingScreen->setMinimumSize(QSize(800, 600));
        LoadingScreen->setMaximumSize(QSize(800, 600));
        centralwidget = new QWidget(LoadingScreen);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMinimumSize(QSize(800, 600));
        centralwidget->setMaximumSize(QSize(800, 600));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 861, 661));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(800, 600));
        label->setMaximumSize(QSize(800, 600));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        LoadingScreen->setCentralWidget(centralwidget);

        retranslateUi(LoadingScreen);

        QMetaObject::connectSlotsByName(LoadingScreen);
    } // setupUi

    void retranslateUi(QMainWindow *LoadingScreen)
    {
        LoadingScreen->setWindowTitle(QApplication::translate("LoadingScreen", "HackAndSlash", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoadingScreen: public Ui_LoadingScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADINGSCREEN_H
