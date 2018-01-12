#include <iostream>
#include "klasa.h"

using namespace std;

int main() {

	int n, x;

	cout << "Koliko ce brojeva biti u svakoj celiji: ";
	cin >> int(n);

	cout << "Unesite neki ceo broj: ";
	cin >> int(x);

	Node start(n, x);



	return 0;
}

/*
	u mainu vrtim .engine u while-u dokle god je unos true, a u svakom prolazu uzimam novi x

	napravi:
		first_step2
		engine
*/