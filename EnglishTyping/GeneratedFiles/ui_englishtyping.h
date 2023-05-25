/********************************************************************************
** Form generated from reading UI file 'englishtyping.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENGLISHTYPING_H
#define UI_ENGLISHTYPING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EnglishTypingClass
{
public:
    QAction *action_json;
    QAction *action;
    QAction *action_2;
    QAction *action_csv;
    QAction *action_showtime;
    QAction *action_hidetime;
    QAction *actioncloseTips;
    QAction *actionopenTips;
    QAction *actionDetialMean;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *lb_chinese;
    QLineEdit *english_sr;
    QVBoxLayout *verticalLayout_4;
    QLabel *tips;
    QLabel *label;
    QSpacerItem *verticalSpacer_2;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EnglishTypingClass)
    {
        if (EnglishTypingClass->objectName().isEmpty())
            EnglishTypingClass->setObjectName(QStringLiteral("EnglishTypingClass"));
        EnglishTypingClass->resize(597, 400);
        action_json = new QAction(EnglishTypingClass);
        action_json->setObjectName(QStringLiteral("action_json"));
        action = new QAction(EnglishTypingClass);
        action->setObjectName(QStringLiteral("action"));
        action_2 = new QAction(EnglishTypingClass);
        action_2->setObjectName(QStringLiteral("action_2"));
        action_csv = new QAction(EnglishTypingClass);
        action_csv->setObjectName(QStringLiteral("action_csv"));
        action_showtime = new QAction(EnglishTypingClass);
        action_showtime->setObjectName(QStringLiteral("action_showtime"));
        action_hidetime = new QAction(EnglishTypingClass);
        action_hidetime->setObjectName(QStringLiteral("action_hidetime"));
        actioncloseTips = new QAction(EnglishTypingClass);
        actioncloseTips->setObjectName(QStringLiteral("actioncloseTips"));
        actionopenTips = new QAction(EnglishTypingClass);
        actionopenTips->setObjectName(QStringLiteral("actionopenTips"));
        actionDetialMean = new QAction(EnglishTypingClass);
        actionDetialMean->setObjectName(QStringLiteral("actionDetialMean"));
        centralWidget = new QWidget(EnglishTypingClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        lb_chinese = new QLabel(centralWidget);
        lb_chinese->setObjectName(QStringLiteral("lb_chinese"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(40);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        lb_chinese->setFont(font);
        lb_chinese->setStyleSheet(QString::fromUtf8("font: 40pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        lb_chinese->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(lb_chinese);

        english_sr = new QLineEdit(centralWidget);
        english_sr->setObjectName(QStringLiteral("english_sr"));
        english_sr->setMinimumSize(QSize(0, 50));
        english_sr->setStyleSheet(QString::fromUtf8("font:20pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        english_sr->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(english_sr);


        verticalLayout->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        tips = new QLabel(centralWidget);
        tips->setObjectName(QStringLiteral("tips"));
        tips->setMinimumSize(QSize(0, 47));
        tips->setMaximumSize(QSize(16777215, 30));
        tips->setStyleSheet(QString::fromUtf8("color:rgb(0, 170, 0);\n"
"font: 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        tips->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(tips);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(17);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("font:17pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"padding-top:0px;\n"
"padding-bottom:0px;"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);


        verticalLayout->addLayout(verticalLayout_4);

        verticalLayout->setStretch(0, 4);
        verticalLayout->setStretch(1, 3);

        verticalLayout_2->addLayout(verticalLayout);

        EnglishTypingClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(EnglishTypingClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 597, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        EnglishTypingClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(EnglishTypingClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        EnglishTypingClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menu->addAction(action_json);
        menu->addAction(action_csv);
        menu_2->addAction(action);
        menu_2->addAction(action_showtime);
        menu_2->addAction(action_hidetime);
        menu_2->addAction(actioncloseTips);
        menu_2->addAction(actionopenTips);
        menu_2->addAction(actionDetialMean);
        menu_3->addAction(action_2);

        retranslateUi(EnglishTypingClass);

        QMetaObject::connectSlotsByName(EnglishTypingClass);
    } // setupUi

    void retranslateUi(QMainWindow *EnglishTypingClass)
    {
        EnglishTypingClass->setWindowTitle(QApplication::translate("EnglishTypingClass", "EnglishTyping", Q_NULLPTR));
        action_json->setText(QApplication::translate("EnglishTypingClass", "\345\257\274\345\205\245json\345\215\225\350\257\215\346\226\207\344\273\266", Q_NULLPTR));
        action->setText(QApplication::translate("EnglishTypingClass", "\351\246\226\351\200\211\351\241\271", Q_NULLPTR));
        action_2->setText(QApplication::translate("EnglishTypingClass", "\345\205\263\344\272\216", Q_NULLPTR));
        action_csv->setText(QApplication::translate("EnglishTypingClass", "\350\257\273\345\217\226csv\345\215\225\350\257\215\346\226\207\344\273\266", Q_NULLPTR));
        action_showtime->setText(QApplication::translate("EnglishTypingClass", "\346\230\276\347\244\272\346\227\266\351\227\264", Q_NULLPTR));
        action_hidetime->setText(QApplication::translate("EnglishTypingClass", "\351\232\220\350\227\217\346\227\266\351\227\264", Q_NULLPTR));
        actioncloseTips->setText(QApplication::translate("EnglishTypingClass", "closeTips", Q_NULLPTR));
        actionopenTips->setText(QApplication::translate("EnglishTypingClass", "openTips", Q_NULLPTR));
        actionDetialMean->setText(QApplication::translate("EnglishTypingClass", "\345\215\225\350\257\215\350\257\246\347\273\206", Q_NULLPTR));
        lb_chinese->setText(QApplication::translate("EnglishTypingClass", "\344\270\255\346\226\207", Q_NULLPTR));
        english_sr->setText(QApplication::translate("EnglishTypingClass", "chinese", Q_NULLPTR));
        tips->setText(QApplication::translate("EnglishTypingClass", "Right", Q_NULLPTR));
        label->setText(QApplication::translate("EnglishTypingClass", "TextLabel", Q_NULLPTR));
        menu->setTitle(QApplication::translate("EnglishTypingClass", "\350\217\234\345\215\225", Q_NULLPTR));
        menu_2->setTitle(QApplication::translate("EnglishTypingClass", "\350\256\276\347\275\256", Q_NULLPTR));
        menu_3->setTitle(QApplication::translate("EnglishTypingClass", "\345\270\256\345\212\251", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class EnglishTypingClass: public Ui_EnglishTypingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENGLISHTYPING_H
