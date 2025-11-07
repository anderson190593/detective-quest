#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TAM 10

// Estrutura da sala
typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// Estrutura da árvore BST de pistas
typedef struct PistaNode {
    char pista[100];
    struct PistaNode* esquerda;
    struct PistaNode* direita;
} PistaNode;

// Estrutura da tabela hash
typedef struct HashItem {
    char pista[100];
    char suspeito[50];
    struct HashItem* prox;
} HashItem;

// Tabela hash
HashItem* tabelaHash[HASH_TAM];

// Função: criarSala – cria dinamicamente uma sala com nome e pista
Sala* criarSala(const char* nome, const char* pista) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esquerda = nova->direita = NULL;
    return nova;
}

// Função: inserirPista – insere pista na BST
PistaNode* inserirPista(PistaNode* raiz, const char* pista) {
    if (raiz == NULL) {
        PistaNode* nova = (PistaNode*) malloc(sizeof(PistaNode));
        strcpy(nova->pista, pista);
        nova->esquerda = nova->direita = NULL;
        return nova;
    }
    if (strcmp(pista, raiz->pista) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->direita = inserirPista(raiz->direita, pista);
    return raiz;
}

// Função: exibirPistas – imprime pistas em ordem alfabética
void exibirPistas(PistaNode* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("🔎 %s\n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

// Função: hash – gera índice para tabela hash
int hash(const char* pista) {
    int soma = 0;
    for (int i = 0; pista[i] != '\0'; i++)
        soma += pista[i];
    return soma % HASH_TAM;
}

// Função: inserirNaHash – associa pista a suspeito
void inserirNaHash(const char* pista, const char* suspeito) {
    int indice = hash(pista);
    HashItem* novo = (HashItem*) malloc(sizeof(HashItem));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->prox = tabelaHash[indice];
    tabelaHash[indice] = novo;
}

// Função: encontrarSuspeito – retorna suspeito associado à pista
char* encontrarSuspeito(const char* pista) {
    int indice = hash(pista);
    HashItem* atual = tabelaHash[indice];
    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0)
            return atual->suspeito;
        atual = atual->prox;
    }
    return NULL;
}

// Função: contarPistasDoSuspeito – conta quantas pistas apontam para o suspeito
int contarPistasDoSuspeito(PistaNode* raiz, const char* suspeito) {
    if (root == NULL) return 0;
    int cont = 0;
    char* s = encontrarSuspeito(root->pista);
    if (s != NULL && strcmp(s, suspeito) == 0)
        cont++;
    cont += contarPistasDoSuspeito(root->esquerda, suspeito);
    cont += contarPistasDoSuspeito(root->direita, suspeito);
    return cont;
}

// Função: explorarSalas – navega pela mansão e coleta pistas
void explorarSalas(Sala* atual, PistaNode** arvorePistas) {
    char escolha;
    while (atual != NULL) {
        printf("\n📍 Sala atual: %s\n", atual->nome);
        if (strlen(atual->pista) > 0) {
            printf("🧩 Pista encontrada: \"%s\"\n", atual->pista);
            *arvorePistas = inserirPista(*arvorePistas, atual->pista);
        } else {
            printf("🔍 Nenhuma pista nesta sala.\n");
        }

        printf("Escolha o caminho:\n");
        if (atual->esquerda) printf("  (e) Esquerda\n");
        if (atual->direita) printf("  (d) Direita\n");
        printf("  (s) Sair da mansão\n");
        printf("Opção: ");
        scanf(" %c", &escolha);

        if (escolha == 'e' && atual->esquerda) atual = atual->esquerda;
        else if (escolha == 'd' && atual->direita) atual = atual->direita;
        else if (escolha == 's') break;
        else printf("❌ Caminho inválido.\n");
    }
}

// Função: verificarSuspeitoFinal – avalia acusação do jogador
void verificarSuspeitoFinal(PistaNode* pistas) {
    char suspeito[50];
    printf("\n👤 Quem você acusa como culpado? ");
    scanf(" %[^\n]", suspeito);

    int cont = contarPistasDoSuspeito(pistas, suspeito);
    if (cont >= 2) {
        printf("\n✅ Acusação válida! %s foi identificado como culpado com %d pistas.\n", suspeito, cont);
    } else {
        printf("\n❌ Acusação fraca. Apenas %d pista(s) apontam para %s.\n", cont, suspeito);
    }
}

// Função: main – monta o mapa, associa pistas e inicia o jogo
int main() {
    // Criação da mansão
    Sala* hall = criarSala("Hall de Entrada", "Pegadas molhadas");
    Sala* salaEstar = criarSala("Sala de Estar", "Copo quebrado");
    Sala* cozinha = criarSala("Cozinha", "Faca fora do lugar");
    Sala* biblioteca = criarSala("Biblioteca", "Livro rasgado");
    Sala* jardim = criarSala("Jardim", "");
    Sala* porao = criarSala("Porão", "Porta secreta");

    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;
    cozinha->direita = porao;

    // Associação de pistas a suspeitos
    inserirNaHash("Pegadas molhadas", "Carlos");
    inserirNaHash("Copo quebrado", "Ana");
    inserirNaHash("Faca fora do lugar", "Carlos");
    inserirNaHash("Livro rasgado", "Bruno");
    inserirNaHash("Porta secreta", "Carlos");

    // Início do jogo
    PistaNode* pistasColetadas = NULL;
    printf("🕵️ Detective Quest – Julgamento Final\n");
    explorarSalas(hall, &pistasColetadas);

    // Exibição de pistas
    printf("\n📜 Pistas coletadas:\n");
    exibirPistas(pistasColetadas);

    // Fase de julgamento
    verificarSuspeitoFinal(pistasColetadas);

    return 0;
}