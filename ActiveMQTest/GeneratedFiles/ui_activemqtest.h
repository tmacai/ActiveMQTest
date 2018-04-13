/********************************************************************************
** Form generated from reading UI file 'activemqtest.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACTIVEMQTEST_H
#define UI_ACTIVEMQTEST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ActiveMQTestClass
{
public:
    QWidget *centralWidget;
    QPushButton *pbSend;
    QLineEdit *lEdtSend;
    QLabel *label;
    QLabel *label_2;
    QTextEdit *textEditRecv;
    QPushButton *pbClear;
    QPushButton *pbRead;

    void setupUi(QMainWindow *ActiveMQTestClass)
    {
        if (ActiveMQTestClass->objectName().isEmpty())
            ActiveMQTestClass->setObjectName(QString::fromUtf8("ActiveMQTestClass"));
        ActiveMQTestClass->resize(859, 742);
        centralWidget = new QWidget(ActiveMQTestClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pbSend = new QPushButton(centralWidget);
        pbSend->setObjectName(QString::fromUtf8("pbSend"));
        pbSend->setGeometry(QRect(740, 30, 91, 41));
        lEdtSend = new QLineEdit(centralWidget);
        lEdtSend->setObjectName(QString::fromUtf8("lEdtSend"));
        lEdtSend->setGeometry(QRect(80, 20, 641, 61));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 40, 54, 12));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 110, 81, 20));
        textEditRecv = new QTextEdit(centralWidget);
        textEditRecv->setObjectName(QString::fromUtf8("textEditRecv"));
        textEditRecv->setGeometry(QRect(90, 100, 741, 561));
        pbClear = new QPushButton(centralWidget);
        pbClear->setObjectName(QString::fromUtf8("pbClear"));
        pbClear->setGeometry(QRect(90, 680, 81, 41));
        pbRead = new QPushButton(centralWidget);
        pbRead->setObjectName(QString::fromUtf8("pbRead"));
        pbRead->setGeometry(QRect(200, 680, 81, 41));
        ActiveMQTestClass->setCentralWidget(centralWidget);

        retranslateUi(ActiveMQTestClass);

        QMetaObject::connectSlotsByName(ActiveMQTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *ActiveMQTestClass)
    {
        ActiveMQTestClass->setWindowTitle(QApplication::translate("ActiveMQTestClass", "ActiveMQTest", 0, QApplication::UnicodeUTF8));
        pbSend->setText(QApplication::translate("ActiveMQTestClass", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ActiveMQTestClass", "\345\217\221\351\200\201\345\206\205\345\256\271\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ActiveMQTestClass", "\346\216\245\346\224\266\345\210\260\347\232\204\345\206\205\345\256\271\357\274\232", 0, QApplication::UnicodeUTF8));
        pbClear->setText(QApplication::translate("ActiveMQTestClass", "\346\270\205\351\231\244", 0, QApplication::UnicodeUTF8));
        pbRead->setText(QApplication::translate("ActiveMQTestClass", "\350\257\273\345\217\226", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ActiveMQTestClass: public Ui_ActiveMQTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACTIVEMQTEST_H
