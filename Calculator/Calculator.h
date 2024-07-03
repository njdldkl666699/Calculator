#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Calculator.h"
#include <QSoundEffect>

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void buttonNumClicked(QAbstractButton*);

    void buttonOperatorClicked(QAbstractButton*);

    void buttonEqualClicked();

    void buttonBracketClicked();

    void buttonCClicked();

    void buttonDelClicked();

    void buttonDotClicked();

    void buttonSignClicked();

private:
    Ui::CalculatorClass ui;

    QSoundEffect* effect;
    QString expression;
    QString val;
};
