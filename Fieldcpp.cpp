#include "stdafx.h"
#include <iostream>
#include <string>
#include "Field.h"
#include <cmath>

using namespace std;

int arrCmp(int* A, int* B)
{
	int result = 0, a = 499, b = 499;
	while ((A[a] == 0) && (a > -1))
		a--;
	while ((B[b] == 0) && (a > -1))
		b--;
	if (b > a)
		return -1;
	else
		return 1;
}

field::field()
{
	for (int i = 0; i < 191; i++)
		el[i] = 0;
}

field::field(string flag, string input)
{
	for (int i = 0; i < 191; i++)
		el[i] = 0;
	if (flag == "hex")
	{
		int i = 0;
		int s = input.size();
		int buff;
		int f = 0;
		char symb;
		for (int j = s - 1; j > -1; j--) {
			f = 0;
			switch (input[j])
				{
					case 'A':
						symb = '0';
						f = 1;
						break;
					case 'B':
						symb = '1';
						f = 1;
						break;
					case 'C':
						symb = '2';
						f = 1;
						break;
					case 'D':
						symb = '3';
						f = 1;
						break;
					case 'E':
						symb = '4';
						f = 1;
						break;
					case 'F':
						symb = '5';
						f = 1;
						break;
					default:
						f = 0;
						break;
				}
			if (f == 1) { buff = symb - '0' + 10; }
			else { buff = input[j] - '0'; }
			for (int k = 0; k < 4; k++) {
				if (i!=191)  
					el[i] = ((buff >> k) & 1);
				i++;
			}
		}
	}
	else
	if (flag == "bin")
	{
		int i = 0;
		int s = input.size();
		for (int j = s - 1; j > -1; j--) {
			el[i] = input[j] - '0';
			i++;
		}
	}
	else
	{
		cout << "Wrong flag!!!";
		return;
	}
}

int field::firstBit()
{
	int res = 190;
	while ((el[res] == 0) && (res > -1))
		res--;
	return res;
}

void field::show(string flag)
{
	
	if (flag == "vector")
	{
		int s = this->firstBit();
		for (int i = s; i > -1 ; i--)
			cout << el[i] << "   ";
		if (s == -1)
			cout << "0";
	}else
		if (flag == "polynom")
		{
			string res = "";
			string l;
			for (int i = 190; i > 1; i--) {
				if (el[i] == 1) {
					l = to_string(i);
					res = res + "x^" + l + " + ";
				}
				
			}
			if (el[1] == 1)
				res = res + 'x' + " + ";
			if (el[0] == 1)
				res = res + '1' + " + ";
			if (res == "") {
				res = "0";
				cout << res;
				return;
			}
			res.erase(res.size() - 3, 3);
			cout << res;
		}
		else 
			if (flag == "hex") {
				string res = "";
				int k = this->firstBit();
				int buff=0;
				char x;
				/*cout << k << endl;
				cout << endl;
				cout << endl;*/
				for (int i = 0; i <= k; i = i + 4)
				{

					if (i != 188) {
						buff = buff + el[i];
						buff = buff + (el[i + 1] << 1);
						buff = buff + (el[i + 2] << 2);
						buff = buff + (el[i + 3] << 3);
					}
					else {
						buff = buff + el[i];
						buff = buff + (el[i + 1] << 1);
						buff = buff + (el[i + 2] << 2);
					}
					switch (buff)
					{
					case 0:
						x = '0';
						break;
					case 1:
						x = '1';
						break;
					case 2:
						x = '2';
						break;
					case 3:
						x = '3';
						break;
					case 4:
						x = '4';
						break;
					case 5:
						x = '5';
						break;
					case 6:
						x = '6';
						break;
					case 7:
						x = '7';
						break;
					case 8:
						x = '8';
						break;
					case 9:
						x = '9';
						break;
					case 10:
						x = 'A';
						break;
					case 11:
						x = 'B';
						break;
					case 12:
						x = 'C';
						break;
					case 13:
						x = 'D';
						break;
					case 14:
						x = 'E';
						break;
					case 15:
						x = 'F';
						break;
					default:
						break;
					}
					res = res + x;
					buff = 0;
				}
				string s="";
				int m = res.size();
				if (m == 0) {
					cout << '0';
					return;
				}
				for (int i = m-1; i > -1; i--)
					cout << res[i];
				return;
			}
			else{
			cout << "Wrong flag!!!";
			return;
		}
	
	
}

