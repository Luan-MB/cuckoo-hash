#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hash.h"

int *load_array(int size) {

	int *arr;
        int i;	
	
	arr = malloc(sizeof(int) * size);

	if (!arr)
		return NULL;

	for (i=0;i<SIZE;i++)
		arr[i] = -2;
	
	return arr;
}

int h1(int key) {

	int m = SIZE;
	return (key % m);
}

int h2(int key) {
	
	int m = SIZE;
	return floor(m * (key * 0.9 - floor(key * 0.9)));
}

int search_key(int key, t_hash hash) {

	int i;
       
	i = h1(key);
	
	if (hash.T1[i] == -2)
		return -1;
	if (hash.T1[i] == key)
		return i;
	
	i = h2(key);
	if (hash.T2[i] == key)
		return i;
	
	return -1;
}

void insert_key(int key, t_hash hash) {

	
	int i, ki;

	if ((i = search_key(key,hash)) != -1)
		return;

	i = h1(key);

	if(hash.T1[i] == -2 || hash.T1[i] == -1)
		hash.T1[i] = key;
	else {
		ki = hash.T1[i];
		hash.T2[h2(ki)] = ki;
		hash.T1[i] = key;
	}
	return;
}

void remove_key(int key, t_hash hash) {

	int i = search_key(key,hash);

	if (i == -1)
		return;
	if (hash.T1[i] == key) {
		hash.T1[i] = -1;
		return;
	}
	
	if (hash.T2[i] == key) {
		hash.T2[i] = -1;
		return;
	}
	return;
}

void insertion_sort(int *aux, int len) {
	
	int i, j, key;

	for (i=1;i<len;i++) {
		key = aux[i];
		j = i -1;
		while (j>=0 && key<aux[j]) {
			aux[j+1] = aux[j];
			j--;
		}
		aux[j+1] = key;
	}
}

void print_hash(t_hash hash) {

	int i, k;
	int *aux;
	int len = 0;

	aux = load_array(SIZE * 2);

	for (i=0;i<SIZE;i++)
		if (hash.T1[i] != -2 && (hash.T1[i] != -1)) {
			aux[len] = hash.T1[i];
			len++;
		}
	for (i=0;i<SIZE;i++)
		if (hash.T2[i] != -2 && (hash.T2[i] != -1)) {
			aux[len] = hash.T2[i];
			len++;
		}

	insertion_sort(aux,len);

	for (i=0;i<len;i++) {
		k = search_key(aux[i], hash);
		if (hash.T1[k] == aux[i])
			printf("%d,T1,%d\n",aux[i],k);
		else
			printf("%d,T2,%d\n",aux[i],k);
	}
	free(aux);
	return;
}

void free_hash(t_hash hash) {

	free(hash.T1);
	free(hash.T2);
	hash.T1 = NULL;
	hash.T2 = NULL;
	return;
}
