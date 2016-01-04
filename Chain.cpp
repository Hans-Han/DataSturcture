#include <iostream>
using namespace std;

template <class T>
class Chain;

template <class T>
class ChainNode{
	friend class Chain<T>;
private:
	T data;
	ChainNode<T> * link;
public:
	ChainNode(const T& e, ChainNode<T> * next=NULL):data(e), link(next){}
};

template <class T>
class Chain{
private:
	ChainNode<T> * first;
	ChainNode<T> * last;
public:
	Chain(ChainNode<T> * fst=NULL, ChainNode<T> * lst=NULL):first(fst), last(lst){}
	void InsertBack(const T& insertData);
	void Concatenate(Chain<T> & b);
	void Reverse();
	void Print();
};

template <class T>
void Chain<T>::InsertBack(const T& insertData)
{
	if(first){
		last->link=new ChainNode<T>(insertData);
		last=last->link;
	}
	else{
		first=new ChainNode<T>(insertData);
		last=first;
	}
}

template <class T>
void Chain<T>::Concatenate(Chain<T>& b)
{
	if(first){
		last->link=b.first;
		last=b.last;
	}
	else{
		first=b.first;
		last=b.last;
	}
}

template <class T>
void Chain<T>::Reverse()
{
	ChainNode<T> *current=first;
	ChainNode<T> *previous=0;
	while(current){
		ChainNode<T> *r=previous;
		previous=current;
		current=current->link;
		previous->link=r;
	}
	first=previous;
}

template <class T>
void Chain<T>::Print()
{
	ChainNode<T> *current=first;
	while(current){
		cout<<current->data;
		if(current->link!=NULL)
			cout<<"->";
		current=current->link;
	}
	cout<<endl;
}

int main()
{
	Chain<int> chain;
	Chain<double> chain2;
	for(int i=1; i<=10; i++)
		chain.InsertBack(i);
	
	chain.Print();
	return 0;
}