void field::set(field& A)
{
	for (int i = 0; i < 191; i++)
		el[i] = A.el[i];
}

void field::add(field& A, field& B)
{
	field C;
	for (int i = 0; i < 191; i++)
		C.el[i] = (A.el[i] + B.el[i]) & 1;
	this->set(C);
}


void field::red(int* A, field& B)
{
	int* C = new int[500];
	int len = B.firstBit();
	for (int i = 0; i < 500; i++)
		C[i] = A[i];
	for (int i=500; i>=len; i--)
		if (C[i] == 1) {
			int k = 0;
			for (int j = len; j > -1; j--)
			{
				C[i - k] = C[i - k] ^ B.el[j];
				k++;
			}
		}
	for (int i = 0; i < 191; i++)
		this->el[i] = C[i];
	delete[] C;
}

void field::redGen(int *A)
{
	int* C = new int[500];
	int* B = new int[500];
	int len = 191;
	for (int i = 0; i < 500; i++)
		B[i] = 0;
	B[0] = 1;
	B[9] = 1;
	B[191] = 1;
	for (int i = 0; i < 500; i++)
		C[i] = A[i];
	for (int i = 500; i >= len; i--)
		if (C[i] == 1) {
			int k = 0;
			for (int j = len; j > -1; j--)
			{
				C[i - k] = C[i - k] ^ B[j];
				k++;
			}
		}
	for (int i = 0; i < 191; i++)
		this->el[i] = C[i];
	delete[] C;
	delete[] B;
}

void field::mod(int* A, field& N)//нито над взять алг с методі 1ой лаби
{
	/*field C;
	int s = N.firstBit();
	for (int i = s; i > -1; i--) {
		C.el[i] = A.el[i] - N.el[i];
		if (C.el[i] == -1)
			C.el[i] = 0;
	}	
	this->set(C);*/
	int* R = new int[500];
	int* B = new int[500];
	int* C = new int[500];
	int k = N.firstBit()+1;
	
	for (int i = 0; i < 500; i++)
		R[i] = A[i];
	for (int i = 0; i < 500; i++)
		B[i] = 0;
	for (int i = 0; i < 500; i++)
		C[i] = 0;
	for (int i = 0; i < 191; i++)
		B[i] = N.el[i];
	while ((arrCmp(R, B) == 1) || (arrCmp(R, B) == 0)) {
		int t = 499;
		while ((R[t] == 0) && (t > -1))
			t--;
		t++;
		
		for (int i = 0; i < 500; i++)
			C[i] = B[i];
		
		//cout << t - k << endl;
		for (int j = 1; j <= t - k; j++) {
			//cout << j << endl;
			for (int i = 499; i > 0; i--)
			{
				C[i] = C[i - 1];
				//cout << i << endl;
			}
			C[j - 1] = 0;
			
		}
		
		if (arrCmp(R, C) == -1) {
			
			t--;
			for (int i = 0; i < 500; i++)
				C[i] = B[i];

			//cout << t - k << endl;
			for (int j = 1; j <= t - k; j++) {
				//cout << j << endl;
				for (int i = 499; i > 0; i--)
				{
					C[i] = C[i - 1];
					//cout << i << endl;
				}
				C[j - 1] = 0;

			}

		}
		//cout << "help" << endl;
		for (int i = 0; i < 500; i++)
			R[i] = R[i] ^ C[i];
		
		
	}
	
	for (int i = 0; i < 191; i++)
	{
		this->el[i] = R[i];
	}
	//cout << "help" << endl;
	delete[] R;
	delete[] B;
	delete[] C;
}

