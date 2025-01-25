#include <stdio.h>
#include <stdlib.h>

//////////////////////////////

#define tam_max_linha (1000)
#define tam_max_substr (255)

//////////////////////////////

#pragma region CABEÇALHO

    //////////////////////////////

    #pragma region Estruturas

        typedef struct cbctGerLinha CbctLinha;
        typedef struct itemLista ItemLista;
        typedef struct no No;
        typedef struct lista Lista;
        typedef struct arvore Arvore;
        typedef struct linha Linha;

        struct cbctGerLinha {
            Linha *inicioLinha;
            Linha *fimLinha;
        };

        // sumário: gerência as estruturas de entrada e saída -
        // lista e árvore, respectivamente
        // Como o cabeçote de lista e a árvore tem ponteiro para
        // próximo, ele é capaz de armazenar as listas e árvores
        // correspondentes a cada linha
        struct linha {
            Linha *prox;
            Arvore *arvore;
            Lista *lista;
            char linhaSaida[tam_max_linha];
        };

        // sumário: cabeçote que aponta para início da lista
        struct lista {
            ItemLista *inicio;
            ItemLista *fim;
        };

        // sumário: lista para receber a sequência de inteiros 
        // da entrada
        struct itemLista {
            ItemLista *prox;
            int valor;
        };

        // sumário: árvore que guardará os dados esperados da saída
        // em sua estrutura, como max, pred, alt e os nós cujos
        // níveis permitirão a contagem para a linha de saída.
        // Também armazena a linha de saída correspondente à árvore.
        struct arvore {
            No *raiz;
            int max;
            int pred;
            int alt;
        };

        // sumário: nó da árvore
        struct no {
            No *direita;
            No *esquerda;
            No *mae;
            int valor;
            int altura; // facilitar saída
        };

    #pragma endregion

    //////////////////////////////

    #pragma region Funções

        //////////////////////////////

        #pragma region Inicializar

            // ger
            Linha *inicializarLinha();
            // arvore
            Arvore *inicializarArvore();
            No *inicializarNo(int valor);
            // lista
            Lista *inicializarLista();
            ItemLista *inicializarItemLista(int valor);

        #pragma endregion

        //////////////////////////////

        #pragma region Adicionar

            // ger
            void adicionarLinha(CbctLinha *cbct, Linha *novaLinha);
            // arvore
            void adicionarNoSubarv(No *noAtual, No *novoNo);
            void adicionarNoArv(Arvore *arv, No *novoNo);
            // lista
            void adicionarItemLista(Lista *lista, ItemLista *item);

        #pragma endregion

        //////////////////////////////

        #pragma region String

            char* obterSubstr(char *str, char *separadores);
            char* proxOcorrencia(char *str, char *alvos);
            int checarCharInt(char c);

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

    return 0;

}

#pragma region PRINCIPAL

