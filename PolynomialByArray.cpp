#include <iostream>
#include <math.h>
using namespace std;

class Polynomial;

class Term {
	friend class Polynomial;
private:
	float coef;
	int exp;
public:
	Term(float _coef = 0, int _exp = 0) : coef(_coef), exp(_exp) {}
	friend ostream& operator<<(ostream& os, const Polynomial& poly);
}; 

class Polynomial {
private:
	Term *termArray;
	int capacity;
	int terms;
public:
	Polynomial(){}
	Polynomial Add(Polynomial b);
	Polynomial Mult(Polynomial b);
	void NewTerm(const float _coef, const int _exp);
	void Print();
	float Eval(float x);
	friend ostream& operator<<(ostream& os, const Polynomial& poly);
};

void Polynomial::NewTerm(const float _coef, const int _exp) {
	if (terms == capacity) {
		capacity += 1;
		Term *temp = new Term[capacity];
		for (int i = 0; i < terms; i++)
			temp[i] = termArray[i];
		delete[] termArray;
		termArray = temp;
	}
	termArray[terms].coef = _coef;
	termArray[terms++].exp = _exp;
}

Polynomial Polynomial::Add(Polynomial b) {
	Polynomial c;
	int aPos = 0, bPos = 0;
	while (aPos < terms && bPos < b.terms) {
		if (termArray[aPos].exp == b.termArray[bPos].exp) {
			float _coef = termArray[aPos].coef + b.termArray[bPos].coef;
			if (_coef != 0)
				c.NewTerm(_coef, termArray[aPos].exp);
			aPos++, bPos++;
		}
		else if (termArray[aPos].exp < b.termArray[bPos].exp) {
			c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++;
		}
		else {
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
	}
	for (; aPos < terms; aPos++)
		c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	for (; bPos < b.terms; bPos++)
		c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);

	return c;
}

Polynomial Polynomial::Mult(Polynomial b)
{
	Polynomial c;
	Polynomial d;
	int aPos = 0, bPos = 0;
	float _coef;
	int _exp;

	int Pos, Pos2;

	while (aPos < terms) {
		while (bPos < b.terms) {
			_coef = termArray[aPos].coef * b.termArray[bPos].coef;
			_exp = termArray[aPos].exp + b.termArray[bPos].exp;
			c.NewTerm(_coef, _exp);
			bPos++;
		}
		aPos++;
		bPos = 0;
	}
	
	float temp = 0;

	for (Pos = 0; Pos < c.terms; Pos++) {
		_coef = c.termArray[Pos].coef;
		for (Pos2 = Pos + 1; Pos2 < c.terms; Pos2++) {
			if (c.termArray[Pos].exp == c.termArray[Pos2].exp) {
				temp += (c.termArray[Pos].coef + c.termArray[Pos2].coef);
				if (temp == 0)
					_coef = temp;
				c.termArray[Pos2].coef = 0;
			}
		}
		if (temp != 0)
			_coef = temp;
		d.NewTerm(_coef, c.termArray[Pos].exp);
		temp = 0;
	}
	
	return d;
}
void Polynomial::Print() {
	int Pos = 0;
	while (Pos < terms) {
		if (termArray[Pos].coef != 0) {
			if (termArray[Pos].exp != 0 && termArray[Pos].coef != 1)
				cout << termArray[Pos].coef << "x^" << termArray[Pos].exp;
			else {
				if (termArray[Pos].exp == 0)
					cout << termArray[Pos].coef;
				else if (termArray[Pos].exp != 0 && termArray[Pos].coef == 1)
					cout << "x^" << termArray[Pos].exp;
			}
		}
			if (Pos + 1 != terms && termArray[Pos + 1].coef>0)
				cout << "+";
			Pos++;
	}
	cout << endl;
}

ostream& operator<<(ostream& os, const Polynomial& poly)
{
	int Pos = 0;
	while (Pos < poly.terms) {
		if (poly.termArray[Pos].exp != 0 && poly.termArray[Pos].coef != 1)
			cout << poly.termArray[Pos].coef << "x^" << poly.termArray[Pos].exp;
		else {
			if (poly.termArray[Pos].exp == 0)  
				cout << poly.termArray[Pos].coef;
			else if (poly.termArray[Pos].exp != 0 && poly.termArray[Pos].coef == 1)
				cout << "x^" << poly.termArray[Pos].exp;
		}

		if (Pos + 1 != poly.terms && poly.termArray[Pos + 1].coef>0)
			cout << "+";
		Pos++;
	}
	cout << endl;
	return os;
}

float Polynomial::Eval(float x)
{
	float value = 0;
	int Pos = 0;

	while (Pos < terms) {
		value += termArray[Pos].coef * pow(x, termArray[Pos].exp);
		Pos++;
	}
	return value;
}

int main(void)
{
	float value;
	Polynomial a, b, c, d;
	a.NewTerm(3, 2);
	a.NewTerm(2, 1);
	a.NewTerm(-4, 0);
	cout << "a: ";
	a.Print();
	
	b.NewTerm(1, 8);
	b.NewTerm(-10, 5);
	b.NewTerm(-3, 3);
	b.NewTerm(2, 2);
	cout << "b: ";
	b.Print();

	c = a.Add(b);
	cout << "c = a + b: ";
	c.Print();
	cout << endl;

	cout << ">>> 입출력 연산자 오버로딩 테스트 <<<" << endl;
	c = a.Add(b);
	cout << a << b << c << endl;

	d = a.Mult(b);
	cout << "d = a * b: ";
	d.Print();
	cout << endl;

	cout << ">>> Eval(float x) 함수 테스트<<<" << endl;
	cout << "x의 값 입력: ";
	cin >> value;
	cout << "c에 대입하여 계산한 값: " << c.Eval(value) << endl;
	cout << "d에 대입하여 계산한 값: " << d.Eval(value) << endl;
}
