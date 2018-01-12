#include <iostream>
#include "klasa.h"

using namespace std;

Node::Node() {
	n = 0;
	num_len = 0;
	numbers = NULL;
	pointers = NULL;
	above = NULL;
}

Node::Node(int n, int x){
	this->n = n;

	numbers = (int*)malloc(n* sizeof(int));

	*pointers = (Node*)malloc((n + 1) * sizeof(Node));
	for (int i = 0; i < n + 1; i++) {
		pointers[i] = NULL;
	}
	above = NULL;

	numbers[0] = x;
	num_len = 1;
}

Node::Node(int n, int x, Node *above) {
	this->n = n;
	numbers = (int*)malloc(n* sizeof(int));
	*pointers = (Node*)malloc((n + 1) * sizeof(Node));
	for (int i = 0; i < n + 1; i++) {
		pointers[i] = NULL;
	}
	this->above = above;

	numbers[0] = x;
	num_len = 1;
}

Node::Node(int n, int *numbers, Node **pointers, Node *above) {
	this->n = n;

	this->numbers = (int*)malloc(n* sizeof(int));
	for (int i = 0; i < n; i++) {
		this->numbers[i] = numbers[i];
	}

	*pointers = (Node*)malloc((n + 1) * sizeof(Node));
	for (int i = 0; i < n + 1; i++) {
		this->pointers[i] = pointers[i];
	}
	
	*this->above = *above;
}

Node::Node(int n, int num_len, int *numbers, Node **pointers, Node *above) {
	this->n = n;
	this->num_len = num_len;

	this->numbers = (int*)malloc(n* sizeof(int));
	for (int i = 0; i < n; i++) {
		this->numbers[i] = numbers[i];
	}

	*pointers = (Node*)malloc((n + 1) * sizeof(Node));
	for (int i = 0; i < n + 1; i++) {
		this->pointers[i] = pointers[i];
	}

	*this->above = *above;
}

void Node::first_step(int x) {
	int start = -1;

	for (int i = 0; i < num_len; i++) {
		if (x < numbers[i]) {
			start = i;
			for (i = num_len; i > start; i--) {
				numbers[i] = numbers[i - 1];
			}
			numbers[i] = x;
			num_len++;
			break;
		}
	}
	if (start == -1){
		numbers[num_len] = x;
		num_len++;
	}
}

void Node::first_step2(int x) {
	int start = -1;

	for (int i = 0; i < num_len; i++) {
		if (x < numbers[i]) {
			start = i;
			for (i = num_len; i > start; i--) {
				numbers[i] = numbers[i - 1];
				//pointers[i + 1] = pointers[i];
			}
			numbers[i] = x;
			//pointers[i + 1] = NULL;
			num_len++;
			break;
		}
	}
	if (start == -1){
		numbers[num_len] = x;
		num_len++;
	}
}

void Node::new_node_odd(int x) {
	int up_index, i;
	int *temp = (int *)malloc((n + 1) * sizeof(int));
	
	for (i = 0; i < n; i++) {
		if (numbers[i] < x)
			temp[i] = numbers[i];
		else {
			temp[i] = x;
			for (++i; i < n + 1; i++) {
				temp[i] = numbers[i];
			}
		}
	}
	if (i == n)
		temp[n] = x;	//	temp je sortiran niz intova(numbers) kome je dodat i x

	up_index = n / 2;	//	clan na ovom mestu ide gore
	
	if (above != NULL){
		Node current = *above;
		current.first_step(temp[up_index]);	//	ovde treba first_step2 za current pointere
	}
	else{
		int *l_numbers = (int *)malloc(up_index * sizeof(int));
		int *r_numbers = (int *)malloc(up_index * sizeof(int));
		for (int i = 0; i < up_index; i++) {
			l_numbers[i] = numbers[i];
			r_numbers[i] = numbers[up_index + 1 + i];
		}

		Node **l_pointers, **r_pointers;
		*l_pointers = (Node*)malloc((n + 1) * sizeof(Node));
		*r_pointers = (Node*)malloc((n + 1) * sizeof(Node));
		for (int i = 0; i < up_index + 1; i++) {
			*l_pointers[i] = *pointers[i];
			*r_pointers[i] = *pointers[up_index + 1 + i];
		}
		Node left = Node(n, l_numbers, l_pointers, this);
		Node right = Node(n, r_numbers, r_pointers, this);

		left.num_len = right.num_len = up_index;

		free(numbers);
		numbers = (int*)malloc(n * sizeof(int));
		numbers[0] = temp[up_index];
		
		free(pointers);
		*pointers = (Node*)malloc((n + 1) * sizeof(Node));
		for (int i = 0; i < up_index + 1; i++) {
			pointers[i] = NULL;
		}
		*pointers[0] = left;
		*pointers[1] = right;

		num_len = 2;
	}
}

