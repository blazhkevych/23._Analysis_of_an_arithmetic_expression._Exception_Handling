#include <cstring>
#include <iostream>
#include "Parser.h"

#include "BaseException.h"
using std::cout;
using std::endl;

void Parser::DeterminationOfPriority(char nextSymbol)
{
	const char inStack = m_symbolStack.Get(); // Символ из вершины стека символов.
	if (
		inStack == nextSymbol || // Такая же операция.

		inStack == '*' && nextSymbol == '+' || inStack == '*' && nextSymbol == '-' || // Операции меньшего приоритета нельзя ложить на операции большего приоритета.
		inStack == '/' && nextSymbol == '+' || inStack == '/' && nextSymbol == '-' ||
		inStack == '^' && nextSymbol == '+' || inStack == '^' && nextSymbol == '-' ||

		inStack == '+' && nextSymbol == '-' || inStack == '-' && nextSymbol == '+' || // Операции одинакого приоритета нельзя ложить друг на друга (+, -).

		inStack == '*' && nextSymbol == '/' || inStack == '*' && nextSymbol == '^' || // Операции одинакого приоритета нельзя ложить друг на друга (/, *, ^).
		inStack == '/' && nextSymbol == '*' || inStack == '/' && nextSymbol == '^' ||
		inStack == '^' && nextSymbol == '/' || inStack == '^' && nextSymbol == '*' ||

		inStack == '*' && nextSymbol == ')' || inStack == '-' && nextSymbol == ')' || // ")" нельзя ложить ни на что кроме "(".
		inStack == '/' && nextSymbol == ')' || inStack == '+' && nextSymbol == ')' ||
		inStack == '^' && nextSymbol == ')'
		)
	{
		m_priority = false;
	}
	else
		m_priority = true;
}

void Parser::PushOutAndAction()
{
	const char oper = m_symbolStack.Pop(); // Оператор в выражении.
	const double second_expressionEl = m_numbersStack.Pop(); // 2 элемент выражения.
	const double first_expressionEl = m_numbersStack.Pop(); // 1 элемент выражения.
	double result{ 0 };

	if (oper == '+')
		result = first_expressionEl + second_expressionEl;
	else if (oper == '-')
		result = first_expressionEl - second_expressionEl;
	else if (oper == '*')
		result = first_expressionEl * second_expressionEl;
	else if (oper == '/')
		result = first_expressionEl / second_expressionEl;
	else if (oper == '^')
		result = pow(first_expressionEl, second_expressionEl);

	m_numbersStack.Push(result);
}

void Parser::ExpressionTraversal(char* str)
{
	char s{ '\0' };
	int len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		if (
			str[i] != '0' || str[i] != '1' || str[i] != '2' ||
			str[i] != '3' || str[i] != '4' || str[i] != '5' ||
			str[i] != '6' || str[i] != '7' || str[i] != '8' ||
			str[i] != '9' ||
			str[i] != '-' || str[i] != '*' || str[i] != '/' ||
			str[i] != '^' || str[i] != '+'
			)
		{
			throw InvalidCharacterInExpression("Недопустимый символ в выражении"); // Сгенерировать исключение типа InvalidCharacterInExpression.
		} // TODO: попробовать добавить в параметры str[i]
		switch (str[i])
		{
		case '(':
			m_symbolStack.Push(str[i]);
			break;
		case ')':
			DeterminationOfPriority(str[i]);
			if (m_priority == true)
			{
				m_symbolStack.Push(str[i]);
			}
			else
			{
				while (m_priority == false) // Пока m_priority выталкиваем выражения и проводим операции
				{
					// Выталкивание чисел и обработка выражения, закидка результатата в стек.
					PushOutAndAction();
					DeterminationOfPriority(str[i]); // и проверяем можем ли сделать вставку.
					if (m_priority == true) // При "(" и ")" ничего не ложим в стек,
						m_symbolStack.Pop(); // а вытягиваем из стека "(".
				}
			}
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			m_numbersStack.Push(CharToDouble(str, i));
			break;
		case '+':
			DeterminationOfPriority(str[i]);
			if (m_priority == true)
			{
				m_symbolStack.Push(str[i]);
			}
			else
			{
				while (m_priority == false) // Пока m_priority выталкиваем выражения и проводим операции
				{
					// Выталкивание чисел и обработка выражения, закидка результатата в стек.
					PushOutAndAction();
					DeterminationOfPriority(str[i]); // и проверяем можем ли сделать вставку.
					if (m_priority == true)
						m_symbolStack.Push(str[i]);
				}
			}
			break;
		case '-':
			DeterminationOfPriority(str[i]);
			if (m_priority == true)
			{
				m_symbolStack.Push(str[i]);
			}
			else
			{
				while (m_priority == false) // Пока m_priority выталкиваем выражения и проводим операции
				{
					// Выталкивание чисел и обработка выражения, закидка результатата в стек.
					PushOutAndAction();
					DeterminationOfPriority(str[i]); // и проверяем можем ли сделать вставку.
					if (m_priority == true)
						m_symbolStack.Push(str[i]);
				}
			}
			break;
		case '*':
			DeterminationOfPriority(str[i]);
			if (m_priority == true)
			{
				m_symbolStack.Push(str[i]);
			}
			else
			{
				while (m_priority == false) // Пока m_priority выталкиваем выражения и проводим операции
				{
					// Выталкивание чисел и обработка выражения, закидка результатата в стек.
					PushOutAndAction();
					DeterminationOfPriority(str[i]); // и проверяем можем ли сделать вставку.
					if (m_priority == true)
						m_symbolStack.Push(str[i]);
				}
			}
			break;
		case '/':
			DeterminationOfPriority(str[i]);
			if (m_priority == true)
			{
				m_symbolStack.Push(str[i]);
			}
			else
			{
				while (m_priority == false) // Пока m_priority выталкиваем выражения и проводим операции
				{
					// Выталкивание чисел и обработка выражения, закидка результатата в стек
					PushOutAndAction();
					DeterminationOfPriority(str[i]); // и проверяем можем ли сделать вставку.
					if (m_priority == true)
						m_symbolStack.Push(str[i]);
				}
			}
			break;
		case '^':
			DeterminationOfPriority(str[i]);
			if (m_priority == true)
			{
				m_symbolStack.Push(str[i]);
			}
			else
			{
				while (m_priority == false) // Пока m_priority выталкиваем выражения и проводим операции
				{
					// Выталкивание чисел и обработка выражения, закидка результатата в стек
					PushOutAndAction();
					DeterminationOfPriority(str[i]); // и проверяем можем ли сделать вставку.
					if (m_priority == true)
						m_symbolStack.Push(str[i]);
				}
			}
			break;
		}
	}
	const double finalResult = m_numbersStack.Pop();
	cout << endl << "Результат выражения: " << finalResult << endl;
}

double Parser::CharToDouble(char* str, int& position) const
{
	char number[20]{ '\0' };
	strncpy_s(number, 20, str + position, 1);
	position++;
	while (str[position] >= '0' && str[position] <= '9' || str[position] == '.')
	{
		strncat_s(number, 20, str + position, 1);
		position++;
	}
	double res = atof(number); // результат выходит 5.1100000000000003, возможно нужно обрезать лишнее.
	position--;
	return res;
}