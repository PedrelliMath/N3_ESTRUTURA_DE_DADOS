#include <iostream>
#include <stdlib.h>
#include <cstdlib>

#ifdef _WIN32
    #define CLEAR_COMMAND "cls" // Comando para limpar console no Windows
#else
    #define CLEAR_COMMAND "clear" // Comando para limpar console no Linux
#endif

void clearConsole() {
    system(CLEAR_COMMAND);
}

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
void mainMenu(void);
void submenugraphs(void);
void submenugraphscolor(void);
void showgraphsoptions(void);
void sequencialColoring(void);

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

Graph G1 = GRAPHinit(4);
Graph G2 = GRAPHinit(10);
Graph G3 = GRAPHinit(17);

void mainMenu(void){
    clearConsole();

    int option = -1;
    do{
        clearConsole();
        std::cout << "1.\tImprimir grafos\n2.\tColorir Grafos\n0.\tSair\n";
        std::cin >> option;
        switch(option){
            case 1:
                submenugraphs();
                break;
            case 2:
                submenugraphscolor();
                break;
            case 0: 
                break;
            default:
                std::cout << "Opcao invalida...\n";
                break;
        }
    }while(option != 0);
}

void submenugraphs(void){
    clearConsole();

    int option = -1;
    do{
        showgraphsoptions();
        std::cin >> option;
        switch(option){
            case 1:
                std::cout << "Grafo G1:\n";
                GRAPHshow(G1);
                break;
            case 2:
                std::cout << "Grafo G2:\n";
                GRAPHshow(G2);
                break;
            case 3:
                std::cout << "Grafo G3:\n";
                GRAPHshow(G3);
                break;
            case 0:
                break;
            default:
                std::cout << "Opcao invalida...\n";
                break;
        }
    }while(option != 0);
}

void showgraphsoptions(void){
    std::cout << "Selecione o grafo: \n";
    std::cout << "1.\tGrafo Exemplo 1\n2.\tGrafo Exemplo 2\n3.\tGrafo Exemplo 3\n0.\tVoltar\n";
}

void submenugraphscolor(void){
    clearConsole();

    std::cout << "Escolha um algoritimo: \n";
    int option = -1;
    do{
        std::cout << "1.\tAlgoritimo Sequencial\n0.\tVoltar\n";
        std::cin >> option;
        switch(option){
            case 1: 
                sequencialColoring();
                break;
            case 0:
                break;
            default:
                std::cout << "Opcao invalida...\n";
                break;
        }   

    }while(option != 0);
}

