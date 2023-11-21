#include <iostream>
#include <stdlib.h>

#define vertex int

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A estrutura graph representa um grafo. O campo adj é um ponteiro para a matriz de adjacências do grafo. O campo V contém o número de vértices e o campo A contém o número de arcos do grafo. */

struct graph {
   int V; 
   int A; 
   int **adj; 
};

/* Um Graph é um ponteiro para um graph, ou seja, um Graph contém o endereço de um graph. */

typedef struct graph *Graph;

Graph GRAPHinit( int V);
static int **MATRIXint( int r, int c, int val);
void GRAPHremoveArc( Graph G, vertex v, vertex w);
void GRAPHshow( Graph G);
int UGRAPHseqColoring(Graph G, int *color);


/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GRAPHinit() constrói um grafo com vértices 0 1 .. V-1 e nenhum arco. */

Graph GRAPHinit( int V) { 
   Graph G = (Graph) malloc( sizeof *G);
   G->V = V; 
   G->A = 0;
   G->adj = MATRIXint( V, V, 0);
   return G;
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função MATRIXint() aloca uma matriz com linhas 0..r-1 e colunas 0..c-1. Cada elemento da matriz recebe valor val. */

static int **MATRIXint( int r, int c, int val) { 
   int **m = (int**) malloc( r * sizeof (int *));
   for (vertex i = 0; i < r; ++i) 
      m[i] = (int *) malloc( c * sizeof (int));
   for (vertex i = 0; i < r; ++i)
      for (vertex j = 0; j < c; ++j)
         m[i][j] = val;
   return m;
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GRAPHinsertArc() insere um arco v-w no grafo G. A função supõe que v e w são distintos, positivos e menores que G->V. Se o grafo já tem um arco v-w, a função não faz nada. */

void GRAPHinsertArc( Graph G, vertex v, vertex w) { 
   if (G->adj[v][w] == 0) {
      G->adj[v][w] = 1; 
      G->A++;
   }
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GRAPHremoveArc() remove do grafo G o arco v-w. A função supõe que v e w são distintos, positivos e menores que G->V. Se não existe arco v-w, a função não faz nada. */

void GRAPHremoveArc( Graph G, vertex v, vertex w) { 
   if (G->adj[v][w] == 1) {
      G->adj[v][w] = 0; 
      G->A--;
   }
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GRAPHshow() imprime, para cada vértice v do grafo G, em uma linha, todos os vértices adjacentes a v. */

void GRAPHshow( Graph G) { 
   for (vertex v = 0; v < G->V; ++v) {
      printf( "%2d:", v);
      for (vertex w = 0; w < G->V; ++w)
         if (G->adj[v][w] == 1) 
            printf( " %2d", w);
      printf( "\n");
   }
}

int UGRAPHseqColoring(Graph G, int *color) {
   int k = 0;

   for (vertex v = 0; v < G->V; ++v) {
      color[v] = -1;
   }

   for (vertex v = 0; v < G->V; ++v) {
      bool available[100];
      int c;

      for (c = 0; c < k; ++c) {
         available[c] = true;
      }

      for (vertex w = 0; w < G->V; ++w) {
         if (G->adj[v][w] == 1 && color[w] != -1) {
            available[color[w]] = false;
         }
      }

      c = 0;
      while (c < k && !available[c]) {
         ++c;
      }

      if (c < k) {
         color[v] = c;
      } else {
         color[v] = k++;
      }
   }

   return k;
}

int main(void) { 
    // Criar um grafo com 5 vértices
    Graph G = GRAPHinit(4);

    // Inserir alguns arcos no grafo
    GRAPHinsertArc(G, 0, 1);
    GRAPHinsertArc(G, 0, 2);
    GRAPHinsertArc(G, 2, 3);
    GRAPHinsertArc(G, 2, 0);
    GRAPHinsertArc(G, 3, 2);
    GRAPHinsertArc(G, 3, 1);
    GRAPHinsertArc(G, 1, 0);
    GRAPHinsertArc(G, 1, 3);
    
    // Mostrar o grafo
    std::cout << "Grafo G:\n";
    GRAPHshow(G);

    int color[5];
    int numColors = UGRAPHseqColoring(G, color);

    // Mostrar a coloração
    std::cout << "\nResultado de coloracao sequencial: \n";
    for (vertex v = 0; v < G->V; ++v) {
        std::cout << "Vertice " << v << ": Cor " << color[v] << "\n";
    }

    std::cout << "\nQuantidade de cores utilizadas: " << numColors << "\n";

    // Liberar a memória alocada para o grafo
    // (lembre-se de liberar a memória alocada para a matriz de adjacências)
    for (vertex i = 0; i < G->V; ++i)
        free(G->adj[i]);
    free(G->adj);
    free(G);

    return 0;
}