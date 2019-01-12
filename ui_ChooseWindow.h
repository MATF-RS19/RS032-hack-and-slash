/********************************************************************************
** Form generated from reading UI file 'ChooseWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEWINDOW_H
#define UI_CHOOSEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChooseWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QPushButton *hackButton;
    QPushButton *slashButton;

    void setupUi(QMainWindow *ChooseWindow)
    {
        if (ChooseWindow->objectName().isEmpty())
            ChooseWindow->setObjectName(QString::fromUtf8("ChooseWindow"));
        ChooseWindow->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ChooseWindow->sizePolicy().hasHeightForWidth());
        ChooseWindow->setSizePolicy(sizePolicy);
        ChooseWindow->setMinimumSize(QSize(200, 600));
        ChooseWindow->setMaximumSize(QSize(800, 600));
        ChooseWindow->setBaseSize(QSize(800, 600));
        ChooseWindow->setMouseTracking(false);
        centralwidget = new QWidget(ChooseWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 821, 601));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(20, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(800, 0));
        QFont font;
        font.setFamily(QString::fromUtf8("Verdana"));
        font.setPointSize(72);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, 30, -1);
        hackButton = new QPushButton(verticalLayoutWidget);
        hackButton->setObjectName(QString::fromUtf8("hackButton"));
        sizePolicy.setHeightForWidth(hackButton->sizePolicy().hasHeightForWidth());
        hackButton->setSizePolicy(sizePolicy);
        hackButton->setMinimumSize(QSize(340, 420));
        hackButton->setMaximumSize(QSize(349, 420));
        hackButton->setBaseSize(QSize(350, 420));

        horizontalLayout->addWidget(hackButton);

        slashButton = new QPushButton(verticalLayoutWidget);
        slashButton->setObjectName(QString::fromUtf8("slashButton"));
        sizePolicy.setHeightForWidth(slashButton->sizePolicy().hasHeightForWidth());
        slashButton->setSizePolicy(sizePolicy);
        slashButton->setMinimumSize(QSize(340, 420));
        slashButton->setMaximumSize(QSize(340, 420));

        horizontalLayout->addWidget(slashButton);


        verticalLayout->addLayout(horizontalLayout);

        ChooseWindow->setCentralWidget(centralwidget);

        retranslateUi(ChooseWindow);

        QMetaObject::connectSlotsByName(ChooseWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ChooseWindow)
    {
        ChooseWindow->setWindowTitle(QApplication::translate("ChooseWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("ChooseWindow", "Choose player", nullptr));
        hackButton->setText(QString());
        slashButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ChooseWindow: public Ui_ChooseWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEWINDOW_H
