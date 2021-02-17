#include <stdio.h>

typedef struct {

	int *T1;
	int *T2;

} t_hash;

#define SIZE 11

int *load_array(int size);
int h1(int key);
int h2(int key);
int search_key(int key, t_hash hash);
void insert_key(int key, t_hash hash);
void remove_key(int key, t_hash hash);
void insertion_sort(int *aux, int len);
void print_hash(t_hash hash);
void free_hash(t_hash hash);
