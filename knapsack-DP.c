#include <stdio.h>
#include <stdlib.h>

int** mochila_otimizada(int n, int p[], int c, int v[]) {
    int b, j;

     // aloca dinamicamente os vetores da mochila
    int** X = (int**)malloc((n+1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        X[i] = (int*)malloc((c+1) * sizeof(int));
    }

    for (b = 0; b <= c; b++) {
        X[0][b] = 0;
        for (j = 1; j <= n; j++) {
            int x = X[j - 1][b];
            if (b - p[j] >= 0) {
                int y = X[j - 1][b - p[j]] + v[j];
                if (x < y) {
                    x = y;
                }
            }
            X[j][b] = x;
        }
    }

    return X;
}

int* itens_Mochila (int n, int p[], int c, int v[], int** X, int* T) {
  int b, j;
  int z = X[n][c];
  int i;

  //printf ("%d\n", z);
  b = c;
  // analisaremos a matriz iniciando pelo canto inferior direito X[n][c], assim, z comecara como o maior valor
  // tambem aqui começaremos com j=n para analisar a matriz de baixo pra cima, e i seguirá j (talvez i seja inutil)

  //ja que j=i-1, entao
    for (int j = n; j >= 1; j--) {

      // todos esses printf nessa funcao foram criados para visualizacao de testes enquanto nao tava dando certo
      //printf("%d, %d, %d /", z, j, b);

      // veremos se o local acima na matriz é maior que z, ja que se for, então houve uma operação e isso que queremos detectar
      if (z > X[j-1][b]) {
        T[j] = 1;
        //printf("(%d-1), %d, %d ;", z, j, T[i]);
        b = b-p[j];
        z = X[j-1][b];
        if (z == 0) {
          break;
        }
      } else {
        // caso z = ao numero acima, iremos andar uma casa pra cima para fazer a verificacao novamente 
      if (z == X[j-1][b]) {
        z = X[j-1][b];
        T[j] = 0;
        //printf("(%d-2), %d, %d ;", z, j, T[i]);
      }}  
      //printf("\n");
    }

  return T;
}

 // libera os valores da matriz X
void liberar_matriz(int** X, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(X[i]);
    }
    free(X);
}

int main() {
  int n, c;
  int i;

  FILE * fptr;

  fptr = fopen("inputs/input300.txt", "r");

  if (fptr == NULL) {
    printf("Erro!");
    exit(1);
  }

   fscanf(fptr, "%d %d", &c, &n);
  
   // aloca dinamicamente os vetores de peso (p) e valor (v)
  int* p = (int*)malloc((n+1) * sizeof(int));
  int* v = (int*)malloc((n+1) * sizeof(int));
  int* T = (int*)malloc((n+1) * sizeof(int)); // T será o vetor que será guardado os itens que estao dentro da mochila

  // zerar todo o vetor T
  for (int k = 0; k<n+1; k++) {
    T[k] = 0;
  }

   //lê os pesos e os valores
  for (i = 1; i <= n; i++) {
    fscanf(fptr, "%d %d", &p[i], &v[i]);
  }

   // chamar a função mochila_otimizada e recuperar a matriz
  int** matriz = mochila_otimizada(n, p, c, v);

  printf("\nThe biggest possible value is %d \n\n", matriz[n][c]);

  int* vetor_Itens = itens_Mochila(n, p, c, v, matriz, T);

  // aqui vemos a matriz T que guarda binariamente os itens da mochila por local no vetor, por exemplo, se no vetor, no local 2, estiver um item, exibira 1, enquanto no que nao houver nada exibira 0
  //printf("\n\ne os itens na mochila são: ");
  //for (i = 1; i<=n; i++) {
  //  printf("%d ", vetor_Itens[i]);
  //}

  printf("and the itens inside the knapsack are: \n ");
  for (i = 1; i<=n; i++) {
    if (vetor_Itens[i] == 1) {
      printf("%d ", i);
    }
  }
  
  // ver a matriz de peso e de valores
  // printf("\n\n");
  // printf("%d %d \n", c, n);
  // for (i = 1; i <= n; i++) {
  //   printf("%d ", p[i]);
  // }
  // printf("\n");
  // for (i = 1; i <= n; i++) {
  //   printf("%d ", v[i]);
  // }
  
  // caso precise ver a matriz (para comparar com o papel resultados)
  // printf("\n\n");
  // for (int i = 0; i <= (n); i++) {
  //     for (int j = 0; j <= (c); j++) {
  //         printf("%d ", matriz[i][j]);
  //      }
  //     printf("\n");
  // }

   // liberar os vetores alocados dinamicamente
  liberar_matriz(matriz, n + 1);
  free(p);
  free(v);
  free(T);

    return 0;
}
