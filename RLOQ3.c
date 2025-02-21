#include <stdio.h>
#include <stdlib.h>

//////////////////////////////

#define tam_max_linha (1000)
#define tam_max_substr (255)
#define FIM_LINHA (-1)

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

        struct arvore {
            No *raiz;
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
            CbctLinha *inicializarCbctLinha() ;
            Linha *inicializarLinha(Lista *lista, Arvore *arv);
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
        
        #pragma region Remover
    
            void removerNoArv(Arvore *arv, int chave);

        #pragma endregion

        //////////////////////////////

        #pragma region Atribuir

            // linha
            void atribuirCbctLinha(CbctLinha *linha);
            void atribuirSaidaLinha(Linha *linha);
            // arvore
            void atribuirListaArv(Lista *lista, Arvore *arv);

        #pragma endregion

        //////////////////////////////

        #pragma region Busca

            No *buscarSucessor(No *subArv);
            No *buscarNoArv(Arvore *arv, int chave);
            No *buscarNoSubarv(No *noAtual, int chave);

        #pragma endregion

        //////////////////////////////

        #pragma region String

            // principal
            void lerComandos(Lista *lista, char *idxStr);
            void lerTodasLinhas(CbctLinha *cbctLinha, FILE *entrada);
            void escreverSaida(CbctLinha *cbctLinha,FILE *saida);
            char *escreverSaidaLinha(Linha *linha);
            // auxiliares
            int preencherStr(char *cadeia, char *conteudo);
            char* obterSubstr(char *str, char *separadores);
            int proxOcorrencia(char *str, char *alvos);
            int checarCharInt(char c);
            char proxCharStr(char *cadeia, char *separadores, int intervalo);
            void printarArvoreOrdenada(No *no, char **idx);

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

//////////////////////////////

#pragma region Main

    int main (void) 
    {

        CbctLinha *cbctLinha = inicializarCbctLinha();
        FILE *entrada = fopen("L2Q3.in", "r");
        FILE *saida = fopen("L2Q3.out", "w");

        if (entrada == NULL)
        {
            printf("Falha ao ler ou entrada\n");
            return EXIT_FAILURE;    
        }

        if (saida == NULL)
        {
            printf("Falha ao designar arquivo de saída\n");
            return EXIT_FAILURE;
        }

        lerTodasLinhas(cbctLinha, entrada);

        atribuirCbctLinha(cbctLinha);

        escreverSaida(cbctLinha, saida);

        return EXIT_SUCCESS;
    }

#pragma endregion

//////////////////////////////


#pragma region PRINCIPAL

//////////////////////////////

    #pragma region Inicializar

            // ger
            CbctLinha *inicializarCbctLinha() {
                CbctLinha *novoCbct = (CbctLinha *) malloc(sizeof(CbctLinha));
                novoCbct->fimLinha = novoCbct->inicioLinha = NULL;
                return novoCbct;
            }

            Linha *inicializarLinha(Lista *lista, Arvore *arv) {
                Linha *novaLinha = (Linha *) malloc(sizeof(Linha));
                novaLinha->arvore = arv;
                novaLinha->lista = lista;
                return novaLinha;
            }

            Arvore *inicializarArvore() {
                Arvore *novaArvore = (Arvore *) malloc(sizeof(Arvore));
                novaArvore->raiz = NULL;
                return novaArvore;
            }

            No *inicializarNo(int valor) {
                No *novoNo = (No *) malloc(sizeof(No));
                novoNo->altura = 0;
                novoNo->valor = valor;
                novoNo->direita = NULL;
                novoNo->esquerda = NULL;
                novoNo->mae = NULL;
                return novoNo;
            }

            Lista *inicializarLista() {
                Lista *novaLista = (Lista *) malloc(sizeof(Lista));
                novaLista->inicio = NULL;
                return novaLista;
            }

            ItemLista *inicializarItemLista(int valor) {
                ItemLista *novoItem = (ItemLista *) malloc(sizeof(ItemLista));
                novoItem->valor = valor;
                novoItem->prox = NULL;
                return novoItem;
            }

    #pragma endregion

    //////////////////////////////

    #pragma region Adicionar

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

        void adicionarNoArv(Arvore *arv, No *novoNo) 
        {
            if (arv->raiz == NULL) {
                novoNo->altura = 0;  // A raiz sempre tem altura 0
                arv->raiz = novoNo;
            } else {
                adicionarNoSubarv(arv->raiz, novoNo);
            }
        }


        void adicionarNoSubarv(No *noAtual, No *novoNo) 
        {
            novoNo->mae = noAtual;
            
            if (novoNo->valor < noAtual->valor) 
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
            
            novoNo->altura = novoNo->mae->altura + 1;
        }


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

    #pragma region Remover

    void removerNoArv(Arvore *arv, int chave) 
    {
        No *noAlvo = buscarNoArv(arv, chave);
        No *x;
        No *y;

        // sentinela, não há o que remover
        if (noAlvo == NULL) 
            return;

        if (noAlvo->esquerda == NULL || noAlvo->direita == NULL)
        {
            y = noAlvo;
        }
        else
        {
            y = buscarSucessor(noAlvo);
        }

        if (y->esquerda != NULL)
        {
            x = y->esquerda;
        }
        else
        {
            x = y->direita;
        }

        if (x != NULL)
        {
            x->mae = y->mae;
        }

        if (y->mae == NULL)
        {
            arv->raiz = x;
        }
        else
        {
            if (y->mae->esquerda == y)
            {
                y->mae->esquerda = x;
            }
            else
            {
                y->mae->direita = x;
            }
        }
        if (y != noAlvo)
        {
            noAlvo->valor = y->valor;
        }

        free(noAlvo);
    }

    #pragma endregion

    //////////////////////////////

    #pragma region Atribuir

    
        void atribuirCbctLinha(CbctLinha *cbctLinha) 
        {
            for (Linha *linhaAtual = cbctLinha->inicioLinha; linhaAtual != NULL; linhaAtual = linhaAtual->prox)
            {
                atribuirSaidaLinha(linhaAtual);
            }
        }
    

        void atribuirSaidaLinha(Linha *linha)
        {
            preencherStr(linha->linhaSaida, escreverSaidaLinha(linha));
        }

        void atribuirListaArv(Lista *lista, Arvore *arv)
        {
            for (ItemLista *itemAtual = lista->inicio; itemAtual != NULL; itemAtual = itemAtual->prox){
                adicionarNoArv(arv, inicializarNo(itemAtual->valor));
            }
        }

    #pragma endregion

    //////////////////////////////

    #pragma region Buscar

        // Sumário: Busca pelo nó sucessor do nó atual - ou seja, o próximo em ordem
        // crescente.
        // Parâmetro: <subArv: Nó submetido à busca>
        // Retorna: <No *: ponteiro pro sucessor ou NULL se não houver>
        No *buscarSucessor(No *subArv) 
        {
            No *atual;

            if (subArv->direita == NULL)
            {
                if (subArv->mae != NULL && subArv->mae->esquerda == subArv)
                    return subArv->mae;
                else 
                // se não, 
                    return NULL;
            }

            for (atual = subArv->direita; 
                atual != NULL && atual->esquerda != NULL; 
                atual = atual->esquerda);

            return atual;
        }

        No *buscarNoArv(Arvore *arv, int chave)
        {
            return buscarNoSubarv(arv->raiz, chave);
        }

        No *buscarNoSubarv(No *noAtual, int chave)
        {
            if (noAtual == NULL || noAtual->valor == chave) return noAtual;
            else if (noAtual->valor > chave) return buscarNoSubarv(noAtual->esquerda, chave);
            else if (noAtual-> valor < chave) return buscarNoSubarv(noAtual->direita, chave);
        }

    #pragma endregion

    //////////////////////////////

    #pragma region String
    
        void escreverSaida(CbctLinha *cbctLinha, FILE *saida)
        {
            for (Linha *linhaAtual = cbctLinha->inicioLinha; linhaAtual != NULL; linhaAtual = linhaAtual->prox)
                fprintf(saida, "%s", linhaAtual->linhaSaida);
        }
        
        char *escreverSaidaLinha(Linha *linha)
        {
            static char linhaStr[tam_max_linha];
            char *idx = linhaStr;
            printarArvoreOrdenada(linha->arvore->raiz, &idx);
            idx -=sizeof(char);
            if (linha->prox != NULL)
            {
                idx[0] = '\n';
                idx += sizeof(char);
            }

            idx[0] = '\0';

            return linhaStr;
        }

        void printarArvoreOrdenada(No *subarv, char **idx){
            if (!subarv)
                return;

            printarArvoreOrdenada(subarv->esquerda, idx);
            *idx += sizeof(char) * preencherStr(*idx, convIntStr(subarv->valor));
            *idx +=  sizeof(char) * preencherStr(*idx, " (");
            *idx +=  sizeof(char) * preencherStr(*idx, convIntStr(subarv->altura));
            *idx +=  sizeof(char) * preencherStr(*idx, ") ");
            printarArvoreOrdenada(subarv->direita, idx);
        }

        void lerTodasLinhas(CbctLinha *cbctLinha, FILE *entrada)
        {
            static char linhaStr[tam_max_linha];

            while (fgets(linhaStr, tam_max_linha, entrada) != NULL) {
                Lista *novaLista = inicializarLista();  
                Arvore *novaArvore = inicializarArvore();  
                Linha *novaLinha = inicializarLinha(novaLista, novaArvore);

                adicionarLinha(cbctLinha, novaLinha);

                lerComandos(novaLista, linhaStr);
                atribuirListaArv(novaLista, novaArvore);
            }
        }

        void lerComandos(Lista *lista, char *idxStr)
        {
            char comando;
            int numero;

            while (*idxStr != '\0')
            {
                while (*idxStr == ' ') idxStr+=sizeof(char);  // Pula espaços
                
                comando = *idxStr;  
                idxStr+=sizeof(char);  

                while (*idxStr == ' ') idxStr+=sizeof(char);  // Pula espaços após o comando

                numero = convStrInt(idxStr);  
                
                while (*idxStr != ' ' && *idxStr != '\n' && *idxStr != '\0') idxStr+=sizeof(char); // Avança para o próximo caractere

                if (comando == 'a') {
                    adicionarItemLista(lista, inicializarItemLista(numero));  
                }
                else if (comando == 'r') {
                    // Verifica se o número já está na lista
                    ItemLista *atual = lista->inicio;
                    ItemLista *anterior = NULL;
                    int encontrado = 0;

                    while (atual != NULL) {
                        if (atual->valor == numero) {
                            // Remove o nó da lista
                            if (anterior == NULL) {
                                lista->inicio = atual->prox;
                            } else {
                                anterior->prox = atual->prox;
                            }

                            if (atual == lista->fim) {
                                lista->fim = anterior;
                            }

                            free(atual);
                            encontrado = 1;
                            break;
                        }
                        anterior = atual;
                        atual = atual->prox;
                    }

                    // Se o número não foi encontrado, adicionamos ele
                    if (!encontrado) {
                        adicionarItemLista(lista, inicializarItemLista(numero));
                    }
                }
            }
        }

        


    #pragma endregion

    //////////////////////////////

//////////////////////////////

#pragma endregion

#pragma region AUXILIARES

    //////////////////////////////

    #pragma region String

        //////////////////////////////

        int preencherStr(char *cadeia, char *conteudo)
        {
            int cont = 0;

            while (*(conteudo) != '\0')
            {
                *(cadeia++) = *(conteudo++);
                cont++;
            }

            return cont;
        }


        char* obterSubstr(char *str, char *separadores) 
        {
            static char substr[tam_max_substr];
            int i, j;

            for(i = 0; str[i] != '\0' && i < tam_max_substr - 1; i++) 
            {
                for (j = 0; separadores[j] != '\0'; j++)
                    if (separadores[j] == str[i])
                        goto fim;

                substr[i] = str[i];
            }

            fim: 
            {
                substr[i] = '\0';
                return substr;
            }
        }

        //////////////////////////////

        int proxOcorrencia(char *str, char *alvos) 
        {
            char *idx = str;
            int i, j;
            
            // para cara char da entrada
            for (i = 0; str[i] != '\0'; i++)
                // verifica por igualdade com algum alvo
                for (j = 0; alvos[j] != '\0'; j++)
                    if (alvos[j] == str[i])
                        goto fim;

            fim: return i; 
        }

        // Sumário: checa se o char recebido é um número representado pela tabela ASCII
        // Parâmetros: <c: caracter avaliado>
        // Retorna: <int: 1 para verdadeiro, 0 para falso>
        int checarCharInt(char c){
            if (c > 47 && c < 58)
                return 1;
            else 
                return 0;
        }

        char proxCharStr(char *cadeia, char *separadores, int intervalo)
        {
            // contadores
            int i, k;

            // busca a próxima ocorrência de um dos separadores nos <intervalo> primeiros
            // caracteres
            for (i = 0; cadeia[i] != '\0' && i < intervalo; i++)
                for (k = i; separadores[k] != '\0'; k++)
                    if (cadeia[i] == separadores[k])
                        goto fim; // finaliza

            // retorna primeira ocorrência entre os separadores,
            // o char na posição final do intervalo ou '\0' se chegar
            //  no final da linha
            fim: return cadeia[i];
        }

        //////////////////////////////

    #pragma endregion

    //////////////////////////////

    #pragma region Conversões

        //////////////////////////////


        int convStrInt(char* str)
        {
            // propriedades
            int inteiro = 0;
            int sinal = 1;
            int i = 0;

            // se for negativo
            if (str[0] == '-')
            {
                sinal = -1; 
                str += sizeof(char);
            }

            // enquanto  não encontrar o final da linha
            while (checarCharInt((str[0])))
            {
                inteiro *= 10; // incrementa o número de algarismos e ordem de grandeza
                inteiro += *str - 48;  // atribui o novo algarismo em sua casa atual
                str += sizeof(char); // incrementa o indexador
            }

            inteiro *= sinal;

            return inteiro; // resultado
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

    #pragma region Matematica

        //////////////////////////////
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

        //////////////////////////////

    #pragma endregion

    //////////////////////////////

#pragma endregion

//////////////////////////////