#include <stdio.h>
#include <stdlib.h>

//////////////////////////////

#define tam_max_linha (1000)
#define tam_max_subcadeia (255)

//////////////////////////////

#pragma region CABEÇALHO

    //////////////////////////////

    #pragma region Estruturas

        typedef struct lista Lista;
        typedef struct no No;
        typedef struct cbctLista CbctLista;
        typedef struct arvore Arvore;
        typedef struct gerLinhas GerLinhas;

        // sumário: gerência as estruturas de entrada e saída -
        // lista e árvore, respectivamente
        // Como o cabeçote de lista e a árvore tem ponteiro para
        // próximo, ele é capaz de armazenar as listas e árvores
        // correspondentes a cada linha
        struct gerLinhas {
            Arvore *arvore;
            CbctLista *listas;
        };

        // sumário: cabeçote que aponta para início da lista
        struct cbctLista {
            CbctLista *prox;
            Lista *inicio;
        };

        // sumário: lista para receber a sequência de inteiros 
        // da entrada
        struct lista {
            Lista *prox;
            int valor;
        };

        // sumário: árvore que guardará os dados esperados da saída
        // em sua estrutura, como max, pred, alt e os nós cujos
        // níveis permitirão a contagem para a linha de saída.
        // Também armazena a linha de saída correspondente à árvore.
        struct arvore {
            Arvore *prox;
            No *raiz;
            int max;
            int pred;
            int alt;
            char linhaSaida[tam_max_linha];
        };

        // sumário: nó da árvore
        struct no {
            No *direita;
            No *esquerda;
            No *mae;
            int valor;
        };

    #pragma endregion

    //////////////////////////////

    #pragma region Funções

        //////////////////////////////

        #pragma region Cadeia

            char* obterSubstr(char *str, char *separadores);
            char* proxOcorrencia(char *str, char *alvos);

        #pragma endregion

        //////////////////////////////

        #pragma region  Conversões

            int convStrInt(char *cadeia);
            char *convIntStr(int inteiro);

        #pragma endregion

        //////////////////////////////

        #pragma region Matematica

            int expInt(int inteiro, int exp);
            int qntAlgsInt(int inteiro);

        #pragma endregion

    #pragma endregion

    //////////////////////////////

#pragma endregion

int main (void) {

}

#pragma region PRINCIPAL

#pragma endregion

#pragma region AUXILIARES

#pragma endregion