void field::modGen(int* A)
{
	int* R = new int[500];
	int* B = new int[500];
	int* C = new int[500];
	//int k = N.firstBit() + 1;
	int k = 191;
	for (int i = 0; i < 500; i++)
		R[i] = A[i];
	for (int i = 0; i < 500; i++)
		B[i] = 0;
	for (int i = 0; i < 500; i++)
		C[i] = 0;
	
	B[0] = 1;
	B[9] = 1;
	B[191] = 1;
	while ((arrCmp(R, B) == 1) || (arrCmp(R, B) == 0)) {
		//cout << "sss" << endl;
		int t = 499;
		while ((R[t] == 0) && (t > -1))
			t--;
		t++;

		for (int i = 0; i < 500; i++)
			C[i] = B[i];

		//cout << t - k << endl;
		for (int j = 1; j <= t - k; j++) {
			//cout << j << endl;
			for (int i = 499; i > 0; i--)
			{
				C[i] = C[i - 1];
				//cout << i << endl;
			}
			C[j - 1] = 0;

		}

		if (arrCmp(R, C) == -1) {

			t--;
			for (int i = 0; i < 500; i++)
				C[i] = B[i];

			//cout << t - k << endl;
			for (int j = 1; j <= t - k; j++) {
				//cout << j << endl;
				for (int i = 499; i > 0; i--)
				{
					C[i] = C[i - 1];
					//cout << i << endl;
				}
				C[j - 1] = 0;

			}

		}
		//cout << "help" << endl;
		for (int i = 0; i < 500; i++)
			R[i] = R[i] ^ C[i];


	}

	for (int i = 0; i < 191; i++)
	{
		this->el[i] = R[i];
	}
	//cout << "help" << endl;
	delete[] R;
	delete[] B;
	delete[] C;
}

void field::mul(field& A, field& B)//190 - крайний
{
	field s;
	int* C = new int[500];
	for (int i = 0; i < 500; i++)
		C[i] = 0;
	int* buff = new int[500];
	for (int i = 0; i < 500; i++)
		buff[i] = 0;
	int as = A.firstBit(), bs = B.firstBit();
	for (int j = as; j > -1; j--) {
		
		for (int i = bs; i > -1; i--) {
			buff[j + i] = A.el[j] * B.el[i];
		}
		s.redGen(buff);
		for (int i = 0; i < 191; i++)
			buff[i] = s.el[i];
		
		for (int i = 0; i < 500; i++)
			C[i] = (C[i] + buff[i]) & 1;
		
		for (int i = 0; i < 500; i++)
			buff[i] = 0;
	}
	for (int i = 0; i < 191; i++)
		this->el[i] = C[i];
	delete[] C;
	delete[] buff;
}

void field::squaring(field& A)
{
	int* C = new int[500];
	for (int i = 0; i < 500; i++)
		C[i] = 0;
	int s = A.firstBit();
	int buff = 2 * s;
	for (int i = s+1; i > 0; i--) {
		C[buff] = A.el[i-1];
		buff = buff - 2;
	}
	this->redGen(C);
	delete[] C;
}

void field::searchReverseEl(field& A)
{
	
	field C,buff;
	C.add(C, A);
	buff.add(buff, A);
	for (int i = 0; i < 189; i++) {
		buff.squaring(buff);
		C.mul(C, buff);
	}
	C.squaring(C);
	this->set(C);
}

field::~field()
{
	delete[] el;
}

string convertToBin(int n)
{
	string res = "",buff="";
	if (n == 0) {
		res = "0";
		return res;
	}
	if (n == 1) {
		res = "1";
		return res;
	}
	int m = log2(n)+1;
	for (int i = 0; i < m; i++)
		res = res + to_string((n >> i) & 1);
	reverse(res.begin(), res.end());
	return res;
}

void field::power(field& A, int n)
{
	field C("bin", "1");
	string bin = convertToBin(n);
	for (int i = 0; i < bin.size(); i++) {
		if (bin[i] == '1') {
			C.mul(C, A);
		}
		if (i != bin.size() - 1) {
			C.squaring(C);
		}
	}
	this->set(C);
}

