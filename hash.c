// Luan Machado Bernardt | GRR20190363

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hash.h"

// Função que inicia e retorna um array de tamanho size
int *load_array(int size) {

	int *arr;
        int i;	
	
	arr = malloc(sizeof(int) * size);

	if (!arr)
		return NULL;
	// Preenche todos os espaços do vetor com -2
	for (i=0;i<SIZE;i++)
		arr[i] = -2;
	
	return arr;
}

// Função de endereçamento para o priemrio array do hash
int h1(int key) {

	int m = SIZE;
	return (key % m);
}

// Função de endereçamento para o segundo array do hash
int h2(int key) {
	
	int m = SIZE;
	return floor(m * (key * 0.9 - floor(key * 0.9)));
}

// Função que busca chave(key) nos arrays do hash, retorna -1, se não encontrou, e o indice(i), se encontrado
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

// Função que insere a chave(key) ao hash
void insert_key(int key, t_hash hash) {

	
	int i, ki;
	
	// Se a chave ja existir no hash, retorna-se
	if ((i = search_key(key,hash)) != -1)
		return;

	i = h1(key);
	// Tenta-se inserir key em T1[i]
	if(hash.T1[i] == -2 || hash.T1[i] == -1)
		hash.T1[i] = key;
	// Se T1[i] estiver ocupado, calcula-se h2(T1[i]) e move-se T1[i] para T2
	// Insere-se a chave em T1[i]
	else {
		ki = hash.T1[i];
		hash.T2[h2(ki)] = ki;
		hash.T1[i] = key;
	}
	return;
}

// Função que remove a chave(key) do hash
void remove_key(int key, t_hash hash) {

	int i = search_key(key,hash);
	
	// Busca-se a chave(key) no hash
	// Se não encontrou(-1), retorna-se
	if (i == -1)
		return;
	// Se encontrada em T1, a chave é removida e sua posição em T1 é marcada com -1(sinal de exclusão)
	if (hash.T1[i] == key) {
		hash.T1[i] = -1;
		return;
	}
	// Se encontrada em T2, a chave é removida e sua posição em T2é marca com -2(sinal de vazio)
	if (hash.T2[i] == key) {
		hash.T2[i] = -2;
		return;
	}
	return;
}

// Função que ordena um vetor(aux) de tamanho len
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

// Função que imprime as chaves presentes no hash em ordem crescente
void print_hash(t_hash hash) {

	int i, k;
	int *aux;
	int len = 0;

	aux = load_array(SIZE * 2);
	// Varre ambas as tabelas de hash e coloca as chaves encontradas em aux
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
	// Ordena-se aux e mordem crescente
	insertion_sort(aux,len);
	// Busca-se os elementos de aux no hash, imprimindo a chave, sua tabela e indice
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
// Função que desaloca as tabelas de hash da memória
void free_hash(t_hash hash) {

	free(hash.T1);
	free(hash.T2);
	hash.T1 = NULL;
	hash.T2 = NULL;
	return;
}
