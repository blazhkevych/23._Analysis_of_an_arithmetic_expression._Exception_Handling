﻿/*
############################################ ЗАДАНИЕ ###########################################
				Разбор арифметического выражения.
					Обработка исключений.
	Модифицировать проект «Разбор арифметического выражения»
следующим образом. Используя механизм исключений, предусмотреть
корректную обработку возможных ошибок при вводе выражения и
информирование о них пользователя. Для этого необходимо разработать
иерархию классов, отвечающих за обработку исключительных ситуаций.
	Во главе иерархии должен находиться абстрактный базовый класс.
Каждый производный класс должен отвечать за обработку определенной
ошибки. В клиентской части программы необходимо применить
полиморфизм при обработке исключений.

* Недопустимый символ в выражении.
* В выражении подряд идут два знака операции.
* В выражении подряд идут две десятичные точки.
* Между числом и открывающей скобкой отсутствует знак операции.
* Между закрывающей скобкой и числом отсутствует знак бинарной операции.
* Между открывающей и закрывающей скобкой отсутствует выражение.
* Между открывающей скобкой и знаком бинарной операции отсутствует выражение.
* Между знаком бинарной операции и закрывающей скобкой отсутствует выражение.
* Между закрывающей и открывающей скобкой отсутствует знак бинарной операции.
* Выражение начинается со знака бинарной операции.
* Выражение начинается с закрывающей скобки.
* Выражение заканчивается знаком бинарной операции.
* Некорректная запись десятичной дроби.
* Несоответствие между количеством открывающих и закрывающих скобок.
################################################################################################
02.47.15
*/

#include <iostream>
#include <windows.h>

#include "BaseException.h"
#include "Parser.h"

using namespace std;

int main()
{
	SetConsoleCP(1251);
	/*
	Задает кодовую страницу ввода, используемую консолью, связанной с вызывающим процессом.
	Консоль использует страницу входного кода для преобразования ввода с клавиатуры
	в соответствующее символьное значение.
	*/
	SetConsoleOutputCP(1251);
	/*
	Задает выходную кодовую страницу, используемую консолью, связанной с вызывающим процессом.
	Консоль использует свою кодовую страницу вывода для преобразования символьных значений,
	записанных различными функциями вывода, в изображения, отображаемые в окне консоли.
	*/

	char str[200];
	cout << "Введите выражение: ";

	cin.getline(str, 200);

	Parser parser;
	try
	{
		parser.ExpressionTraversal(str);
	}
	catch (BaseException* exception)
	{
		cout << exception->GetMSG();
	}

	/*
	 (5+2^3-(4-(2+3)*2)-1)
	 // 37 symbols without nullterminator
	 (5.11+2.22^3.33-(4.44-(2.22+3.33)*2.22)-1.11)
	*/

	return 0;
}