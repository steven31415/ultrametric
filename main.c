#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {

	struct node* left;
	struct node* right;
	struct node* parent;
	int height;
};

void freeTree(struct node* root) {

	if (!root) {
		return;
	}
	
	freeTree(root->left);
	freeTree(root->right);
	free(root);
}

void printMatrix(int n, int M[n][n]){

	int max_val = 0;
	for(int i = 0; i < n; ++i) {
	    for(int j = 0; j < n; ++j) {
	        if (M[i][j] > max_val) {
	        	max_val = M[i][j];
	        }
	    }
	}

	int digit_count = 0;
	while (max_val != 0) {
		max_val /= 10;
		digit_count++;
	}

	for(int i = 0; i < n; ++i) {
	    for(int j = 0; j < n; ++j) {
	        printf("%*d  ", digit_count, M[i][j]);
	    }
	    printf("\n");
	}
	printf("\n");
}

void randomUltrametric(int n, int M[n][n]) {

	// Construct random tree

	struct node *C[n];
	struct node *L[n];
	int C_size = n;

	for (int i = 0; i < n; ++i) {
		struct node* leaf = malloc(sizeof(struct node));
		leaf->left = NULL;
		leaf->right = NULL;
		leaf->height = 0;

		C[i] = leaf;
		L[i] = leaf;
	}

	while (C_size > 1) {
		int r1, r2, r_min, r_max;

		r1 = rand() % C_size;

		do {
			r2 = rand() % C_size;
		}
		while (r1 == r2);

		struct node* new_node = malloc(sizeof(struct node));
		new_node->left = C[r1];
		new_node->right = C[r2];
		new_node->parent = NULL;
		new_node->height = max(C[r1]->height, C[r2]->height) + 1;

		C[r1]->parent = new_node;
		C[r2]->parent = new_node;

		if (r1 < r2) {
			r_min = r1;
			r_max = r2;
		}
		else {
			r_min = r2;
			r_max = r1;
		}

		C[r_min] = new_node;
		C[r_max] = C[C_size - 1];

		C_size--;
	}

	struct node* root = C[0];


	// Contruct corresponding distance matrix

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			struct node* p = L[i];
			struct node* q = L[j];

			while (p != q) {
				if (p->height < q->height) {
					p = p->parent;
				}
				else {
					q = q->parent;
				}
			}

			M[i][j] = p->height;
		}
	}


	// Delete tree

	freeTree(root);
}

int main(int argc, char* argv[]) {

	int n = atoi(argv[1]);
	int M[n][n];

	srand(time(NULL));
	randomUltrametric(n, M);
	printMatrix(n, M);
}