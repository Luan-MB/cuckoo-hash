// Luan Machado Bernardt | GRR20190363

#include <stdio.h>
#include "hash.h"

int main () {

	t_hash hash;
	int num;
	char c;
	
	hash.T1 = load_array(SIZE);
	hash.T2 = load_array(SIZE);

	if (!hash.T1 || !hash.T2) {
		perror("Falaha ao alocar na memória");
		return 1;
	}
	// Função que lê stdin até encontrar o fim do arquivo (EOF ou ctrl+d)
	while ((c = getchar()) != EOF) {
		switch (c) {
			// Se ler i, lê-se um espaço em branco e em seguida o número a ser inserido
			case 'i':
				c = getchar();
				scanf("%d",&num);
				insert_key(num,hash);
				break;
			// Se r, l~e-se um espaço em branco e em seguida o número a ser removido
			case 'r':
				c = getchar();
				scanf("%d",&num);
				remove_key(num,hash);
				break;
		}
	}
	print_hash(hash);
	free_hash(hash);
	return 0;
}
