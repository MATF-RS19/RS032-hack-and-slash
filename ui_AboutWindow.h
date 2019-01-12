/********************************************************************************
** Form generated from reading UI file 'AboutWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTWINDOW_H
#define UI_ABOUTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AboutWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QMainWindow *AboutWindow)
    {
        if (AboutWindow->objectName().isEmpty())
            AboutWindow->setObjectName(QString::fromUtf8("AboutWindow"));
        AboutWindow->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AboutWindow->sizePolicy().hasHeightForWidth());
        AboutWindow->setSizePolicy(sizePolicy);
        AboutWindow->setMinimumSize(QSize(800, 600));
        AboutWindow->setMaximumSize(QSize(800, 600));
        AboutWindow->setBaseSize(QSize(800, 600));
        centralwidget = new QWidget(AboutWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 1950, 798));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 200);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Verdana"));
        font.setPointSize(72);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush1(QColor(255, 255, 255, 128));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush1);
        QBrush brush2(QColor(120, 120, 120, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        QBrush brush3(QColor(0, 0, 0, 128));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush3);
        label_2->setPalette(palette);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Verdana"));
        font1.setPointSize(16);
        label_2->setFont(font1);

        verticalLayout->addWidget(label_2);

        AboutWindow->setCentralWidget(centralwidget);

        retranslateUi(AboutWindow);

        QMetaObject::connectSlotsByName(AboutWindow);
    } // setupUi

    void retranslateUi(QMainWindow *AboutWindow)
    {
        AboutWindow->setWindowTitle(QApplication::translate("AboutWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("AboutWindow", "About", nullptr));
        label_2->setText(QApplication::translate("AboutWindow", "Credits:\n"
"Character animation: https://robert-ramsay.itch.io/\n"
"Map assets: https://finalbossblues.itch.io/, \n"
"                   https://anarchisedlute.itch.io/\n"
"Spell sprites: https://codemanu.itch.io/, \n"
"                     https://indiedevs.itch.io/\n"
"User interface assets: https://ansimuz.itch.io/, \n"
"                                  https://opengameart.org/users/jorge-avila, \n"
"                                  https://www.freepik.com/teinstud\n"
"Sound: Eric Matias https://soundimage.org/,\n"
"            https://www.zapsplat.com/author/soundsparkllc/, \n"
"            https://www.zapsplat.com/author/zapsplat/,\n"
"https://www.freesoundeffects.com/composer/partners-in-rhyme-0/\n"
"\n"
"\n"
"Pavle Radivojevi\304\207\n"
"Loreta Bovan\n"
"\n"
"Faculty of Mathematics, University of Belgrade, 2019.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AboutWindow: public Ui_AboutWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTWINDOW_H
