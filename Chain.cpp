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
	void InsertFront(const T& insertData);
	void Delete(T delData);
	void Concatenate(Chain<T> & b);
	void Reverse();
	void Print();
	//알고리즘 연습문제
	T Max();
	void mSmall(int m);
	void ascendingSort();
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
void Chain<T>::InsertFront(const T& insertData)
{
	ChainNode<T> *insertNode=new ChainNode<T>(insertData);
	if(first){
		insertNode->link=first;
		first=insertNode;
	}
	else{
		first=insertNode;
		last=first;
	}
}

template <class T>
void Chain<T>::Delete(T delData)
{
	ChainNode<T> *current=first;
	ChainNode<T> *beforeNode=NULL;
	if(current==NULL || current->data==delData){
		if(first==NULL){
			cout<<"Empty List : You can't delete data from this list."<<endl;
			return;
		}
		first=current->link;
		delete current;
	}
	else{
		for(current=first->link; current!=NULL; beforeNode=current, current=current->link)
		{
			if(current->data==delData){
				if(current->link==NULL)
					last=beforeNode;
				beforeNode->link=current->link;
				delete current;
				return;
			}
		}
	}
}



template <class T>
void Chain<T>::Concatenate(Chain<T>& b)
{
	if(first){
		if(!b.first)
			return;
		last->link=b.first;
		last=b.last;
	}
	else{
		first=b.first;
		last=b.last;
	}
	b.first=b.last=0;
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
	last=first;
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

template <class T>
T Chain<T>::Max()
{
	ChainNode<T> *current=first;
	T max=current->data;
	while(current)
	{
		if(current->link==NULL)
			return max;
		if(max < current->link->data){
			current=current->link;
			max=current->data;
		}
		else
			current=current->link;
	}
}

template <class T>
void Chain<T>::ascendingSort()
{
	ChainNode<T> *current1;
	T temp;
	ChainNode<T> *current2;
	for(current1=first; current1!=NULL; current1=current1->link)
	{
		for(current2=current1->link; current2!=NULL; current2=current2->link)
		{
			if(current1->data > current2->data){
				temp=current1->data;
				current1->data=current2->data;
				current2->data=temp;
			}
		}
	}
}
template <class T>
void Chain<T>::mSmall(int m)
{
	ChainNode<T> *current=first;
	(*this).ascendingSort();
	for(int i=0; i<m; i++)
	{
		cout<<current->data<<"  ";
		current=current->link;
	}
	cout<<endl;
}

int main()
{
	Chain<double> chain;
	Chain<double> chain2;
	chain2.Delete(1);
	for(double i=1; i<=3; i++)
	{
		chain.InsertBack(i);
		chain.InsertFront(i+3);
	}
	for(double i=1.5; i<4; i++)
	{
		chain2.InsertBack(i);
		chain2.InsertFront(i+3.0);
	}
	cout<<"===chain==="<<endl;
	chain.Print();
	cout<<"===chain2==="<<endl;
	chain2.Print();
	cout<<"===chain.Delete(1) test==="<<endl;
	chain.Delete(1);
	chain.Print();
	cout<<"===chain and chain2 concatenate==="<<endl;
	chain.Concatenate(chain2);
	chain.Print();
	cout<<"===chain.Reverse() test==="<<endl;
	chain.Reverse();
	chain.Print();
	cout<<endl;
	cout<<"Algorithm : search Max"<<endl;
	cout<<chain.Max()<<endl;
	cout<<"Algorithm : m개의 가장 작은 수 찾기"<<endl;
	chain.mSmall(4);
	return 0;
}
