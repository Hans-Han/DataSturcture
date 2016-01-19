#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
class Tree;

template <typename T>
class InorderIterator;

//template <typename T>
//class PreorderIterator;
//
//template <typename T>
//class PostorderIterator;

template <typename T>
class Stack
{
	T* stack;
	int top;
	int capacity;

public:
	Stack(int stackCapacity = 10) : capacity(stackCapacity) {
		if (capacity < 1)
			throw "Stack capacity must be > 0";
		top = -1;
		stack = new T[capacity];
	}

	Stack(Stack& stk)
	{
		capacity = stk.capacity;
		top = stk.top;
		stack = stk.stack;
	}

	bool IsEmpty() const
	{
		return top == -1;
	}
	T Top() const
	{
		if (IsEmpty())
			throw "Stack is empty";
		return stack[top];
	}

	void Push(const T& item)
	{
		if (top == capacity - 1)
		{
			ChangeSize(capacity, 2 * capacity);
			capacity *= 2;
		}
		stack[++top] = item;
	}

	void ChangeSize(int oldSize, int newSize)
	{
		if (newSize < 0)
			throw "New length must be > 0";

		T* temp = new T[newSize];
		int size = min(oldSize, newSize);
		for (int i = 0; i < size; i++)
			temp[i] = stack[i];

		delete[] stack;
		stack = temp;
	}

	void Pop()
	{
		if (IsEmpty())
			throw "Stack is empty. Cannot delete.";
		stack[top--].~T();
	}

	/*void Print()
	{
		for (int i = 0; i <= top; i++)
			cout << stack[i] << " ";
		cout << endl;
	}*/
};

template <typename T>
class TreeNode {
	friend class Tree<T>;
	friend class InorderIterator<T>;
	/*friend class PreorderIterator<T>;
	friend class PostorderIterator<T>;*/
private:
	T data;
	TreeNode<T> *leftChild;
	TreeNode<T> *rightChild;
public:
	TreeNode(T element, TreeNode<T> *lft = NULL, TreeNode<T> *rht = NULL) :data(element), leftChild(lft), rightChild(rht) {}
};

template <typename T>
class InorderIterator {
private:
	Stack<TreeNode<T>*> s;
	TreeNode<T> *currentNode;
public:
	InorderIterator() {
		currentNode = root;
	}
	T*Next() { //다음 중위 원소를 가져오는 코드
		while (currentNode) {
			s.Push(currentNode);
			currentNode = currentNode->leftChild;
		}
		if (s.IsEmpty())
			return 0;
		currentNode = s.Top();
		s.Pop();
		T& temp = currentNode->data;
		currentNode = currentNode->rightChild;
		return &temp;
	}
};


//template <typename T>
//class PreorderIterator {
//private:
//	Stack<TreeNode<T>*> s;
//	TreeNode<T> *currentNode;
//public:
//	PreorderIterator() {
//		currentNode = root;
//	}
//	T* Next() {
//	
//
//	}
//};


template <typename T>
class Tree {
private:
	TreeNode<T> *root;
	void addHelper(TreeNode<T> *rot, T val) {
		if (rot->data > val) {
			if (!rot->leftChild)
				rot->leftChild = new TreeNode<T>(val);
			else
				addHelper(rot->leftChild, val);
		}
		else {
			if (!rot->rightChild)
				rot->rightChild = new TreeNode<T>(val);
			else
				addHelper(rot->rightChild, val);
		}

	}
public:
	Tree(TreeNode<T> *rot = NULL) :root(rot) {}
	typedef InorderIterator<T> iterator;
	void add(T val) {
		if (root)
			this->addHelper(root, val);
		else
			root = new TreeNode<T>(val);
	}
	void NonrecInorder();
	void NonrecPreorder();
	void NonrecPostorder();
	void Inorder();
	void Inorder(TreeNode<T> *currentNode);
	void Preorder();
	void Preorder(TreeNode<T> *currentNode);
	void Postorder();
	void Postorder(TreeNode<T> *currentNode);

};

template <typename T>
void Tree<T>::NonrecInorder() { //중위 순회 비순환 버전
	Stack<TreeNode<T>*> s;
	TreeNode<T> *currentNode = root;
	cout << "NonrecInorder()" << endl;
	while (1) {
		while (currentNode) {
			s.Push(currentNode);
			currentNode = currentNode->leftChild;
		}
		if (s.IsEmpty()) {
			cout << endl;
			return;
		}
		currentNode = s.Top();
		s.Pop();
		cout << currentNode->data << " ";
		currentNode = currentNode->rightChild;
	}
}

template <typename T>
void Tree<T>::NonrecPreorder() {
	Stack<TreeNode<T>*> s;
	TreeNode<T> *currentNode = root;
	cout << "NonrecPreorder()" << endl;
	while (1) {
		while (currentNode) {
			cout << currentNode->data << " ";
			s.Push(currentNode);
			currentNode = currentNode->leftChild;
		}
		if (s.IsEmpty()) {
			cout << endl;
			return;
		}
		currentNode = s.Top();
		s.Pop();
		currentNode = currentNode->rightChild;
	}
}

template <typename T>
void Tree<T>::NonrecPostorder() {
	Stack<TreeNode<T>*> s;
	TreeNode<T> *currentNode = root;
	cout << "NonrecPostorder()" << endl;
	
	// Fail
}

template <typename T>
void Tree<T>::Inorder() {
	cout << "Inorder()" << endl;
	Inorder(root);
	cout << endl;
}

template <typename T>
void Tree<T>::Inorder(TreeNode<T> *currentNode) {
	if (currentNode) {
		Inorder(currentNode->leftChild);
		cout << currentNode->data << " ";
		Inorder(currentNode->rightChild);
	}
}

template <typename T>
void Tree<T>::Preorder() {
	cout << "Preorder()" << endl;
	Preorder(root);
	cout << endl;
}

template <typename T>
void Tree<T>::Preorder(TreeNode<T> *currentNode) {
	if (currentNode) {
		cout << currentNode->data << " ";
		Preorder(currentNode->leftChild);
		Preorder(currentNode->rightChild);
	}
}

template <typename T>
void Tree<T>::Postorder() {
	cout << "Postorder()" << endl;
	Postorder(root);
	cout << endl;
}

template <typename T>
void Tree<T>::Postorder(TreeNode<T> *currentNode) {
	if (currentNode) {
		Postorder(currentNode->leftChild);
		Postorder(currentNode->rightChild);
		cout << currentNode->data << " ";
	}
}

int main(void)
{
	Tree<int> tree;
	tree.add(11);
	tree.add(2);
	tree.add(6);
	tree.add(20);
	tree.add(13);
	tree.add(17);
	tree.Inorder();
	tree.NonrecInorder();
	tree.Preorder();
	tree.NonrecPreorder();
	tree.Postorder();
	tree.NonrecPostorder();

	return 0;
}
