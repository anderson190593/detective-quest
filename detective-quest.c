#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa uma sala da mansão
typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

/*
    Função: criarSala
    Objetivo: aloca dinamicamente uma sala com o nome fornecido
*/
Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*) malloc(sizeof(Sala));
    if (novaSala != NULL) {
        strcpy(novaSala->nome, nome);
        novaSala->esquerda = NULL;
        novaSala->direita = NULL;
    }
    return novaSala;
}

/*
    Função: explorarSalas
    Objetivo: permite ao jogador navegar pela árvore binária da mansão
*/
void explorarSalas(Sala* atual) {
    char escolha;

    while (atual != NULL) {
        printf("\n📍 Você está na sala: %s\n", atual->nome);

        // Verifica se é um nó-folha
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("🔍 Esta sala não possui mais caminhos. Fim da exploração.\n");
            break;
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
    Objetivo: monta o mapa da mansão e inicia a exploração
*/
int main() {
    // Criação manual da árvore binária da mansão
    Sala* hall = criarSala("Hall de Entrada");
    Sala* salaEstar = criarSala("Sala de Estar");
    Sala* cozinha = criarSala("Cozinha");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* jardim = criarSala("Jardim");
    Sala* porao = criarSala("Porão");

    // Montagem da árvore
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;
    cozinha->direita = porao;

    // Início da exploração
    printf("🕵️ Bem-vindo ao Detective Quest!\n");
    explorarSalas(hall);

    // Liberação de memória
    free(hall);
    free(salaEstar);
    free(cozinha);
    free(biblioteca);
    free(jardim);
    free(porao);

    return 0;
}