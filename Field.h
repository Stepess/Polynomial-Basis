#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

class field
{
public:
	field();
	field(string flag, string input);
	int firstBit();
	void show(string flag);
	void set(field& A);
	void add(field& A, field& B);
	void red(int* A, field& B);
	void redGen(int * A);
	void mod(int* A, field& N);
	void modGen(int* A);
	void mul(field& A, field& B);
	void squaring(field& A);
	void searchReverseEl(field& A);
	void power(field& A, int n);
	void trace(field& A);
	~field();

private:
	int* el = new int[191];
};

int arrCmp(int* A, int* B);
string convertToBin(int n);

//lab4

class onb
{
public:
	onb();
	onb(string flag, string input);
	int firstBit();
	void show(string flag);
	void set(onb& A);
	void add(onb& A, onb& B);
	void squaring(onb& A);
	int trace();
	int** mulMatrix();
	void invert(onb& A);
	void mul(onb& A, onb& B, int** matrix);
	~onb();

private:
	int* el = new int[191];
};

