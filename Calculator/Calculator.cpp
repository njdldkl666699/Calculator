#include "Calculator.h"
#include<QDialog>
#include<QStack>

Calculator::Calculator(QWidget* parent)
	: QMainWindow(parent), effect(new QSoundEffect(this)), expression(""), val("0")
{
	ui.setupUi(this);
	this->setWindowIcon(QIcon(":/res/Icon.png"));
	effect->setSource(QUrl::fromLocalFile(":/res/sound.wav"));
	connect(ui.buttonNumGroup, &QButtonGroup::buttonClicked, this, &Calculator::buttonNumClicked);
	connect(ui.buttonOperatorGroup, &QButtonGroup::buttonClicked, this, &Calculator::buttonOperatorClicked);
	connect(ui.pushButton_equal, &QPushButton::clicked, this, &Calculator::buttonEqualClicked);
	connect(ui.pushButton_bracket, &QPushButton::clicked, this, &Calculator::buttonBracketClicked);
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
	const auto& buttonName = button->objectName();
	if (buttonName.isEmpty())
		return;
	else
	{
		QString num = buttonName.back();
		if (val.isEmpty() || val == "0")
			val = num;
		else
			val += num;
		ui.lineEdit->setText(val);
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
		QChar op = '\0';
		if (buttonName == "pushButton_add")
			op = '+';
		else if (buttonName == "pushButton_sub")
			op = '-';
		else if (buttonName == "pushButton_mul")
			op = '*';
		else if (buttonName == "pushButton_div")
			op = '/';
		if(val!="0")
			expression += val;
		expression += op;
		val = '0';
		ui.lineEdit->setText(val);
		ui.lineEdit_pre->setText(expression);
	}
}

static bool isOperator(QString c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

static bool isBracket(QChar c)
{
	return c == '(' || c == ')';
}

static bool isPriorityHigher(QChar c1, QChar c2)
{
	if (c1 == '*' || c1 == '/')
		return true;
	else if (c1 == '+' || c1 == '-')
	{
		if (c2 == '*' || c2 == '/')
			return false;
		else
			return true;
	}
	else
		return false;
}

void Calculator::buttonEqualClicked()
{
	effect->play();
	if(val!="0")
		expression += val;
	qDebug() << expression;

	//转为后缀表达式
	QStack<QString>stack2;
	QStack<QChar>stack1;
	QString tmp;
	for (QString::const_iterator it = expression.begin(); it != expression.end(); it++)
	{
		if (*it == '-' && (it == expression.begin() ||
			(*(it - 1) == '(' || isOperator(*(it - 1)))))//符号位
		{
			tmp += *it;
		}
		else if (it->isDigit() || *it == '.')//数字和小数点
		{
			tmp += *it;
		}
		else if (isOperator(*it))
		{
			if (!tmp.isEmpty())
			{
				stack2.push(tmp);
				tmp.clear();
			}
			while (true)
			{
				if (stack1.isEmpty() || stack1.top() == '(' || isPriorityHigher(*it, stack1.top()))
				{
					stack1.push(*it);
					break;
				}
				else
				{
					stack2.push(stack1.pop());
				}
			}
		}
		else if (*it == '(')
		{
			if (!tmp.isEmpty())
			{
				stack2.push(tmp);
				tmp.clear();
			}
			stack1.push(*it);
		}
		else if (*it == ')')
		{
			if (!tmp.isEmpty())
			{
				stack2.push(tmp);
				tmp.clear();
			}
			while (stack1.top() != '(')
			{
				stack2.push(stack1.pop());
			}
			stack1.pop();
		}
	}
	if (!tmp.isEmpty())
		stack2.push(tmp);
	while (!stack1.isEmpty())
	{
		stack2.push(stack1.pop());
	}

	//Debug
	for(const auto& s : stack2)
	{
		qDebug() << s;
	}

	//计算后缀表达式
	QStack<QString> stack3;
	for (const auto& s : stack2)
	{
		if (isOperator(s))
		{
			double num2 = stack3.pop().toDouble();
			double num1 = stack3.pop().toDouble();
			double result = 0;
			if (s == "+")
				result = num1 + num2;
			else if (s == "-")
				result = num1 - num2;
			else if (s == "*")
				result = num1 * num2;
			else if (s == "/")
				result = num1 / num2;
			stack3.push(QString::number(result));
		}
		else
		{
			stack3.push(s);
		}
	}
	val= stack3.pop();
	ui.lineEdit->setText(val);
	ui.lineEdit_pre->setText(expression + '=');
	expression.clear();
}

void Calculator::buttonBracketClicked()
{
	static bool hasLeftBracket = false;
	effect->play();
	if (hasLeftBracket)
	{
		if(val!="0")
			expression += val;
		expression += ')';
		val = '0';
		ui.lineEdit->setText(val);
		hasLeftBracket = false;
	}
	else
	{
		expression += '(';
		hasLeftBracket = true;
	}
	ui.lineEdit_pre->setText(expression);
}

void Calculator::buttonCClicked()
{
	effect->play();
	ui.lineEdit->setText("0");
	ui.lineEdit_pre->clear();
	expression.clear();
	val = '0';
}

void Calculator::buttonDelClicked()
{
	effect->play();
	if(val.isEmpty())
		return;
	else
	{
		val.removeLast();
		if (val.isEmpty())
			ui.lineEdit->setText("0");
		else
			ui.lineEdit->setText(val);
	}
}

void Calculator::buttonDotClicked()
{
	effect->play();
	if(val.isEmpty())
		val = "0.";
	else
		val += ".";
	ui.lineEdit->setText(val);
}

void Calculator::buttonSignClicked()
{
	effect->play();
	if(val.isEmpty())
		return;
	else
	{
		if (val.front() == '-')
			val.removeFirst();
		else
			val.push_front('-');
		ui.lineEdit->setText(val);
	}
}