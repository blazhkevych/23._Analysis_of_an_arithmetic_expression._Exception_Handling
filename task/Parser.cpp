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

#pragma region Проверка на корректность символов в строке.

	for (int i = 0; i < len; i++) // Проверка на корректность символов в строке.
	{
		// 1. Недопустимый символ в выражении. // OK
		if (
			str[i] != '0' && str[i] != '1' && str[i] != '2' &&
			str[i] != '3' && str[i] != '4' && str[i] != '5' &&
			str[i] != '6' && str[i] != '7' && str[i] != '8' &&
			str[i] != '9' &&
			str[i] != '-' && str[i] != '*' && str[i] != '/' &&
			str[i] != '^' && str[i] != '+' &&
			str[i] != '(' && str[i] != ')' &&
			str[i] != '.'
			)
		{
			throw new InvalidCharacterInExpression("\n\n1. Недопустимый символ в выражении !\n\n"); // TODO: попробовать добавить в параметры str[i] 
		}

		// 2. В выражении подряд идут два знака операции. // OK
		// (5.11++2.22^3.33-(4.44-(2.22+3.33)*2.22)-1.11)
		if (
			str[i] == '-' && str[i + 1] == '-' ||
			str[i] == '+' && str[i + 1] == '+' ||
			str[i] == '*' && str[i + 1] == '*' ||
			str[i] == '/' && str[i + 1] == '/' ||
			str[i] == '^' && str[i + 1] == '^'
			)
		{
			throw new TwoIdenticalOperationSignsInRow("\n\n2. В выражении подряд идут два знака операции !\n\n");
		}

		// 3. В выражении подряд идут две десятичные точки. // OK
		// (5.11+2..22^3.33-(4.44-(2.22+3.33)*2.22)-1.11)
		if (str[i] == '.' && str[i + 1] == '.')
		{
			throw new TwoDecimalPointsInRow("\n\n3. В выражении подряд идут две десятичные точки !\n\n");
		}

		// 4. Между числом и открывающей скобкой отсутствует знак операции. // OK
		// (5.11+2.22^3.33(4.44-(2.22+3.33)*2.22)-1.11)
		if (str[i] >= '0' && str[i] <= '9' && str[i + 1] == '(') // Если число, заходим.
		{
			{
				throw new NoOperationSignBetweenNumberNndOpeningBracket("\n\n4. Между числом и открывающей скобкой отсутствует знак операции !\n\n");
			}

			//bool operationSign_0{ false }; // Знак операции встретился на пути к открывающей скобке ?, если да - true.
			//for (int j = i + 1; j < len; j++) // Бежим от следующего знака, после str[i].
			//{
			//	if (
			//		str[j] == '-' || str[j] == '+' ||
			//		str[j] == '*' || str[j] == '/' ||
			//		str[j] == '^'
			//		)
			//		operationSign_0 = true; // Если на пути встретили знак операции.
			//	if (str[j] == '(' && operationSign_0 == false) // Если дошли до '(', но не встретили знак операции.
			//	{
			//		throw new NoOperationSignBetweenNumberNndOpeningBracket("\n\nМежду числом и открывающей скобкой отсутствует знак операции !\n\n");
			//	}
			//}
		}

		// 5. Между закрывающей скобкой и числом отсутствует знак бинарной операции. // OK
		// (5.11+2.22^3.33-(4.44-(2.22+3.33)2.22)-1.11)
		if (str[i] == ')' && str[i + 1] >= '0' && str[i + 1] <= '9')
		{
			{
				throw new NoBinaryOperationBetweenClosingBracketAndNumber("\n\n5. Между закрывающей скобкой и числом отсутствует знак бинарной операции !\n\n");
			}

			//bool operationSign_1{ false }; // Знак бинарной операции встретился на пути к числу ?, если да - true.
			//for (int j = i + 1; j < len; j++) // Бежим от следующего знака, после str[i].
			//{
			//	if (
			//		str[j] == '-' || str[j] == '+' ||
			//		str[j] == '*' || str[j] == '/' ||
			//		str[j] == '^'
			//		)
			//		operationSign_1 = true; // Если на пути встретили знак бинарной операции.
			//	if (str[j] >= '0' && str[j] <= '9' && operationSign_1 == false) // Если дошли до числа, но не встретили знак операции.
			//	{
			//		throw new NoBinaryOperationBetweenClosingBracketAndNumber("\n\nМежду закрывающей скобкой и числом отсутствует знак бинарной операции !\n\n");
			//	}
			//}
		}

		// 6. Между открывающей и закрывающей скобкой отсутствует выражение. // OK
		// (5.11+2.22^3.33-(4.44-(2.22+3.33)*2.22)-1.11)
		if (i != 0 && str[i] == '(')
		{
			bool inNumber{ false }; // Находимся в числе.
			int numbers{ 0 }; // Подсчет чисел в выражении.
			for (int j = i + 1; j < len || str[j] != ')'; j++)
			{
				while (str[j] >= '0' && str[j] <= '9' && str[j] == '.')
				{
					j++;
					if (str[j] <= '0' && str[j] >= '9' && str[j] != '.')
						inNumber = true;
					else
					{
						inNumber = false;
						numbers++;
						if (numbers == 2)
							break;
					}

				}
			}
		}

		/*{
			throw new NoExpressionBetweenOpeningAndClosingBrace("\n\n6. Между открывающей и закрывающей скобкой отсутствует выражение !\n\n");
		}*/

		// 7. Между открывающей скобкой и знаком бинарной операции отсутствует выражение. // ?
		// NoExpressionBetweenOpeningBracketAndSignBinaryOperation
		// (+2.22^3.33-(4.44-(2.22+3.33)*2.22)-1.11)
		if (
			str[i] == '(' && str[i + 1] == '-' ||
			str[i] == '(' && str[i + 1] == '+' ||
			str[i] == '(' && str[i + 1] == '*' ||
			str[i] == '(' && str[i + 1] == '/' ||
			str[i] == '(' && str[i + 1] == '^'
			) // Если '(', заходим.
		{
			throw new NoExpressionBetweenOpeningBracketAndSignBinaryOperation("\n\n7. Между открывающей скобкой и знаком бинарной операции отсутствует выражение !\n\n");
		}

		// 8. Между знаком бинарной операции и закрывающей скобкой отсутствует выражение. // OK
		// NoExpressionBetweenBinaryOperationAndClosingBracket.
		// (5.11+2.22^3.33-(4.44-(2.22+)*2.22)-1.11)
		if (
			str[i] == '-' && str[i + 1] == ')' ||
			str[i] == '+' && str[i + 1] == ')' ||
			str[i] == '*' && str[i + 1] == ')' ||
			str[i] == '/' && str[i + 1] == ')' ||
			str[i] == '^' && str[i + 1] == ')'
			) // Если знак бинарной операции, заходим.
		{
			throw new NoExpressionBetweenBinaryOperationAndClosingBracket("\n\n8. Между знаком бинарной операции и закрывающей скобкой отсутствует выражение !\n\n");
		}

		// 9. Между закрывающей и открывающей скобкой отсутствует знак бинарной операции. // ?
		// NoBinaryOperationBetweenClosingAndOpeningBrace.
		// (5.11+2.22^3.33-(4.44-2.22)(3.33*2.22)-1.11)
		if (str[i] == ')' && str[i + 1] == '(') // Если ')', заходим.
		{
			throw new NoBinaryOperationBetweenClosingAndOpeningBrace("\n\n9. Между закрывающей и открывающей скобкой отсутствует знак бинарной операции !\n\n");
		}

		// 10. Выражение начинается со знака бинарной операции.
		// ExpressionStartsWithBinaryOperation
		// (+5.11+2.22^3.33-(4.44-(2.22+3.33)*2.22)-1.11)
		if (
			str[0] == '(' && str[1] == '+' ||
			str[0] == '(' && str[1] == '-' ||
			str[0] == '(' && str[1] == '*' ||
			str[0] == '(' && str[1] == '/' ||
			str[0] == '(' && str[1] == '^'
			) // Если ')', заходим.
		{
			throw new ExpressionStartsWithBinaryOperation("\n\n10. Выражение начинается со знака бинарной операции !\n\n");
		}



		// Выражение начинается с закрывающей скобки.								  // The expression starts with a closing brace.
		// Выражение заканчивается знаком бинарной операции.						  // The expression ends with a binary operation sign.
		// Некорректная запись десятичной дроби.									  // Incorrect decimal notation.
		// Несоответствие между количеством открывающих и закрывающих скобок.		  // Mismatch between the number of opening and closing brackets.


	}

#pragma endregion

	for (int i = 0; i < len; i++)
	{
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