void sequencialColoring(void){
    int option = -1;
    do{
        showgraphsoptions();
        std::cin >> option;
        switch(option){
            case 1:
            {
                int color1[5];
                int numColors = UGRAPHseqColoring(G1, color1);
                std::cout << "\nResultado de coloracao sequencial: \n";
                for (vertex v = 0; v < G1->V; ++v) {
                std::cout << "Vertice " << v << ": Cor " << color1[v] << "\n";
                }
                std::cout << "\nQuantidade de cores utilizadas: " << numColors << "\n";
                break;
            }
            case 2:
            {
                int color2[10];
                int numColors2 = UGRAPHseqColoring(G2, color2);
                std::cout << "\nResultado de coloracao sequencial: \n";
                for (vertex v = 0; v < G2->V; ++v) {
                std::cout << "Vertice " << v << ": Cor " << color2[v] << "\n";
                }
                std::cout << "\nQuantidade de cores utilizadas: " << numColors2 << "\n";
                break;
            }
            case 3:
            {
                int color3[17];
                int numColors3 = UGRAPHseqColoring(G3, color3);
                std::cout << "\nResultado de coloracao sequencial: \n";
                for (vertex v = 0; v < G3->V; ++v) {
                std::cout << "Vertice " << v << ": Cor " << color3[v] << "\n";
                }
                std::cout << "\nQuantidade de cores utilizadas: " << numColors3 << "\n";
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Opcao invalida...\n";
                break;
        }
    }while(option != 0);
}

int main(void) { 

    // Criar arestas grafo exemplo 1
    GRAPHinsertArc(G1, 0, 1);
    GRAPHinsertArc(G1, 0, 3);
    GRAPHinsertArc(G1, 1, 0);
    GRAPHinsertArc(G1, 1, 2);
    GRAPHinsertArc(G1, 2, 1);
    GRAPHinsertArc(G1, 2, 3);
    GRAPHinsertArc(G1, 3, 0);
    GRAPHinsertArc(G1, 3, 2);

    // Criar arestas grafo exemplo 2
    GRAPHinsertArc(G2, 0, 1);
    GRAPHinsertArc(G2, 0, 2);
    GRAPHinsertArc(G2, 0, 5);
    GRAPHinsertArc(G2, 0, 8);
    GRAPHinsertArc(G2, 0, 7);
    GRAPHinsertArc(G2, 1, 0);
    GRAPHinsertArc(G2, 1, 2);
    GRAPHinsertArc(G2, 1, 9);
    GRAPHinsertArc(G2, 2, 0);
    GRAPHinsertArc(G2, 2, 1);
    GRAPHinsertArc(G2, 2, 4);
    GRAPHinsertArc(G2, 2, 8);
    GRAPHinsertArc(G2, 2, 3);
    GRAPHinsertArc(G2, 3, 2);
    GRAPHinsertArc(G2, 3, 9);
    GRAPHinsertArc(G2, 3, 6);
    GRAPHinsertArc(G2, 4, 2);
    GRAPHinsertArc(G2, 4, 8);
    GRAPHinsertArc(G2, 4, 7);
    GRAPHinsertArc(G2, 4, 6);
    GRAPHinsertArc(G2, 5, 0);
    GRAPHinsertArc(G2, 5, 7);
    GRAPHinsertArc(G2, 5, 6);
    GRAPHinsertArc(G2, 6, 3);
    GRAPHinsertArc(G2, 6, 4);
    GRAPHinsertArc(G2, 6, 5);
    GRAPHinsertArc(G2, 7, 0);
    GRAPHinsertArc(G2, 7, 9);
    GRAPHinsertArc(G2, 7, 4);
    GRAPHinsertArc(G2, 7, 5);
    GRAPHinsertArc(G2, 8, 0);
    GRAPHinsertArc(G2, 8, 2);
    GRAPHinsertArc(G2, 8, 4);
    GRAPHinsertArc(G2, 9, 1);
    GRAPHinsertArc(G2, 9, 3);
    GRAPHinsertArc(G2, 9, 7);

    // Criar arestas grafo exemplo 3
    GRAPHinsertArc(G3, 0, 1);
    GRAPHinsertArc(G3, 0, 2);
    GRAPHinsertArc(G3, 0, 14);
    GRAPHinsertArc(G3, 1, 0);
    GRAPHinsertArc(G3, 1, 2);
    GRAPHinsertArc(G3, 1, 13);
    GRAPHinsertArc(G3, 1, 14);
    GRAPHinsertArc(G3, 2, 0);
    GRAPHinsertArc(G3, 2, 1);
    GRAPHinsertArc(G3, 2, 3);
    GRAPHinsertArc(G3, 2, 4);
    GRAPHinsertArc(G3, 2, 12);
    GRAPHinsertArc(G3, 2, 13);
    GRAPHinsertArc(G3, 2, 14);
    GRAPHinsertArc(G3, 2, 15);
    GRAPHinsertArc(G3, 3, 2);
    GRAPHinsertArc(G3, 3, 4);
    GRAPHinsertArc(G3, 3, 13);
    GRAPHinsertArc(G3, 3, 15);
    GRAPHinsertArc(G3, 3, 11);
    GRAPHinsertArc(G3, 4, 2);
    GRAPHinsertArc(G3, 4, 3);
    GRAPHinsertArc(G3, 4, 5);
    GRAPHinsertArc(G3, 4, 6);
    GRAPHinsertArc(G3, 4, 9);
    GRAPHinsertArc(G3, 4, 10);
    GRAPHinsertArc(G3, 4, 16);
    GRAPHinsertArc(G3, 5, 4);
    GRAPHinsertArc(G3, 5, 6);
    GRAPHinsertArc(G3, 5, 10);
    GRAPHinsertArc(G3, 5, 11);
    GRAPHinsertArc(G3, 6, 4);
    GRAPHinsertArc(G3, 6, 5);
    GRAPHinsertArc(G3, 6, 7);
    GRAPHinsertArc(G3, 6, 8);
    GRAPHinsertArc(G3, 6, 9);
    GRAPHinsertArc(G3, 6, 10);
    GRAPHinsertArc(G3, 6, 16);
    GRAPHinsertArc(G3, 7, 6);
    GRAPHinsertArc(G3, 7, 8);
    GRAPHinsertArc(G3, 7, 9);
    GRAPHinsertArc(G3, 7, 10);
    GRAPHinsertArc(G3, 8, 6);
    GRAPHinsertArc(G3, 8, 7);
    GRAPHinsertArc(G3, 8, 9);
    GRAPHinsertArc(G3, 9, 4);
    GRAPHinsertArc(G3, 9, 6);
    GRAPHinsertArc(G3, 9, 7);
    GRAPHinsertArc(G3, 9, 8);
    GRAPHinsertArc(G3, 9, 10);
    GRAPHinsertArc(G3, 10, 4);
    GRAPHinsertArc(G3, 10, 5);
    GRAPHinsertArc(G3, 10, 6);
    GRAPHinsertArc(G3, 10, 7);
    GRAPHinsertArc(G3, 10, 9);
    GRAPHinsertArc(G3, 10, 11);
    GRAPHinsertArc(G3, 11, 3);
    GRAPHinsertArc(G3, 11, 5);
    GRAPHinsertArc(G3, 11, 10);
    GRAPHinsertArc(G3, 11, 12);
    GRAPHinsertArc(G3, 11, 15);
    GRAPHinsertArc(G3, 11, 16);
    GRAPHinsertArc(G3, 12, 2);
    GRAPHinsertArc(G3, 12, 11);
    GRAPHinsertArc(G3, 12, 13);
    GRAPHinsertArc(G3, 12, 15);
    GRAPHinsertArc(G3, 13, 1);
    GRAPHinsertArc(G3, 13, 2);
    GRAPHinsertArc(G3, 13, 3);
    GRAPHinsertArc(G3, 13, 12);
    GRAPHinsertArc(G3, 13, 14);
    GRAPHinsertArc(G3, 13, 15);
    GRAPHinsertArc(G3, 14, 0);
    GRAPHinsertArc(G3, 14, 1);
    GRAPHinsertArc(G3, 14, 2);
    GRAPHinsertArc(G3, 14, 13);
    GRAPHinsertArc(G3, 15, 2);
    GRAPHinsertArc(G3, 15, 3);
    GRAPHinsertArc(G3, 15, 11);
    GRAPHinsertArc(G3, 15, 12);
    GRAPHinsertArc(G3, 15, 13);
    GRAPHinsertArc(G3, 15, 16);
    GRAPHinsertArc(G3, 16, 4);
    GRAPHinsertArc(G3, 16, 15);
    GRAPHinsertArc(G3, 16, 11);
    GRAPHinsertArc(G3, 16, 6);

    mainMenu();

    for (vertex i = 0; i < G1->V; ++i) {
        free(G1->adj[i]);
    }
    free(G1->adj);
    free(G1);

    for (vertex i = 0; i < G2->V; ++i) {
        free(G2->adj[i]);
    }
    free(G2->adj);
    free(G2);

    for (vertex i = 0; i < G3->V; ++i) {
        free(G3->adj[i]);
    }
    free(G3->adj);
    free(G3);

    return 0;
}
