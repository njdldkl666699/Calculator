#include "Calculator.h"

Calculator::Calculator(QWidget* parent)
	: QMainWindow(parent), preVal(0.0), isRlt(false),
	effect(new QSoundEffect(this)), preOperator(nullptr)
{
	ui.setupUi(this);
	this->setWindowIcon(QIcon(":/res/Icon.png"));
	effect->setSource(QUrl::fromLocalFile(":/res/sound.wav"));
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
{
}

void Calculator::buttonNumClicked(QAbstractButton* button)
{
	effect->play();
	if (isRlt)
		ui.lineEdit->clear();

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
		isRlt = false;
	}
}

void Calculator::buttonOperatorClicked(QAbstractButton* button)
{
	effect->play();
	const auto& buttonName = button->objectName();
	if (buttonName.isEmpty())
		return;
	else
	{
		const auto& num = ui.lineEdit->text().toDouble();
		if (preOperator != nullptr)
		{
			const auto& preBtnName = preOperator->objectName();
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

		QChar op = '\0';
		if (buttonName == "pushButton_add")
			op = '+';
		else if (buttonName == "pushButton_sub")
			op = '-';
		else if (buttonName == "pushButton_mul")
			op = '*';
		else if (buttonName == "pushButton_div")
			op = '/';
		ui.lineEdit_pre->setText(QString::number(preVal) + op);
		preOperator = button;
		//ui.lineEdit->setText("0");
		isRlt = true;
	}
}

void Calculator::buttonEqualClicked()
{
	effect->play();
	if (preOperator != nullptr)
	{
		const auto& preBtnName = preOperator->objectName();
		const auto& num = ui.lineEdit->text().toDouble();
		const double preVal_bef = preVal;
		QChar op = '\0';
		if (preBtnName == "pushButton_add")
		{
			preVal += num;
			op = '+';
		}
		else if (preBtnName == "pushButton_sub")
		{
			preVal -= num;
			op = '-';
		}
		else if (preBtnName == "pushButton_mul")
		{
			preVal *= num;
			op = '*';
		}
		else if (preBtnName == "pushButton_div")
		{
			preVal /= num;
			op = '/';
		}
		ui.lineEdit->setText(QString::number(preVal));
		ui.lineEdit_pre->setText(QString::number(preVal_bef) + ' ' + op + ' ' + QString::number(num) + " =");
		preOperator = nullptr;
	}
	else
	{
		ui.lineEdit_pre->setText(ui.lineEdit->text() + '=');
	}
	isRlt = true;
}

void Calculator::buttonCEClicked()
{
	effect->play();
	ui.lineEdit->setText("0");
	isRlt = false;
}

void Calculator::buttonCClicked()
{
	effect->play();
	ui.lineEdit->setText("0");
	ui.lineEdit_pre->clear();
	preVal = 0.0;
	preOperator = nullptr;
	isRlt = false;
}

void Calculator::buttonDelClicked()
{
	effect->play();
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
		isRlt = false;
	}
}

void Calculator::buttonDotClicked()
{
	effect->play();
	auto text = ui.lineEdit->text();
	if (text.contains('.'))
		return;
	else
	{
		text += '.';
		ui.lineEdit->setText(text);
		isRlt = false;
	}
}

void Calculator::buttonSignClicked()
{
	effect->play();
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