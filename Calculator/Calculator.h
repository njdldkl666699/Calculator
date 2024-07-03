#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Calculator.h"

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

    void buttonCEClicked();

    void buttonCClicked();

    void buttonDelClicked();

    void buttonDotClicked();

    void buttonSignClicked();

private:
    Ui::CalculatorClass ui;

    double preVal;

    bool isRlt;
    
    QAbstractButton* preOperator;
};