void Node::new_node_even(int x) {
	int up_index, i;
	int *temp = (int *)malloc((n + 1) * sizeof(int));

	for (i = 0; i < n; i++) {
		if (numbers[i] < x)
			temp[i] = numbers[i];
		else {
			temp[i] = x;
			for (++i; i < n + 1; i++) {
				temp[i] = numbers[i];
			}
		}
	}
	if (i == n)
		temp[n] = x;	//	temp je sortiran niz intova(numbers) kome je dodat i x

	up_index = n / 2 - 1;	//	clan na ovom mestu ide gore

	if (above != NULL){
		Node current = *above;
		current.first_step(temp[up_index]);	//	ovde treba first_step2 za current pointere
	}
	else{
		int *l_numbers = (int *)malloc(up_index * sizeof(int));
		int *r_numbers = (int *)malloc((up_index + 1) * sizeof(int));
		for (int i = 0; i < up_index; i++) {
			l_numbers[i] = numbers[i];
			r_numbers[i] = numbers[up_index + 1 + i];
		}
		r_numbers[i] = numbers[up_index + 1 + i];

		Node **l_pointers, **r_pointers;
		*l_pointers = (Node*)malloc((n + 1) * sizeof(Node));
		*r_pointers = (Node*)malloc((n + 1) * sizeof(Node));
		for (int i = 0; i < up_index + 1; i++) {
			*l_pointers[i] = *pointers[i];
			*r_pointers[i] = *pointers[up_index + 1 + i];
		}
		*r_pointers[i] = *pointers[up_index + 1 + i];

		Node left = Node(n, l_numbers, l_pointers, this);
		Node right = Node(n, r_numbers, r_pointers, this);

		left.num_len = up_index;
		right.num_len = up_index + 1;

		free(numbers);
		numbers = (int*)malloc(n * sizeof(int));
		numbers[0] = temp[up_index];

		free(pointers);
		*pointers = (Node*)malloc((n + 1) * sizeof(Node));
		for (int i = 0; i < up_index + 1; i++) {
			pointers[i] = NULL;
		}
		*pointers[0] = left;
		*pointers[1] = right;

		num_len = 2;
	}
}

void Node::engine(int x) {

	bool flag = true;
	Node current = Node(n, num_len, numbers, pointers, above);	//	kopija this-a

	while (flag) {

		if (current.pointers[0] != NULL) {	//	nisam u poslednjem, idem dole
			for (int i = 0; i < current.num_len; i++) {
				if (current.numbers[i] > x) {
					current = *current.pointers[i];
					break;
				}
				if (i == current.num_len - 1)
					current = *current.pointers[i + 1];
			}
		}

		else if (current.pointers[0] == NULL && current.num_len < n) {	//	u poslednjem sam, ima mesta za first_step
			this->first_step(x);
			flag = false;
		}

		else {	//	dosao sam do poslednjeg i nema mesta za first_step
			if (n % 2 == 0)
				this->new_node_even(x);
			else
				this->new_node_odd(x);



			flag = false;
		}
	}
}
