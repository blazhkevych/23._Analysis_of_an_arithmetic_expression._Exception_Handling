#pragma once
#include<iostream>
using std::string;

// Создание иерархии классов, обрабатывающих исключения
// абстрактный базовый класс, создать объект класса невозможно.
class BaseException abstract
{
protected:
	char m_msg[100];
public:
	BaseException(const char* msg)
	{
		strcpy_s(m_msg, msg);
	}
	virtual char* GetMSG() { return m_msg; }
};

class InvalidCharacterInExpression :public BaseException
{
public:
	InvalidCharacterInExpression(const char* msg) : BaseException(msg) {}
};

/*
// Недопустимый символ в выражении.											  // Invalid character in expression.
// В выражении подряд идут два знака операции.								  // In the expression, there are two signs of the operation in a row.
// В выражении подряд идут две десятичные точки.							  // Expression has two decimal points in a row.
// Между числом и открывающей скобкой отсутствует знак операции.			  // There is no operation sign between the number and the opening bracket.
// Между закрывающей скобкой и числом отсутствует знак бинарной операции.	  // There is no binary operation sign between the closing bracket and the number.
// Между открывающей и закрывающей скобкой отсутствует выражение.			  // There is no expression between the opening and closing brace.
// Между открывающей скобкой и знаком бинарной операции отсутствует выражение.// There is no expression between the opening bracket and the sign of the binary operation.
// Между знаком бинарной операции и закрывающей скобкой отсутствует выражение.// There is no expression between the binary operation sign and the closing bracket.
// Между закрывающей и открывающей скобкой отсутствует знак бинарной операции.// There is no sign of a binary operation between the closing and opening brace.
// Выражение начинается со знака бинарной операции.							  // The expression starts with the sign of the binary operation.
// Выражение начинается с закрывающей скобки.								  // The expression starts with a closing brace.
// Выражение заканчивается знаком бинарной операции.						  // The expression ends with a binary operation sign.
// Некорректная запись десятичной дроби.									  // Incorrect decimal notation.
// Несоответствие между количеством открывающих и закрывающих скобок.		  // Mismatch between the number of opening and closing brackets.
 */