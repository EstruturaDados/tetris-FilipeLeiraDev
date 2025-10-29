#include <stdio.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

//int main() {

    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.



    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha


    //return 0;
//}

/*
 * Programa: Tetris Stack - Fila de Peças Futuras
 * Disciplina: Estruturas de Dados em C (Aula 3)
 * Descrição: Simula uma fila circular de peças do Tetris com enqueue, dequeue,
 *            geração automática e exibição clara.
 */
/*
 * Programa: Tetris Stack - Fila + Pilha de Reserva
 * Disciplina: Estruturas de Dados em C (Aula 3 - Nível Intermediário)
 * Descrição: Simula fila circular de peças futuras e pilha de reserva.
 *            Jogar, reservar, usar peça reservada, com geração automática.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ==================== ESTRUTURA DA PEÇA ====================
typedef struct {
    char nome;   // 'I', 'O', 'T', 'L'
    int id;      // ID único
} Peca;

// ==================== CONFIGURAÇÕES ====================
#define TAM_FILA 5
#define TAM_PILHA 3

Peca fila[TAM_FILA];
int frente = 0, tras = 0, cont_fila = 0;

Peca pilha[TAM_PILHA];
int topo = -1;  // -1 = pilha vazia

int proximo_id = 0;

// ==================== PROTÓTIPOS ====================
void inicializarFila();
void exibirEstado();
Peca gerarPeca();
int filaCheia();
int filaVazia();
int pilhaCheia();
int pilhaVazia();
void enqueue(Peca p);
Peca dequeue();
void push(Peca p);
Peca pop();
void limparBuffer();

// ==================== FUNÇÃO PRINCIPAL ====================
int main() {
    int opcao;

    srand(time(NULL));
    inicializarFila();

    printf("=== TETRIS STACK - FILA + PILHA DE RESERVA ===\n\n");

    do {
        exibirEstado();

        printf("\nOpcoes de Acao:\n");
        printf("1 - Jogar peca (dequeue)\n");
        printf("2 - Reservar peca (fila -> pilha)\n");
        printf("3 - Usar peca reservada (pop)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: // Jogar peça
                if (filaVazia()) {
                    printf("\n[ERRO] Fila vazia! Nao ha peca para jogar.\n");
                } else {
                    Peca jogada = dequeue();
                    printf("\nPECA JOGADA: [%c %d]\n", jogada.nome, jogada.id);
                    // Gera nova peça para manter fila cheia
                    if (!filaCheia()) {
                        Peca nova = gerarPeca();
                        enqueue(nova);
                        printf("NOVA PECA GERADA: [%c %d]\n", nova.nome, nova.id);
                    }
                }
                break;

            case 2: // Reservar peça
                if (filaVazia()) {
                    printf("\n[ERRO] Fila vazia! Nao ha peca para reservar.\n");
                } else if (pilhaCheia()) {
                    printf("\n[ERRO] Pilha de reserva cheia! Libere espaco primeiro.\n");
                } else {
                    Peca reservada = dequeue();
                    push(reservada);
                    printf("\nPECA RESERVADA: [%c %d]\n", reservada.nome, reservada.id);
                    // Gera nova peça
                    if (!filaCheia()) {
                        Peca nova = gerarPeca();
                        enqueue(nova);
                        printf("NOVA PECA GERADA: [%c %d]\n", nova.nome, nova.id);
                    }
                }
                break;

            case 3: // Usar peça reservada
                if (pilhaVazia()) {
                    printf("\n[ERRO] Pilha de reserva vazia! Nao ha peca reservada.\n");
                } else {
                    Peca usada = pop();
                    printf("\nPECA RESERVADA USADA: [%c %d]\n", usada.nome, usada.id);
                }
                break;

            case 0:
                printf("\nJogo encerrado. Obrigado por jogar!\n");
                break;

            default:
                printf("\n[ERRO] Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// ==================== INICIALIZAÇÃO ====================
void inicializarFila() {
    printf("Inicializando fila com %d pecas...\n", TAM_FILA);
    for (int i = 0; i < TAM_FILA; i++) {
        Peca p = gerarPeca();
        enqueue(p);
    }
    printf("Fila inicializada!\n\n");
}

// ==================== EXIBIÇÃO DO ESTADO ====================
void exibirEstado() {
    printf("\n=== ESTADO ATUAL ===\n");

    // Fila
    printf("Fila de pecas     : ");
    if (filaVazia()) {
        printf("[FILA VAZIA]\n");
    } else {
        int i = frente;
        for (int c = 0; c < cont_fila; c++) {
            printf("[%c %d] ", fila[i].nome, fila[i].id);
            i = (i + 1) % TAM_FILA;
        }
        printf("\n");
    }

    // Pilha
    printf("Pilha de reserva  : (Topo -> Base): ");
    if (pilhaVazia()) {
        printf("[VAZIA]\n");
    } else {
        for (int i = topo; i >= 0; i--) {
            printf("[%c %d] ", pilha[i].nome, pilha[i].id);
        }
        printf("\n");
    }
}

// ==================== GERAÇÃO DE PEÇA ====================
Peca gerarPeca() {
    Peca p;
    int tipo = rand() % 4;
    switch (tipo) {
        case 0: p.nome = 'I'; break;
        case 1: p.nome = 'O'; break;
        case 2: p.nome = 'T'; break;
        case 3: p.nome = 'L'; break;
    }
    p.id = proximo_id++;
    return p;
}

// ==================== VERIFICAÇÕES ====================
int filaCheia()  { return cont_fila == TAM_FILA; }
int filaVazia()  { return cont_fila == 0; }
int pilhaCheia() { return topo == TAM_PILHA - 1; }
int pilhaVazia() { return topo == -1; }

// ==================== FILA CIRCULAR ====================
void enqueue(Peca p) {
    if (filaCheia()) return;
    fila[tras] = p;
    tras = (tras + 1) % TAM_FILA;
    cont_fila++;
}

Peca dequeue() {
    if (filaVazia()) {
        Peca vazia = {' ', -1};
        return vazia;
    }
    Peca removida = fila[frente];
    frente = (frente + 1) % TAM_FILA;
    cont_fila--;
    return removida;
}

// ==================== PILHA (LIFO) ====================
void push(Peca p) {
    if (pilhaCheia()) return;
    pilha[++topo] = p;
}

Peca pop() {
    if (pilhaVazia()) {
        Peca vazia = {' ', -1};
        return vazia;
    }
    return pilha[topo--];
}

// ==================== LIMPAR BUFFER ====================
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}