//////////////////////////////

    #pragma region Inicializar

            // ger
            CbctLinha *inicializarCbctLinha() {
                CbctLinha *novoCbct = (CbctLinha *) malloc(sizeof(CbctLinha));
                novoCbct->fimLinha = novoCbct->inicioLinha = NULL;
                return novoCbct;
            }

            // Sumário: inicializa novo gerente de linhas
            // Parâmetros: <void>
            // Retorno: ponteiro para novo gerente
            Linha *inicializarLinha() {
                Linha *novaLinha = (Linha *) malloc(sizeof(Linha));
                novaLinha->arvore = NULL;
                novaLinha->lista = NULL;
                return novaLinha;
            }

            // arvore
            // Sumário: inicializa nova árvore
            // Parâmetros: <void>
            // Retorno: ponteiro para nova árvore
            Arvore *inicializarArvore() {
                Arvore *novaArvore = (Arvore *) malloc(sizeof(Arvore));
                novaArvore->raiz = NULL;
                novaArvore->max = 0;
                novaArvore->alt = 0;
                novaArvore->pred = 0;
                return novaArvore;
            }

            // Sumário: inicializa novo nó
            // Parâmetros: <valor: valor do novo nó>
            // Retorno: ponteiro para novo nó
            No *inicializarNo(int valor) {
                No *novoNo = (No *) malloc(sizeof(No));
                novoNo->altura = 0;
                novoNo->valor = valor;
                novoNo->direita = NULL;
                novoNo->esquerda = NULL;
                novoNo->mae = NULL;
                return novoNo;
            }

            // lista
            // Sumário: inicializa nova lista
            // Parâmetros: <void>
            // Retorno: ponteiro para nova lista
            Lista *inicializarLista() {
                Lista *novaLista = (Lista *) malloc(sizeof(Lista));
                novaLista->inicio = NULL;
                return novaLista;
            }

            // Sumário: inicializa novo item de lista
            // Parâmetros: <valor: valor do item>
            // Retorno: ponteiro para novo item
            ItemLista *inicializarItemLista(int valor) {
                ItemLista *novoItem = (ItemLista *) malloc(sizeof(ItemLista));
                novoItem->valor = valor;
                novoItem->prox = NULL;
                return novoItem;
            }

    #pragma endregion

    //////////////////////////////

    #pragma region Adicionar

        /*
        // ger
        // Sumário: Adiciona uma lista de itens ao gerente de linhas
        // Parâmetros: <ger: gerente a ter lista adicionada> e <lista: 
        // lista a ser adicionada>
        // Retorna: <void>
        void adicionarLista(Linha *linha, Lista *lista) 
        {
            if (ger->inicioListas == NULL)
                ger->inicioListas = ger->fimListas = lista;
            else 
            {
                ger->fimListas->prox = lista;
                ger->fimListas = lista;
            }
        }
        */

        /*
        // Sumário: Adiciona uma árvore ao gerente de linhas
        // Parâmetros: <ger: gerente a ter a árvore adicionada> e <arv:
        // árvore a ser adicionada>
        // Retorna: <void>
        void adicionarArvore(GerLinhas *ger, Arvore *arv) 
        {
            if (ger->inicioArvores == NULL)
                ger->inicioArvores = ger->fimArvores = arv;
            else 
            {
                ger->fimArvores->prox = arv;
                ger->fimArvores = arv;
            }
        }
        */

        void adicionarLinha(CbctLinha *cbct, Linha *novaLinha)
        {
            if (cbct->inicioLinha == NULL)
                cbct->inicioLinha = cbct->fimLinha = novaLinha;
            else 
            {
                cbct->fimLinha->prox = novaLinha;
                cbct->fimLinha = novaLinha;
            }
        }

        // arvore
        // Sumário: Adiciona um novo nó à árvore
        // Parâmetros: <arv: árvore na qual ocorrerá a inserção> e 
        // <novoNo: nó a ser inserido>
        // Retorna: <void>
        void adicionarNoArv(Arvore *arv, No *novoNo) 
        {
            if (arv->raiz == NULL)
                arv->raiz = novoNo;
            else 
                adicionarNoSubarv(arv->raiz, novoNo);
        }

        // Sumário: Recursão auxiliar para adicionar nó na subárvore
        // Parâmetros: <No: no atual da subárvore> e <novoNo: nó a 
        // ser inserido>
        // Retorna: <void>
        void adicionarNoSubarv(No *noAtual, No *novoNo) 
        {
            novoNo->mae = noAtual;
            novoNo->altura += 1;
            
            if (noAtual->valor > novoNo->valor) 
            {
                if (noAtual->esquerda != NULL)
                    adicionarNoSubarv(noAtual->esquerda, novoNo);
                else
                    noAtual->esquerda = novoNo;
            }
            else 
            {
                if (noAtual->direita != NULL)
                    adicionarNoSubarv(noAtual->direita, novoNo);
                else 
                    noAtual->direita = novoNo;
            }
        }

        // lista
        // Sumário: adiciona um item à lista
        // Parâmetros: <lista: lista na qual ocorrerá a inserção> e 
        // <item: item a ser inserido>
        // Retorna: <void>
        void adicionarItemLista(Lista *lista, ItemLista *item) 
        {
            if (lista->inicio == NULL)
                lista->inicio = lista->fim = item;
            else 
            {
                lista->fim->prox = item;
                lista->fim = item;
            }
        }

    #pragma endregion

//////////////////////////////

#pragma endregion

