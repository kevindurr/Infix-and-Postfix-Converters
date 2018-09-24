//Kevin Durr

template<typename T>
Stack<T>::Stack()
{
}

template<typename T>
Stack<T>::~Stack()
{
	clear();
}

template<typename T>
Stack<T>::Stack(const Stack<T>& rhs)
{
	theArray = rhs.theArray;
}

template<typename T>
Stack<T>::Stack(Stack<T> && rhs)
{
	theArray = std::move(rhs.theArray);
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& rhs)
{
	auto copy = rhs;
	std::swap(*this, copy);
	return *this;
}
template<typename T>
Stack<T>& Stack<T>::operator=( Stack<T>&& rhs)
{
	theArray = std::move(rhs.theArray);
	return *this;
}
template<typename T>
bool Stack<T>::empty() const
{
	return (theArray.empty());

}
template<typename T>
void Stack<T>::clear()
{
	theArray.clear();
}
template<typename T>
void Stack<T>::push(const T& x)
{
	theArray.push_back(x);
}
template<typename T>
void Stack<T>::push(T && x)
{
	theArray.push_back(std::move(x));
}
template<typename T>
void Stack<T>::pop()
{
	if (size() != 0)
	{
		theArray.pop_back();
	}
}
template<typename T>
T& Stack<T>::top()
{
	return theArray.back();
}

template<typename T>
const T& Stack<T>::top() const
{
	return theArray.back();
}

template<typename T>
int Stack<T>::size() const
{
	return theArray.size();
}
template<typename T>
void Stack<T>::print(std::ostream& os, char ofc) const
{
	for (int i = 0; i < size(); i++)
		os << theArray[i] << ofc;
}
template<typename T>
std::ostream& operator<< (std::ostream& os, const Stack<T>& a)
{
	a.print(os);
	return os;
}

template<typename T>
bool operator== (const Stack<T>& s1, const Stack <T>& s2)
{
	if (s1.size() != s2.size())
		return false;
	else
	{
		Stack<T> temp1 = std::move(s1);
		Stack<T> temp2 = std::move(s2);
		
		for(int i = 0; i < temp1.size(); i++)
		{
			if (temp1.top() > temp2.top())
				return false;
			temp1.pop();
			temp2.pop();
		}
	}
	return true;
}

template<typename T>
bool operator!= (const Stack<T>& s1, const Stack <T>& s2)
{
	return !(s1 == s2);
}
template<typename T>
bool operator<= (const Stack<T>& a, const Stack <T>& b)
{

	if (a.size() > b.size())
		return false;
	else
	{
		Stack<T> temp1(a);
		Stack<T> temp2(b);
		while (!temp1.empty())
		{
			if (temp1.top() <= temp2.top())
			{
				temp1.pop();
				temp2.pop();
			}
			else
				return false;
		}
	
	}
	return true;
}