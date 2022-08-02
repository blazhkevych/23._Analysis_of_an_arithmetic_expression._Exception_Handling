#pragma once

template<class T>
class Stack
{
	int m_top; // Верхушка стека
	enum { EMPTY = -1, FULL = 1000 };
	T m_stack[FULL];
public:
	Stack();
	void Push(T); // Добавление элемента в стек
	T Pop(); // Выталкивание элемента из стека
	bool IsEmpty(); // Не пуст ли стек?
	bool IsFull(); // Не полон ли стек?
	int GetCount(); // Количество элементов в стеке
	T Get(); // Просмотр элемента в вершине стека
	// Очистка стека
	void Clear();
};

template<class T>
Stack<T>::Stack()
{
	// Изначально стек пуст
	m_top = EMPTY;
}

template<class T>
bool Stack<T>::IsEmpty()
{
	return m_top == EMPTY; //Стек пустой?
}

template<class T>
bool Stack<T>::IsFull()
{
	return m_top == FULL - 1; //Стек полный?
}

template<class T>
int Stack<T>::GetCount()
{
	return m_top + 1; //Подсчёт элементов в стеке
}

template<class T>
void Stack<T>::Push(T c)
{
	// Если в стеке есть место, то увеличиваем указатель
	// на вершину стека и вставляем новый элемент
	if (!IsFull())
		m_stack[++m_top] = c;
}

template<class T>
T Stack<T>::Pop()
{
	// Если в стеке есть элементы, то возвращаем верхний и
	// уменьшаем указатель на вершину стека
	if (!IsEmpty())
		return m_stack[m_top--];
	// Если в стеке элементов нет
	return -1;
}

template<class T>
T Stack<T>::Get()
{
	// Если в стеке есть элементы, то возвращаем верхний элемент
	if (!IsEmpty())
		return m_stack[m_top];
	// Если в стеке элементов нет
	return -1;
}

template<class T>
void Stack<T>::Clear()
{
	// Эффективная "очистка" стека 
	// (данные в массиве все еще существуют, 
	// но функции класса, ориентированные на работу с вершиной стека,
	// будут их игнорировать)
	m_top = EMPTY;
}