#pragma region AUXILIARES

    //////////////////////////////

    #pragma region String

        //////////////////////////////

        // Sumário: obtém a substring de início igual ao ponteiro de caracter
        // passado e final fim da cadeia ou primeira ocorrência de um dos 
        // separadores
        // Parâmetros: <str: ponteiro para o início da string> e <separadores:
        // string dos separadores, caracteres que finalizam a substring além do
        // '\0'
        // Retorna: ponteiro para a substring formada.
        char* obterSubstr(char *str, char *separadores) 
        {
            static char substr[tam_max_substr];
            char *idx = substr;
            int i, j;

            for(i = 0; str[i] != '\n'; i++) 
            {
                for (j = 0; separadores[j] != '\0'; j++)
                    if (separadores[j] == str[i])
                        break;

                idx[i] = str[i];
            }

            return substr;
        }

        //////////////////////////////

        // Sumário: busca pela próxima ocorrência de certos alvos
        // em uma string e retorna o seu ponteiro
        // Parâmetros: <str: string alvo> <alvos: caracteres que finalizarão
        // a busca>
        // Retorna: <char *: ponteiro para a primeira ocorrência de um dos alvos>
        char* proxOcorrencia(char *str, char *alvos) 
        {
            char *idx = str;
            int i, j;
            
            // para cara char da entrada
            for (i = 0; str[i] != '\0'; i++)
                // verifica por igualdade com algum alvo
                for (j = 0; alvos[j] != '\0'; j++)
                    if (alvos[j] == str[i])
                        break;    

            // retorna ponteiro da primeira ocorrência 
            // de um dos alvos ou '\0'
            return &idx[i]; 
        }

        int checarCharInt(char c){
            if (c > 47 && c < 58)
                return 1;
            else 
                return 0;
        }

        //////////////////////////////

    #pragma endregion

    //////////////////////////////

    #pragma region Conversões

        //////////////////////////////

        // Sumário: converte um texto para seu equivalente numérico inteiro
        // Parâmetros: <str: indexador da string a ser convertida>
        // Retorna: <int: numero resultante>
        int convStrInt(char* str)
        {
            // propriedades
            int inteiro = 0;
            int sinal = 1;
            int i = 0;

            // se for negativo
            if (str[i] == '-')
            {
                sinal = -1; 
                i++;
            }

            // enquanto  não encontrar o final da linha
            while (checarCharInt(*str))
            {
                inteiro *= 10; // incrementa o número de algarismos e ordem de grandeza
                inteiro += *str - 48;  // atribui o novo algarismo em sua casa atual
                i++; // incrementa o indexador
            }

            inteiro *= sinal;

            return inteiro; // resultado
        }

        //////////////////////////////

    #pragma endregion

    #pragma region Matematica

        //////////////////////////////

        // Sumário: Obtém a quantidade de algarismos presentes em um número
        // inteiro
        // Parâmetros: <inteiro: número cujos algarismos devem ser contabilizados>
        // Retorna: <int: quantidade de algarismos>
        int qntAlgsInt(int inteiro)
        {
            static int qntAlgs;

            if (inteiro == 0)
                return 1;
            else 
                for (qntAlgs = 0; inteiro != 0; qntAlgs++)
                    inteiro /= 10;

            return qntAlgs;
        }

        // Sumário: eleva um determinado número inteiro por um expoente também inteiro
        // Parâmetros: <inteiro: número a ser elevado, base> e <expoente>
        // Retorna: <int: resultado da exponencialização>
        int expInt(int inteiro, int exp)
        {
            int resultado = inteiro;
            if (exp == 0)
                return 1; // todo número ^0 é 1
            else if (exp < 0)
                return -1; // erro
            else // eleve normalmente
                for (; exp > 1; exp--)
                    resultado *= inteiro;

            return resultado;
        }

        // Sumário: Converte um inteiro para uma cadeia de caracteres
        // com seu conteúdo
        // Parâmetros: <inteiro: número inteiro a ser lido>
        // Retorna: <char *: ponteiro para a cadeia resultante>
        char* convIntStr(int inteiro)
        {
            static char str[tam_max_substr];
            char *idx = str;
            int numGrandezaAtual;

            if (inteiro < 0)
            {
                *(idx) = '-';
                inteiro *= -1;
                idx += sizeof(char);
            }

            for (int numAlgs = qntAlgsInt(inteiro); numAlgs > 0; numAlgs--)
            {
                numGrandezaAtual = inteiro / (expInt(10, numAlgs - 1));
                *(idx) = numGrandezaAtual + 48;
                inteiro -= numGrandezaAtual * expInt(10, numAlgs - 1);
                idx += sizeof(char);
            }
            *(idx) = '\0';

            return str;
        }

        //////////////////////////////

    #pragma endregion

    //////////////////////////////

#pragma endregion

//////////////////////////////