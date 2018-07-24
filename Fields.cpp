// Field.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Field.h"

using namespace std;

int main()
{
	field f("hex", "399F8292DFFBC26B4EF3E95CBE2F987673EF5F8A98D03726");
	f.show("hex");
	cout << endl;
	field f1("hex", "23FD8D168B784FC7FAED1098BE3B6E46E741654FE6A2662E");
	f1.show("hex");
	cout << endl;
	field fq("hex", "0");
	fq.show("hex");
	cout << endl;
	field f2, f3, f4;
	f2.add(f, f1);
	f2.show("hex");
	cout << endl;
	f3.mul(f, f1);
	f3.show("hex");
	cout << endl;
	f4.squaring(f);
	f4.show("hex");
	cout << endl;
	field f5;
	f5.searchReverseEl(f);
	f5.show("hex");
	cout << endl;
	field f6;
	f6.power(f, 2);
	f6.show("hex");
	cout << endl;
	field f7;
	f7.trace(f);
	f7.show("hex");
	cout << endl;




	/*string one = "";

	for (int i = 0; i < 191; i++)
		one.insert(i, "1");*/
	/*onb f("hex", "482FF1FB43882341811C862FF9893527F72E058D1AAA2BE9");
	f.show("hex");
	cout << endl;
	onb f1("hex", "25606F3AAA5D0EC7C3B5928948358FBD4550EC4786D82F3E");
	f1.show("hex");
	cout << endl;
	int** A = new int*[191];
	for (int i = 0; i < 191; i++)
		A[i] = new int[191];*/
	/*onb f2, f3;
	f2.add(f, f1);
	f2.show("hex");
	cout << endl;
	f3.squaring(f);
	f3.show("hex");
	cout << endl;
	cout << f.trace() << endl;;*/
	//A = f.mulMatrix();
	//f.invert(f);
	/*onb f4;
	f4.mul(f, f1, A);
	f4.show("hex");
	cout << endl;
	for (int i = 0; i < 191; i++)
		delete[] A[i];*/
	getchar();
    return 0;
}
//нужно помнить что число в масиве перевернуто!!!!!!
//в 3ей доделать нормальный мод (идти слева направо и ксорить с целым полиномом, когда встречу бит 1) - done
//в 4ой для шестнадцатиричного представления использовать только числа 191 бит, а в случае бинарного представления 100...00 = бэта, 00..001 = бэта (в 190)