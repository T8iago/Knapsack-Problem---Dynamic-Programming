#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  int p;
  int v;
  int item;
} Mochila; 

void bubbleSort (Mochila *ord, int n) {
  int i, j;
  Mochila ordem;

  for (i = 1; i <= n; i++) {
    for (j = i + 1; j <= n; j++) {
      if (ord[i].v < ord[j].v) {
        ordem = ord[i];
        ord[i] = ord[j];
        ord[j] = ordem;
      }
    }
  }
}

void zerozero (Mochila itens[], int n) {
  itens[0].item = 0;
  itens[0].p = 0;
  itens[0].v = 0;
}

void checarMochila(Mochila itens[], int n, int c, int T[]) {
  int i, b;
  b = c;

  for (i = 1; i <= n; i++) {
    if (b <= 0) {
      break; 
    }
    if (itens[i].p <= b) {
      b -= itens[i].p;
      T[i] = 1;
    }
  }
}

int main(void) {
  int n, c;
  int valorTotal = 0; 

  FILE * fptr;

  fptr = fopen("inputs/input3000.txt", "r");

  if (fptr == NULL) {
    printf("Erro!");
    exit(1);
  }
  
  fscanf(fptr, "%d %d", &c, &n);

  Mochila *itens = (Mochila *)malloc((n + 1) * sizeof(Mochila));
  int *T = (int *)malloc((n + 1) * sizeof(int));

  for (int i = 0; i <= n; i++) {
    T[i] = 0;
  }

  for (int i = 1; i <= n; i++) {
    itens[i].item = i;
  }

  for (int i = 1; i <= n; i++) {
    fscanf(fptr, "%d %d", &itens[i].p, &itens[i].v);
  }

  clock_t inicio = clock();
  
  zerozero(itens, n);
  bubbleSort(itens, n);
  checarMochila(itens, n, c, T);

  for (int i = 1; i <= n; i++) {
    if (T[i] == 1) {
      valorTotal += itens[i].v;
    }
  }
  printf("\n%d ", valorTotal);

  printf("\n");
  for (int i = 1; i <= n; i++) {
    if (T[i] == 1) {
      printf("%d ", itens[i].item);
    }
  }

  clock_t fim = clock ();

  double tempoDecorrido = (double)(fim-inicio) / CLOCKS_PER_SEC;

  printf("\n\nTempo decorrido: %.6f segundos\n", tempoDecorrido );
  
  free(itens);
  free(T);

  return 0;
} 
