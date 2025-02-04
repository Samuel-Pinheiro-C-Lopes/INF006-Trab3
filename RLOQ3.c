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
    
            void removerNoArvore(Arvore *arv, int chave);

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
            void lerComandos(Arvore *arv, char *idxStr);
            void lerTodasLinhas(CbctLinha *cbctLinha, FILE *entrada);
            void escreverSaida(CbctLinha *cbctLinha,FILE *saida);
            char *escreverSaidaLinha(Linha *linha);
            // auxiliares
            int preencherStr(char *cadeia, char *conteudo);
            char* obterSubstr(char *str, char *separadores);
            int proxOcorrencia(char *str, char *alvos);
            int checarCharInt(char c);
            char proxCharStr(char *cadeia, char *separadores, int intervalo);

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
        FILE *entrada = fopen("L2Q2.in", "r");
        FILE *saida = fopen("L2Q2.out", "w");

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

            // Sumário: inicializa novo gerente de linhas
            // Parâmetros: <void>
            // Retorno: ponteiro para novo gerente
            Linha *inicializarLinha(Lista *lista, Arvore *arv) {
                Linha *novaLinha = (Linha *) malloc(sizeof(Linha));
                novaLinha->arvore = arv;
                novaLinha->lista = lista;
                return novaLinha;
            }

            // arvore
            // Sumário: inicializa nova árvore
            // Parâmetros: <void>
            // Retorno: ponteiro para nova árvore
            Arvore *inicializarArvore() {
                Arvore *novaArvore = (Arvore *) malloc(sizeof(Arvore));
                novaArvore->raiz = NULL;
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

    #pragma region Remover

        // Sumário: Realiza a remoção de um nó de determinada chave
        // na árvore alvo.
        // Parâmetros: <arv: árvore que terá um nó removido> e <chave: identidade
        // do nó a ser removido>
        // Retorna: <void>
        void removerNoArv(Arvore *arv, int chave) 
        {
            No *noAlvo = buscarNoArv(arv, chave);
            No *subst;

        }
        

    #pragma endregion

    //////////////////////////////

    #pragma region Atribuir

        // Sumário: realiza todas as atribuições necessárias para cada linha
        // presente no cabeçote, considerando que as listas de cada linha foram lidas
        // Parâmetros: <cbctLinha: cabeçote cujas linhas serão atribuídas>
        // Retorna: <void>
        void atribuirCbctLinha(CbctLinha *cbctLinha) 
        {
            for (Linha *linhaAtual = cbctLinha->inicioLinha; linhaAtual != NULL; linhaAtual = linhaAtual->prox)
            {
                atribuirListaArv(linhaAtual->lista, linhaAtual->arvore);
                // [...]?
                atribuirSaidaLinha(linhaAtual);
            }
        }
    
        // Sumário: designa a string correspondente a saída esperada
        // por essa linha com base na árvore e lista correspondente
        // Parâmetros: <linha: linha alvo da atribuição>
        // Retorna: <void>
        void atribuirSaidaLinha(Linha *linha)
        {
            // necessário preencher com base no conteúdo escrito
            // ao invés de designar o ponteiro pois
            // escreverSaidaLinha retorna ponteiro para a string estática
            // de seu escopo, deve ser utilizada apenas como alvo de cópia
            preencherStr(linha->linhaSaida, escreverSaidaLinha(linha));
        }

        // Sumário: atribui uma lista de valores a uma árvore de busca binária
        // Parâmetros: <lista: lista a ser lida> e <arv: árvore a ser escrita>
        // Retorna: <void>
        void atribuirListaArv(Lista *lista, Arvore *arv)
        {
            for (ItemLista *itemAtual = lista->inicio; itemAtual != NULL; itemAtual = itemAtual->prox)
                adicionarNoArv(arv, inicializarNo(itemAtual->valor));
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
            
            for (atual = subArv->direita; 
                atual != NULL && atual->esquerda != NULL; 
                atual = atual->esquerda);

            return atual;
        }

        // Sumário: Busca por um nó em uma árvore, o checa e retorna se encontrar
        // Parâmetros: <arv: árvore a ter um nó buscado> e <chave: valor de
        // busca>
        // Retorna: <No *: ponteiro para o nó ou nulo se não houver>
        No *buscarNoArv(Arvore *arv, int chave)
        {
            return buscarNoSubarv(arv->raiz, chave);
        }

        // Sumário: função auxiliar recursiva para realizar a busca do nó de chave
        // equivalente à passada, retornando o Nó ou NULL
        // Parâmetros: <noAtual: nó atual da recursão, representa raiz da
        // subárvore avaliada> e <chave: valor de
        // busca>
        // Retorna: <No *: ponteiro para o nó ou nulo se não houver>
        No *buscarNoSubarv(No *noAtual, int chave)
        {
            if (noAtual == NULL || noAtual->valor == chave) return noAtual;
            else if (noAtual->valor > chave) return buscarNoSubarv(noAtual->esquerda, chave);
            else if (noAtual-> valor <= chave) return buscarNoSubarv(noAtual->direita, chave);
        }

    #pragma endregion

    //////////////////////////////

    #pragma region String
    
        // Sumário: escreve a saída de todas as linha de um cabeçote 
        // para o arquivo de saída alvo
        // Parâmetros: <cbctLinha: cabeçote das linhas> e <saida: arquivo alvo>
        // Retorna: <void>
        void escreverSaida(CbctLinha *cbctLinha, FILE *saida)
        {
            for (Linha *linhaAtual = cbctLinha->inicioLinha; linhaAtual != NULL; linhaAtual = linhaAtual->prox)
                fprintf(saida, "%s", linhaAtual->linhaSaida);
        }

        // Sumário: escreve um texto de saída baseado nos campos preenchidos
        // da linha
        // Parâmetros: <linha: linha a ter seu campo de string de saída
        // preenchido com base nas lista e árvore intrínsecas
        // Return: <char *: ponteiro para o texto gerado>
        // !!!! ALTERAÇÕES PENDENTES !!!!
        char *escreverSaidaLinha(Linha *linha)
        {
            static char linhaStr[tam_max_linha];
            char *idx = linhaStr;

            for (ItemLista *itemAtual = linha->lista->inicio; itemAtual != NULL; itemAtual = itemAtual->prox)
            {
                // [...]
            }

            if (linha->prox != NULL)
            {
                idx[0] = '\n';
                idx += sizeof(char);
            }

            idx[0] = '\0';

            return linhaStr;
        }

        // Sumário: Lê todas as linhas em formato de lista presentes em um arquivo de texto
        // Parâmetros: <cbctLinha: cbct de linha a  ser escrita> e <entrada: arquivo a ser
        // lido>
        // Retorna: <void>
        void lerTodasLinhas(CbctLinha *cbctLinha, FILE *entrada)
        {
            static char linhaStr[tam_max_linha];

            while (fgets(linhaStr, tam_max_linha, entrada) != NULL) {
                // adiciona ao cbct       // nova linha    // nova lista       // nova árvore
                adicionarLinha(cbctLinha, inicializarLinha(inicializarLista(), inicializarArvore()));
                lerComandos(cbctLinha->fimLinha->arvore, linhaStr);
            }
        }

        // Sumário: Lê uma lista de uma entrada de texto, cujos números inteiros devem ser
        // espaçados em 1 entre si Navega pelos espaços.
        // Parâmetros: <lista: lista a ser preenchida> e <idxStr: indexador atual
        // do texto de entrada>
        // Retorno: <void>
        void lerComandos(Arvore *arv, char *idxStr)
        {
            char comando;
            int numero;

            while (idxStr[0] != '\0')
            {
                idxStr += sizeof(char) * proxOcorrencia(idxStr, "ra\n");
                comando = obterSubstr(idxStr, " ")[0];
                idxStr += sizeof(char) * proxOcorrencia(idxStr, "-0123456789\n");
                numero = convStrInt(obterSubstr(idxStr, " \n"));

                switch(comando)
                {
                    case ('\0'): // fim string
                    case ('\n'): break; // pula linha
                    case ('a'): goto add;
                    case ('r'): {
                        if (buscarNoArv(arv, numero) == NULL)
                            goto add;

                        removerNoArv(arv, numero);
                        break;
                    }
                    add: adicionarNoArv(arv, inicializarNo(convStrInt(obterSubstr(idxStr, " "))));
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

        // Sumário: Preenche a cadeia alvo com o conteúdo
        // até o fim do conteúdo.
        // Não checa pelo final da cadeia alvo, podendo tentar atribuir memória não alocada
        // para a cadeia
        // Parâmetros: <cadeia: vetor de caracteres alvo a ser preenchido> e <conteudo:
        // vetor de caracteres que deve preencher o alvo>
        // Retorna: <int: quantos caracteres foram preenchidos>
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

        // Sumário: busca pela próxima ocorrência de certos alvos
        // em uma string e retorna quantidade de passos até chegar nela
        // Parâmetros: <str: string alvo> <alvos: caracteres que finalizarão
        // a busca>
        // Retorna: <int: quantidade de avanços até a primeira ocorrência de um dos alvos>
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

            // retorna ponteiro da primeira ocorrência 
            // de um dos alvos ou '\0'
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

        // Sumário: busca em uma cadeia a primeira ocorrência de um ou mais 
        // caracteres de separação em um intervalo, retornando essa ocorrência
        // Parâmetros: <cadeia: cadeia de caracteres de entrada>, <separadores: caracteres de busca> e
        // <intervalo: quantos caracteres contando com o atual devem ser lidos a partir do indexador>
        // Returna: <char: caracter da ocorrência encontrada> 
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

        //////////////////////////////

    #pragma endregion

    //////////////////////////////

#pragma endregion

//////////////////////////////