void field::trace(field& A)
{
	field C, buff;
	C.add(C, A);
	buff.add(buff, A);
	for (int i = 0; i < 190; i++) {
		buff.squaring(buff);
		C.add(C, buff);
	}
	this->set(C);
}

//
//lab4
//

onb::onb()
{
	for (int i = 0; i < 191; i++)
		el[i] = 0;
}

onb::onb(string flag, string input)
{
	for (int i = 0; i < 191; i++)
		el[i] = 0;
	if (flag == "bin")
	{
		int i = 0;
		int s = input.size();
		for (int j = s - 1; j > -1; j--) {
			//cout << input[j] << "  ";
			el[i] = input[j] - '0';
			i++;
		}
		
		/*cout << endl;
		for (int k=0; k < i; k++)
			cout << el[k] << "  ";
		cout << endl;*/
	}else
		if (flag == "hex")
		{
			int i = 0;
			int s = input.size();
			int buff;
			int f = 0;
			char symb;
			for (int j = s - 1; j > -1; j--) {
				//cout << input[j] << endl;
				f = 0;
				switch (input[j])
				{
				case 'A':
					symb = '0';
					f = 1;
					break;
				case 'B':
					symb = '1';
					f = 1;
					break;
				case 'C':
					symb = '2';
					f = 1;
					break;
				case 'D':
					symb = '3';
					f = 1;
					break;
				case 'E':
					symb = '4';
					f = 1;
					break;
				case 'F':
					symb = '5';
					f = 1;
					break;
				default:
					f = 0;
					break;
				}
				if (f == 1) { buff = symb - '0' + 10; }
				else { buff = input[j] - '0'; }
				for (int k = 0; k < 4; k++) {
					if (i!=191)
						el[i] = ((buff >> k) & 1);
					//cout << i << endl;
					i++;
				}
				
				/*cout << i << "  ";
				cout << el[i] << endl;*/
			}
		}
}

int onb::firstBit()
{
	int res = 190;
	while ((el[res] == 0) && (res > -1))
		res--;
	return res;
}

void onb::show(string flag)
{

	if (flag == "vector")
	{
		int s = this->firstBit();
		for (int i = s; i > -1; i--)
			cout << el[i] << "   ";
		if (s == -1)
			cout << "0";
	}else
		if (flag == "hex") {
			string res = "";
			int k = this->firstBit();
			int buff = 0;
			char x;
			//cout << k << endl;
			for (int i = 0; i <= k; i = i + 4)
			{
				if (i != 188) {
				buff = buff + el[i];
				buff = buff + (el[i + 1] << 1);
				buff = buff + (el[i + 2] << 2);
				buff = buff + (el[i + 3] << 3);
				}
				else {
					buff = buff + el[i];
					buff = buff + (el[i + 1] << 1);
					buff = buff + (el[i + 2] << 2);
				}
				//cout << buff << endl;
				switch (buff)
				{
				case 0:
					x = '0';
					break;
				case 1:
					x = '1';
					break;
				case 2:
					x = '2';
					break;
				case 3:
					x = '3';
					break;
				case 4:
					x = '4';
					break;
				case 5:
					x = '5';
					break;
				case 6:
					x = '6';
					break;
				case 7:
					x = '7';
					break;
				case 8:
					x = '8';
					break;
				case 9:
					x = '9';
					break;
				case 10:
					x = 'A';
					break;
				case 11:
					x = 'B';
					break;
				case 12:
					x = 'C';
					break;
				case 13:
					x = 'D';
					break;
				case 14:
					x = 'E';
					break;
				case 15:
					x = 'F';
					break;
				default:
					break;
				}
				res = res + x;
				buff = 0;
			}
			string s = "";
			int m = res.size();
			if (m == 0) {
				cout << '0';
				return;
			}
			for (int i = m - 1; i > -1; i--)
				cout << res[i];
			return;
		}
		else 
			if(flag == "polynom")
			{
				string res = "";
				string l;
				int k = this->firstBit();
				if (k == 190) {
					res = "1";
					cout << res;
					return;
				}
				if (k == -1) {
					res = "0";
					cout << res;
					return;
				}
				for (int i = 1; i <= k; i++) {
					//cout << i << endl;
					if (el[i] == 1) {
						l = to_string(i+1);
						reverse(l.begin(), l.end());
						res = res + " + " + l + "^x";
					}

				}
				if (el[0] == 1) {
					res.insert(0, " + x");
				}
				reverse(res.begin(), res.end());
				res.erase(res.size() - 3, 3);
				cout << res;
			}
		else
			{
			cout << "Wrong flag!!!";
			return;
		}
}

