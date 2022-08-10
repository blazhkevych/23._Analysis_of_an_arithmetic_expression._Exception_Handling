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
	virtual ~BaseException() = default;

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

class TwoIdenticalOperationSignsInRow :public BaseException
{
public:
	TwoIdenticalOperationSignsInRow(const char* msg) : BaseException(msg) {}
};

class TwoDecimalPointsInRow :public BaseException
{
public:
	TwoDecimalPointsInRow(const char* msg) : BaseException(msg) {}
};

class NoOperationSignBetweenNumberNndOpeningBracket :public BaseException
{
public:
	NoOperationSignBetweenNumberNndOpeningBracket(const char* msg) : BaseException(msg) {}
};

class NoBinaryOperationBetweenClosingBracketAndNumber :public BaseException
{
public:
	NoBinaryOperationBetweenClosingBracketAndNumber(const char* msg) : BaseException(msg) {}
};

class NoExpressionBetweenOpeningAndClosingBrace :public BaseException
{
public:
	NoExpressionBetweenOpeningAndClosingBrace(const char* msg) : BaseException(msg) {}
};

class NoExpressionBetweenOpeningBracketAndSignBinaryOperation :public BaseException
{
public:
	NoExpressionBetweenOpeningBracketAndSignBinaryOperation(const char* msg) : BaseException(msg) {}
};

class NoExpressionBetweenBinaryOperationAndClosingBracket :public BaseException
{
public:
	NoExpressionBetweenBinaryOperationAndClosingBracket(const char* msg) : BaseException(msg) {}
};

class NoBinaryOperationBetweenClosingAndOpeningBrace :public BaseException
{
public:
	NoBinaryOperationBetweenClosingAndOpeningBrace(const char* msg) : BaseException(msg) {}
};




/*
// Между открывающей скобкой и знаком бинарной операции отсутствует выражение.// There is no expression between the opening bracket and the sign of the binary operation.
// Между знаком бинарной операции и закрывающей скобкой отсутствует выражение.// There is no expression between the binary operation sign and the closing bracket.
// Между закрывающей и открывающей скобкой отсутствует знак бинарной операции.// There is no sign of a binary operation between the closing and opening brace.
// Выражение начинается со знака бинарной операции.							  // The expression starts with the sign of the binary operation.
// Выражение начинается с закрывающей скобки.								  // The expression starts with a closing brace.
// Выражение заканчивается знаком бинарной операции.						  // The expression ends with a binary operation sign.
// Некорректная запись десятичной дроби.									  // Incorrect decimal notation.
// Несоответствие между количеством открывающих и закрывающих скобок.		  // Mismatch between the number of opening and closing brackets.
 */