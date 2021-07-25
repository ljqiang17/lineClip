/********************************************************************************
** Form generated from reading UI file 'lineclip.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINECLIP_H
#define UI_LINECLIP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LineClip
{
public:

    void setupUi(QWidget *LineClip)
    {
        if (LineClip->objectName().isEmpty())
            LineClip->setObjectName(QString::fromUtf8("LineClip"));
        LineClip->resize(400, 300);

        retranslateUi(LineClip);

        QMetaObject::connectSlotsByName(LineClip);
    } // setupUi

    void retranslateUi(QWidget *LineClip)
    {
        LineClip->setWindowTitle(QApplication::translate("LineClip", "LineClip", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LineClip: public Ui_LineClip {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINECLIP_H
