#pragma once
#include "stack.h"

class Parser
{
	Stack<char> m_symbolStack; // Стек для операций и скобок.
	Stack<double> m_numbersStack; // Стек для чисел.
	// Отображает можем ли мы ложить в m_symbolStack следующий символ.
	bool m_priority{ false };
	// Вычисляет можем ли мы ложить в m_symbolStack следующий символ.
	void DeterminationOfPriority(char nextSymbol);
	// Выталкивает 2 числа из m_numbersStack, производит действие и ложит результат в m_numbersStack.
	void PushOutAndAction();
	// Преобразует чар в дабл.
	double CharToDouble(char* str, int& position) const;
public:
	// Обход выражения.
	void ExpressionTraversal(char* str);
};