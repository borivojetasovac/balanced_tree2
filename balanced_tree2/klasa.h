#pragma once

#include <iostream>

using namespace std;

class Node {

private:
	int n;
	int *numbers;
	int num_len;
	Node **pointers;	//	niz pointera, uvek biti za jedan duzi od niza int-ova
	Node *above;

public:
	Node();																	//	podrazumevani konstruktor
	Node(int n, int x);														//	konstruktor za pravljenje samo prve celije, jer nema *above
	Node(int n, int x, Node *above);										//	konstruktor za pravljenje novih celija
	Node(int n, int *numbers, Node **pointers, Node *above);				//	konstruktor za pravljenje celije izmedju dve postojece
	Node(int n, int num_len, int *numbers, Node **pointers, Node *above);	//	konstruktor za kopiju
	void first_step(int x);													//	ne radi sa pointerima, za to koristi first_step2
	void first_step2(int x);
	void new_node_odd(int x);												//	za neparne
	void new_node_even(int x);												//	za parne
	void engine(int x);
};
