#include <stdio.h>
#include <stdlib.h>

#define TAM_FILA 5

/* 
Struct da peça do jogo
*/
typedef struct {
    char nome; // Tipo da peça I, O, T, L
    int id; // Identificador único
} Peca;

/*
Struct da fila circular
*/
typedef struct {
    Peca fila[TAM_FILA]; // Vetor de peças
    int inicio; // Índice do início da fila
    int fim; //Índice do final da fila
    int quantidade;  // Quantidade atual de elementos
} Fila;

/*
Gerar uma nova peça
*/
Peca gerarPeca(int id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};

    nova.nome = tipos[rand() % 4]; // Escolhe um tipo aleatório
    nova.id = id;

    return nova;
}

/*
Inicializa a fila
*/
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

/*
Verifica se a fila está cheia
*/
int filaCheia(Fila *f) {
    return f->quantidade == TAM_FILA;
}

/*
Verifica se a fila esta vazia
*/
int filaVazia(Fila *f) {
    return f->quantidade == 0;
}

/*
Insere uma peça na fila
*/
void enqueue(Fila *f, Peca peca) {
    if (filaCheia(f)) {
        printf("Fila cheia! Não é possivel inserir nova peça.\n");
        return;
    }

    f->fila[f->fim] = peca;
    f->fim = (f->fim + 1) % TAM_FILA; // Avanço circular
    f->quantidade++;
}

/*
Remove uma peça da fila 
*/
void dequeue(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia! Não ha peça para remover.\n");
        return;
    }

    f->inicio = (f->inicio + 1) % TAM_FILA; // Avanço circular
    f->quantidade--;
}

/*
Exibe o estado da fila
*/
void exibirFila(Fila *f) {
    printf("\nFila de peças:\n");

    if (filaVazia(f)) {
        printf("Fila vazia.\n");
        return;
    }

    int i;
    int indice = f->inicio;

    for (i = 0; i < f->quantidade; i++) {
        printf("[%c %d] ", f->fila[indice].nome, f->fila[indice].id);
        indice = (indice + 1) % TAM_FILA;
    }

    printf("\n");
}

/*
PROGRAMA PRINCIPAL
*/
int main() {
    Fila fila;
    int opcao;
    int idpeca = 0;

    inicializarFila(&fila);

    // Inicializa a fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca(idpeca++));
    }

    do {
        exibirFila(&fila);

        printf("\nOpcoes:\n");
        printf("1 - Jogar peca (dequeue)\n");
        printf("2 - Inserir nova peca (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
        case 1:
            dequeue(&fila);
            enqueue(&fila, gerarPeca(idpeca++));
            break;

        case 2:
            enqueue(&fila, gerarPeca(idpeca++));
            break;

        case 0: 
            printf("Encerrando o programa...\n");
            break;

        default:
            printf("Opção inválida.\n");
            break;
        }
    } while (opcao != 0);
    
    return 0;
}