void onb::set(onb& A)
{
	for (int i = 0; i < 191; i++) {
		//cout << A.el[i] << "   ";
		el[i] = A.el[i];
	}
	//cout << endl;
}


void onb::add(onb& A, onb& B)
{
	onb C;
	for (int i = 0; i < 191; i++)
		C.el[i] = (A.el[i] + B.el[i]) & 1;
	this->set(C);
}

void onb::squaring(onb& A)
{
	onb C;
	/*for (int k = 0; k < 191; k++)
		cout << A.el[k] << "  ";*/
	//cout << endl;
	for (int i = 1; i < 191; i++)
		C.el[i-1] = A.el[i];
	
	
	C.el[190] = A.el[0];
	/*for (int k = 0; k < 191; k++)
		cout << C.el[k] << "  ";*/
	/*for (int i = 0; i < 190; i++)
		cout << C.el[i];
	cout << endl;
	for (int i = 0; i < 190; i++)
		cout << A.el[i];
	cout << endl;*/
	//cout << endl;
	this->set(C);
}

int onb::trace()
{
	int res;
	for (int i = 0; i < 191; i++)
		res = (res + el[i]) & 1;
	return res;
}

int** onb::mulMatrix()
{
	int** matrix = new int*[191];
	int x=0,y=0, buff=0;
	int size = 191;
	int p = size * 2 + 1;
	for (int i = 0; i < 191; i++)
		matrix[i] = new int[191];
	for (int i = 0; i < 191; i++)
		for (int j = 0; j < 191; j++)
			matrix[i][j] = 0;
	for (int i=0; i<size; i++)
		for (int j = i; j < size; j++) {
			//cout << i << "  " << j << endl;
			x = 1;
			for (int k = 0; k < i; k++)
				x = (x * 2) % p;
			y = 1;
			for (int k = 0; k < j; k++)
				y = (y * 2) % p;
			buff = (x + y) % p;
			//cout << buff << endl;
			if (buff == 1)
				matrix[i][j] = 1;
			else {
				buff = (x - y);
				if (buff < 0)
					buff = buff + p;
			}
				if (buff == 1)
					matrix[i][j] = 1;
				else {
					buff = (-x + y);
					if (buff < 0)
						buff = buff + p;
				}
					if (buff == 1)
						matrix[i][j] = 1;
					else {
						buff = -x - y;
						if (buff < 0)
							buff = buff + p;
					}
						if (buff == 1)
							matrix[i][j] = 1;
		}
	for (int j = 0; j < size; j++)
		for (int i = j; i < size; i++)
			matrix[i][j] = matrix[j][i];
	return matrix;
	for (int i = 0; i < 191; i++)
		delete[] matrix[i];
}

void onb::invert(onb& A)
{
	onb C;
	//A.show("vector");
	//cout << endl;
	for (int i = 0; i < 191; i++)
		C.el[i]=A.el[190-i];
	//C.show("vector");
	this->set(C);
}

void onb::mul(onb& A, onb& B, int** matrix)
{
	onb X, Y,C;
	X.invert(A);
	Y.invert(B);
	for (int j = 0; j < 191; j++)
		for (int i = 0; i < 191; i++)
			C.el[j] = (C.el[j] + X.el[i]*matrix[i][j]) % 2;
	for (int j=0; j< 191; j++)
		for (int i = 0; i < 191; i++)
			C.el[j] = (C.el[j] + C.el[i] * Y.el[i]) % 2;
	C.invert(C);
	
	this->set(C);
}

onb::~onb()
{
	delete[] el;
}