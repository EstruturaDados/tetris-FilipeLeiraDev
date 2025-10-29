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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ==================== ESTRUTURA DA PEÇA ====================
typedef struct {
    char nome;   // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;      // Identificador único (ordem de criação)
} Peca;

// ==================== CONFIGURAÇÕES DA FILA ====================
#define TAMANHO_FILA 5
Peca fila[TAMANHO_FILA];
int frente = 0;      // Índice da frente da fila
int tras = 0;        // Índice do final da fila
int contador = 0;    // Quantidade de peças na fila
int proximo_id = 0;  // Próximo ID a ser atribuído

// ==================== PROTÓTIPOS DAS FUNÇÕES ====================
void inicializarFila();
void exibirFila();
Peca gerarPeca();
int estaCheia();
int estaVazia();
void enqueue(Peca nova);
Peca dequeue();
void limparBuffer();

// ==================== FUNÇÃO PRINCIPAL ====================
int main() {
    int opcao;

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Inicializa a fila com 5 peças
    inicializarFila();

    printf("=== TETRIS STACK - FILA DE PECAS FUTURAS ===\n\n");

    do {
        exibirFila();

        printf("\nOpcoes de acao:\n");
        printf("1 - Jogar peca (dequeue)\n");
        printf("2 - Inserir nova peca (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                if (estaVazia()) {
                    printf("\n[ERRO] Fila vazia! Nao ha peca para jogar.\n");
                } else {
                    Peca jogada = dequeue();
                    printf("\nPECA JOGADA: [%c %d]\n", jogada.nome, jogada.id);
                }
                break;

            case 2:
                if (estaCheia()) {
                    printf("\n[ERRO] Fila cheia! Nao ha espaco para nova peca.\n");
                } else {
                    Peca nova = gerarPeca();
                    enqueue(nova);
                    printf("\nNOVA PECA ADICIONADA: [%c %d]\n", nova.nome, nova.id);
                }
                break;

            case 0:
                printf("\nJogo encerrado. Ate a proxima!\n");
                break;

            default:
                printf("\n[ERRO] Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

// ==================== INICIALIZAÇÃO DA FILA ====================
void inicializarFila() {
    printf("Inicializando fila com 5 pecas...\n");
    for (int i = 0; i < TAMANHO_FILA; i++) {
        Peca nova = gerarPeca();
        fila[tras] = nova;
        tras = (tras + 1) % TAMANHO_FILA;
        contador++;
    }
    printf("Fila inicializada com sucesso!\n\n");
}

// ==================== EXIBIÇÃO DA FILA ====================
void exibirFila() {
    printf("\n=== FILA DE PECAS ===\n");
    if (estaVazia()) {
        printf("  [FILA VAZIA]\n");
        return;
    }

    printf("  ");
    int i = frente;
    for (int count = 0; count < contador; count++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % TAMANHO_FILA;
    }
    printf("\n");
}

// ==================== GERAÇÃO AUTOMÁTICA DE PEÇA ====================
Peca gerarPeca() {
    Peca nova;
    int tipo = rand() % 4;
    switch (tipo) {
        case 0: nova.nome = 'I'; break;
        case 1: nova.nome = 'O'; break;
        case 2: nova.nome = 'T'; break;
        case 3: nova.nome = 'L'; break;
    }
    nova.id = proximo_id++;
    return nova;
}

// ==================== VERIFICAÇÕES DE ESTADO ====================
int estaCheia() {
    return contador == TAMANHO_FILA;
}

int estaVazia() {
    return contador == 0;
}

// ==================== OPERAÇÕES DA FILA CIRCULAR ====================
void enqueue(Peca nova) {
    if (estaCheia()) return;

    fila[tras] = nova;
    tras = (tras + 1) % TAMANHO_FILA;
    contador++;
}

Peca dequeue() {
    if (estaVazia()) {
        Peca vazia = {' ', -1};
        return vazia;
    }

    Peca removida = fila[frente];
    frente = (frente + 1) % TAMANHO_FILA;
    contador--;
    return removida;
}

// ==================== LIMPAR BUFFER DO TECLADO ====================
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}