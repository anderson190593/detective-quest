#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de uma sala da mansão
typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// Estrutura de um nó da árvore de pistas (BST)
typedef struct PistaNode {
    char pista[100];
    struct PistaNode* esquerda;
    struct PistaNode* direita;
} PistaNode;

/*
    Função: criarSala
    Objetivo: cria dinamicamente uma sala com nome e pista
*/
Sala* criarSala(const char* nome, const char* pista) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    if (nova != NULL) {
        strcpy(nova->nome, nome);
        strcpy(nova->pista, pista);
        nova->esquerda = NULL;
        nova->direita = NULL;
    }
    return nova;
}

/*
    Função: inserirPista
    Objetivo: insere uma nova pista na árvore BST de forma ordenada
*/
PistaNode* inserirPista(PistaNode* raiz, const char* pista) {
    if (raiz == NULL) {
        PistaNode* nova = (PistaNode*) malloc(sizeof(PistaNode));
        strcpy(nova->pista, pista);
        nova->esquerda = nova->direita = NULL;
        return nova;
    }
    if (strcmp(pista, raiz->pista) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    } else if (strcmp(pista, raiz->pista) > 0) {
        raiz->direita = inserirPista(raiz->direita, pista);
    }
    return raiz;
}

/*
    Função: exibirPistas
    Objetivo: imprime as pistas em ordem alfabética (in-order traversal)
*/
void exibirPistas(PistaNode* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("🔎 %s\n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

/*
    Função: explorarSalasComPistas
    Objetivo: permite a navegação pela mansão e coleta de pistas
*/
void explorarSalasComPistas(Sala* atual, PistaNode** arvorePistas) {
    char escolha;

    while (atual != NULL) {
        printf("\n📍 Você está na sala: %s\n", atual->nome);

        if (strlen(atual->pista) > 0) {
            printf("🧩 Pista encontrada: \"%s\"\n", atual->pista);
            *arvorePistas = inserirPista(*arvorePistas, atual->pista);
        } else {
            printf("🔍 Nenhuma pista nesta sala.\n");
        }

        printf("Escolha o caminho:\n");
        if (atual->esquerda != NULL) printf("  (e) Ir para a esquerda\n");
        if (atual->direita != NULL) printf("  (d) Ir para a direita\n");
        printf("  (s) Sair da mansão\n");
        printf("Opção: ");
        scanf(" %c", &escolha);

        if (escolha == 'e' && atual->esquerda != NULL) {
            atual = atual->esquerda;
        } else if (escolha == 'd' && atual->direita != NULL) {
            atual = atual->direita;
        } else if (escolha == 's') {
            printf("🚪 Você saiu da mansão.\n");
            break;
        } else {
            printf("❌ Caminho inválido. Tente novamente.\n");
        }
    }
}

/*
    Função: main
    Objetivo: monta o mapa da mansão e inicia a exploração com coleta de pistas
*/
int main() {
    // Criação do mapa da mansão
    Sala* hall = criarSala("Hall de Entrada", "Pegadas molhadas no tapete");
    Sala* salaEstar = criarSala("Sala de Estar", "Copo quebrado no chão");
    Sala* cozinha = criarSala("Cozinha", "Faca fora do lugar");
    Sala* biblioteca = criarSala("Biblioteca", "Livro com páginas arrancadas");
    Sala* jardim = criarSala("Jardim", "");
    Sala* porao = criarSala("Porão", "Porta secreta entreaberta");

    // Montagem da árvore binária da mansão
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;
    cozinha->direita = porao;

    // Inicializa árvore de pistas
    PistaNode* arvorePistas = NULL;

    // Início da exploração
    printf("🕵️ Bem-vindo ao Detective Quest – Coleta de Pistas!\n");
    explorarSalasComPistas(hall, &arvorePistas);

    // Exibe pistas coletadas
    printf("\n📜 Pistas coletadas em ordem alfabética:\n");
    exibirPistas(arvorePistas);

    // Liberação de memória omitida para simplificação

    return 0;
}