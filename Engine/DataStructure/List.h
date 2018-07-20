#pragma once

namespace Engine {

	template<typename T>
	struct Node
	{
		Node()
		{
			this->data = new T();
			next = nullptr;
			prev = nullptr;
		}

		Node(T* data)
		{
			this->data = data;
			next = nullptr;
			prev = nullptr;
		}

		T* data;
		Node<T>* next;
		Node<T>* prev;

	};

	template<typename T>
	class List
	{
	private:

	public:

		Node<T>* ptr;
		Node<T>* headNode;
		Node<T>* tailNode;
		int length;

		List<T>();
		~List<T>();
		void Add(T* t);
		void Delete(Node<T>* & ptr);

	};

	template<typename T>
	List<T>::List()
	{
		length = 0;
		ptr = nullptr;
		headNode = nullptr;
		tailNode = nullptr;
	}

	template<typename T>
	List<T>::~List()
	{

	}

	template<typename T>
	void List<T>::Add(T* t)
	{

		Node<T>* temp = new Node<T>(t);

		if (length == 0)
		{
			headNode = temp;
			tailNode = temp;
		}
		else
		{
			tailNode->next = temp;
			temp->prev = tailNode;
			tailNode = temp;
		}

		length++;

	}

	template<typename T>
	void List<T>::Delete(Node<T>* & ptr)
	{
		Node<T>* temp = new Node<T>();
		temp = ptr;
		if (length == 0)
		{
			printf("NO ENEMY\n");
		}
		else if (length == 1)
		{
			length = 0;
			ptr = nullptr;
			headNode = nullptr;
			tailNode = nullptr;
		}
		else if (ptr->prev == nullptr)
		{
			headNode = ptr->next;
			headNode->prev = nullptr;
			delete ptr;
			ptr = headNode;
			length--;
		}
		else if (ptr->next == nullptr)
		{
			tailNode = ptr->prev;
			tailNode->next = nullptr;
			delete ptr;
			ptr = tailNode;
			length--;
		}
		else
		{
			temp = ptr->next;
			ptr->prev->next = ptr->next;
			ptr->next->prev = ptr->prev;
			delete ptr;
			ptr = temp;
			length--;
		}
	}

}