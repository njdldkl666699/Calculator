#include "Calculator.h"

Calculator::Calculator(QWidget* parent)
    : QMainWindow(parent), preVal(0.0), preOperator(nullptr)
{
    ui.setupUi(this);
    connect(ui.buttonNumGroup, &QButtonGroup::buttonClicked, this, &Calculator::buttonNumClicked);
    connect(ui.buttonOperatorGroup, &QButtonGroup::buttonClicked, this, &Calculator::buttonOperatorClicked);
    connect(ui.pushButton_equal, &QPushButton::clicked, this, &Calculator::buttonEqualClicked);
    connect(ui.pushButton_ce, &QPushButton::clicked, this, &Calculator::buttonCEClicked);
    connect(ui.pushButton_c, &QPushButton::clicked, this, &Calculator::buttonCClicked);
    connect(ui.pushButton_del, &QPushButton::clicked, this, &Calculator::buttonDelClicked);
    connect(ui.pushButton_dot, &QPushButton::clicked, this, &Calculator::buttonDotClicked);
    connect(ui.pushButton_sign, &QPushButton::clicked, this, &Calculator::buttonSignClicked);
}

Calculator::~Calculator()
{}

void Calculator::buttonNumClicked(QAbstractButton* button)
{
    const auto& buttonName = button->objectName();
    auto text = ui.lineEdit->text();
    if (buttonName.isEmpty())
        return;
    else
    {
        const QChar num = buttonName.back();
        if (text.isEmpty() || text == "0")
            text = num;
        else
            text += num;
        ui.lineEdit->setText(text);
    }
}

void Calculator::buttonOperatorClicked(QAbstractButton* button)
{
    const auto& buttonName = button->objectName();
    if (buttonName.isEmpty())
        return;
    else
    {
        if (preOperator != nullptr)
        {
            const auto& preBtnName = preOperator->objectName();
            const auto& num = ui.lineEdit->text().toDouble();
            if (preBtnName == "pushButton_add")
                preVal += num;
			else if (preBtnName == "pushButton_sub")
				preVal -= num;
			else if (preBtnName == "pushButton_mul")
				preVal *= num;
			else if (preBtnName == "pushButton_div")
				preVal /= num;
			ui.lineEdit->setText(QString::number(preVal));
        }
		else
		{
			preVal = ui.lineEdit->text().toDouble();
		}
        preOperator = button;
        ui.lineEdit->setText("0");
    }
}

void Calculator::buttonEqualClicked()
{
    if (preOperator != nullptr)
	{
		const auto& preBtnName = preOperator->objectName();
		const auto& num = ui.lineEdit->text().toDouble();
		if (preBtnName == "pushButton_add")
			preVal += num;
		else if (preBtnName == "pushButton_sub")
			preVal -= num;
		else if (preBtnName == "pushButton_mul")
			preVal *= num;
		else if (preBtnName == "pushButton_div")
			preVal /= num;
		ui.lineEdit->setText(QString::number(preVal));
		preOperator = nullptr;
	}
}

void Calculator::buttonCEClicked()
{
    ui.lineEdit->setText("0");
}

void Calculator::buttonCClicked()
{
    ui.lineEdit->setText("0");
	preVal = 0.0;
	preOperator = nullptr;
}

void Calculator::buttonDelClicked()
{
    auto text = ui.lineEdit->text();
	if (text.isEmpty())
		return;
	else
	{
		text.removeLast();
		if (text.isEmpty())
			text = "0";
		ui.lineEdit->setText(text);
		preVal = text.toDouble();
	}
}

void Calculator::buttonDotClicked()
{
	auto text = ui.lineEdit->text();
	if (text.contains('.'))
		return;
	else
	{
		text += '.';
		ui.lineEdit->setText(text);
        /*bool ok;
		text.toDouble(&ok);
        qDebug() << ok;*/
	}
}

void Calculator::buttonSignClicked()
{
    auto text = ui.lineEdit->text();
	if (text.isEmpty() || text == "0")
		return;
	else
	{
		if (text.front() == '-')
			text.removeFirst();
		else
			text.push_front('-');
		ui.lineEdit->setText(text);
	}
}