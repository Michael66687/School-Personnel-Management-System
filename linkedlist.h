#pragma once
template<class T>
struct node
{
	T data;
	node<T>* next;
};

//基于模板的链表类声明
template<class T>
class linkedlist
{
private:
	node<T>* head;
	node<T>* current;
	//内联函数，用于深拷贝
	inline void deepCopy(const linkedlist<T>& original);
public:
	linkedlist();
	linkedlist(const linkedlist<T>& aplist);
	virtual ~linkedlist();

	void insert(node<T>* newNode);//在头部插入
	void insert_end(node<T>* newNode);//在尾部插入
	node<T>* getFirst();//获得链表头的数据
	inline node<T>* getNext();//获得当前节点的下一个数据
	bool find(const T& element);//查找一个数据
	bool retrieve(T& element);//检索一个数据
	bool replace(const T& newElement);//替换数据
	bool remove(node<T>* node);//移除一个数据
	bool isEmpty()const;
	void makeEmpty();
	int size();
	linkedlist<T>& operator=(const linkedlist<T>& rlist);
};

//定义部分
#include<iostream>

template<class T>
linkedlist<T>::linkedlist()
{
	head = current = NULL;
}

//复制构造函数
template<class T>
linkedlist<T>::linkedlist(const linkedlist<T>& aplist)
{
	deepCopy(aplist);
}

//析构函数
template<class T>
linkedlist<T>::~linkedlist()
{
	makeEmpty();
}

//插入函数
template<class T>
void linkedlist<T>::insert(node<T>* newNode)
{
	current = NULL;
	newNode->next = head;
	head = newNode;
}
template<class T>
void linkedlist<T>::insert_end(node<T>* newNode)
{
	current = NULL;
	node<T>* tail = head;
	newNode->next = NULL;
	if (tail == NULL)
	{
		head = newNode;
	}
	else
	{
		while (tail->next != NULL)
			tail = tail->next;
		tail->next = newNode;
	}
}

//获得链表头的函数
template<class T>
node<T>* linkedlist<T>::getFirst()
{
	if (head == NULL)
	{
		return NULL;
	}
	current = head;
	return head;
}

//获得下一个数据
template<class T>
node<T>* linkedlist<T>::getNext()
{
	if (current == NULL)
	{
		return NULL;
	}
	if (current->next == NULL)
	{
		current = NULL;
		return NULL;
	}
	current = current->next;
	return current;
}

//查找一个数据
template<class T>
bool linkedlist<T>::find(const T& element)
{
	node<T>* n;
	n = getFirst();
	if (n == NULL)
	{
		return false;
	}
	do
	{
		if (n->data == element)
		{
			return true;
		}
		n = getNext();
	} while (n != NULL);
	return false;
}

//检索一个数据
template<class T>
bool linkedlist<T>::retrieve(T& element)
{
	if (!find(element))
	{
		return false;
	}
	element = current->data;
	return true;
}

//替换一个数据
template<class T>
bool linkedlist<T>::replace(const T& newElement)
{
	if (current == NULL)
	{
		return false;
	}
	current->data = newElement;
	return true;
}

//移除一个数据
template<class T>
bool linkedlist<T>::remove(node<T>* n)
{
	current = NULL;
	if (head == NULL)
	{
		return false;
	}
	node<T>* tmp = head;
	if (head == n)
	{
		head = tmp->next;
		delete tmp;
		return true;
	}
	while (tmp->next != NULL)
	{
		if (tmp->next == n)
		{
			node<T>* ptr = tmp->next;
			tmp->next = ptr->next;
			delete ptr;
			return true;
		}
		tmp = tmp->next;
	}
	return false;
}

//判断是否为空
template<class T>
bool linkedlist<T>::isEmpty()const
{
	return head == NULL;
}

//将链表清空
template<class T>
void linkedlist<T>::makeEmpty()
{
	while (head != NULL)
	{
		current = head;
		head = head->next;
		delete current;
	}
	current = NULL;
}

//获得链表大小
template<class T>
int linkedlist<T>::size()
{
	int size = 0;
	node<T>* tmp = head;
	while (tmp != NULL)
	{
		size++;
		tmp = tmp->next;
	}
	return size;
}

//"="运算符重载
template<class T>
linkedlist<T>& linkedlist<T>::operator=(const linkedlist<T>& rlist)
{
	if (this == &rlist)
	{
		return *this;
	}
	makeEmpty();
	deepCopy(rlist);
	return *this;
}

//深拷贝函数
template<class T>
void linkedlist<T>::deepCopy(const linkedlist<T>& original)
{
	head = current = NULL;
	if (original.head == NULL)
	{
		return;
	}
	node<T>* copy = head = new node<T>;
	node<T>* origin = original.head;
	copy->data = origin->data;
	if (origin == original.current)
	{
		current = copy;
	}
	while (origin->next != NULL)
	{
		copy->next = new node<T>;
		origin = origin->next;
		copy = copy->next;
		copy->data = origin->data;
		if (origin == original.current)
		{
			current = copy;
		}
	}
	copy->next = NULL;
}