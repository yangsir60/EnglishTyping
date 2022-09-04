/********************************************************************************
** Form generated from reading UI file 'qt5test.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT5TEST_H
#define UI_QT5TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qt5testClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *qt5testClass)
    {
        if (qt5testClass->objectName().isEmpty())
            qt5testClass->setObjectName(QStringLiteral("qt5testClass"));
        qt5testClass->resize(600, 400);
        menuBar = new QMenuBar(qt5testClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        qt5testClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(qt5testClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        qt5testClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(qt5testClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        qt5testClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(qt5testClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        qt5testClass->setStatusBar(statusBar);

        retranslateUi(qt5testClass);

        QMetaObject::connectSlotsByName(qt5testClass);
    } // setupUi

    void retranslateUi(QMainWindow *qt5testClass)
    {
        qt5testClass->setWindowTitle(QApplication::translate("qt5testClass", "qt5test", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class qt5testClass: public Ui_qt5testClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT5TEST_H
