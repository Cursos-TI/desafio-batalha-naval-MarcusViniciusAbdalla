#include <stdio.h> // Biblioteca padrão para entrada e saída de dados
#include <stdbool.h> // Para usar tipos booleanos (true/false)

// --- Constantes para o Tabuleiro de Batalha Naval ---
#define TABULEIRO_TAMANHO 10 // Tabuleiro 10x10
#define TAMANHO_NAVIO 3      // Navios de 3 posições

// --- Funções Recursivas para Movimento das Peças de Xadrez ---

// Função recursiva para simular o movimento da TORRE
// Move a peça 'direcao_str' por 'passos_restantes' casas.
// current_step: o número da casa atual na simulação.
void moverTorreRecursivo(int passos_restantes, int current_step) {
    // Caso base: Se não há mais passos para mover, a recursão termina.
    if (passos_restantes == 0) {
        printf("Torre parou.\n\n");
        return;
    }

    // Ação: Imprime a direção do movimento para o passo atual.
    printf("Casa %d: Direita\n", current_step);

    // Chamada recursiva: Decrementa os passos restantes e incrementa o passo atual.
    moverTorreRecursivo(passos_restantes - 1, current_step + 1);
}

// Função recursiva para simular o movimento do BISPO
// Move a peça na diagonal por 'passos_restantes' casas.
// current_step: o número da casa atual na simulação.
void moverBispoRecursivo(int passos_restantes, int current_step) {
    // Caso base: Se não há mais passos para mover, a recursão termina.
    if (passos_restantes == 0) {
        printf("Bispo parou.\n\n");
        return;
    }

    // Ação: Imprime a direção do movimento para o passo atual.
    printf("Casa %d: Cima, Direita\n", current_step);

    // Chamada recursiva: Decrementa os passos restantes e incrementa o passo atual.
    moverBispoRecursivo(passos_restantes - 1, current_step + 1);
}

// Função recursiva para simular o movimento da RAINHA
// Move a peça 'direcao_str' por 'passos_restantes' casas.
// current_step: o número da casa atual na simulação.
void moverRainhaRecursivo(int passos_restantes, int current_step) {
    // Caso base: Se não há mais passos para mover, a recursão termina.
    if (passos_restantes == 0) {
        printf("Rainha parou.\n\n");
        return;
    }

    // Ação: Imprime a direção do movimento para o passo atual.
    printf("Casa %d: Esquerda\n", current_step);

    // Chamada recursiva: Decrementa os passos restantes e incrementa o passo atual.
    moverRainhaRecursivo(passos_restantes - 1, current_step + 1);
}


// --- Função Principal ---
int main() {
    // --- Simulação do Movimento da TORRE (usando recursividade) ---
    printf("--- Movimento da TORRE (Recursivo) ---\n");
    printf("A Torre se movera 5 casas para a direita.\n");
    moverTorreRecursivo(5, 1); // Inicia a recursão para 5 passos, começando do passo 1

    // --- Simulação do Movimento do BISPO (usando recursividade) ---
    printf("--- Movimento do BISPO (Recursivo) ---\n");
    printf("O Bispo se movera 5 casas na diagonal (cima e direita).\n");
    moverBispoRecursivo(5, 1); // Inicia a recursão para 5 passos, começando do passo 1

    // --- Simulação do Movimento da RAINHA (usando recursividade) ---
    printf("--- Movimento da RAINHA (Recursivo) ---\n");
    printf("A Rainha se movera 8 casas para a esquerda.\n");
    moverRainhaRecursivo(8, 1); // Inicia a recursão para 8 passos, começando do passo 1

    // --- Simulação do Movimento do CAVALO (usando loops aninhados complexos) ---
    // O Cavalo move-se em "L": 2 casas em uma direção e 1 casa perpendicularmente.
    // Simulação: 2 casas para CIMA e 1 casa para a DIREITA.
    printf("--- Movimento do CAVALO (Loops Aninhados Complexos) ---\n");
    printf("O Cavalo se movera em 'L': 2 casas para CIMA e 1 casa para a DIREITA.\n");

    int passos_verticais = 2;   // Quantidade de passos verticais
    int passos_horizontais = 1; // Quantidade de passos horizontais
    int passo_total = 0;        // Contador de passos totais para o Cavalo

    // Loop externo (for) para simular os passos verticais (CIMA)
    for (int y = 0; y < passos_verticais; y++) {
        passo_total++;
        printf("Passo %d do Cavalo: Cima\n", passo_total);
        // Exemplo de uso de 'continue' (não estritamente necessário aqui, mas demonstra o uso):
        // if (y == 0) continue; // Poderia pular alguma lógica no primeiro passo vertical
    }

    // Loop interno (while) para simular os passos horizontais (DIREITA)
    int x = 0;
    while (x < passos_horizontais) {
        passo_total++;
        printf("Passo %d do Cavalo: Direita\n", passo_total);
        x++;
        // Exemplo de uso de 'break' (não estritamente necessário aqui, mas demonstra o uso):
        // if (x == 1) break; // Poderia parar após o primeiro passo horizontal
    }
    printf("Cavalo parou.\n\n");

    // --- Simulação do Movimento do BISPO (usando Loops Aninhados) ---
    // Esta é uma implementação alternativa para simular um movimento diagonal
    // usando loops aninhados para ilustrar a combinação de movimentos vertical e horizontal
    // para cada "passo" na diagonal.
    printf("--- Movimento do BISPO (Loops Aninhados - Demonstracao) ---\n");
    printf("O Bispo se movera 3 casas na diagonal (cima e direita) usando loops aninhados.\n");

    int max_diagonal_steps = 3; // Número de "passos" diagonais a simular
    int current_diagonal_step = 1;

    for (int diag_step = 0; diag_step < max_diagonal_steps; diag_step++) {
        printf("Passo diagonal %d:\n", current_diagonal_step++);
        // Loop para o componente vertical de um passo diagonal
        for (int vert_comp = 0; vert_comp < 1; vert_comp++) { // Apenas 1 "movimento" vertical por passo diagonal
            printf("  Cima\n");
        }
        // Loop para o componente horizontal de um passo diagonal
        int horiz_comp = 0;
        while (horiz_comp < 1) { // Apenas 1 "movimento" horizontal por passo diagonal
            printf("  Direita\n");
            horiz_comp++;
        }
    }
    printf("Bispo (loops aninhados) parou.\n\n");

    // ==========================================================
    // --- Desafio: Posicionando Navios no Tabuleiro de Batalha Naval ---
    // ==========================================================
    printf("========================================\n");
    printf("--- Batalha Naval: Posicionando Navios ---\n");
    printf("========================================\n\n");

    // 1. Represente o Tabuleiro: Matriz 10x10 inicializada com 0 (água)
    int tabuleiro[TABULEIRO_TAMANHO][TABULEIRO_TAMANHO];
    int linha, coluna; // Variáveis de controle para loops

    // Inicializa todas as posições do tabuleiro com 0
    for (linha = 0; linha < TABULEIRO_TAMANHO; linha++) {
        for (coluna = 0; coluna < TABULEIRO_TAMANHO; coluna++) {
            tabuleiro[linha][coluna] = 0; // 0 representa água
        }
    }

    // 2. Posicione os Navios:
    // Navio 1: Horizontal
    // Coordenadas de início (linha, coluna) para o navio horizontal.
    // Garantido que está dentro dos limites e não se sobrepõe ao outro navio.
    int navio1_linha_inicial = 2;
    int navio1_coluna_inicial = 1;
    bool navio1_posicionado = true; // Flag para verificar se o navio foi posicionado com sucesso

    // Validação de limites para o navio horizontal
    if (navio1_coluna_inicial + TAMANHO_NAVIO > TABULEIRO_TAMANHO) {
        printf("Erro: Navio Horizontal fora dos limites do tabuleiro!\n");
        navio1_posicionado = false;
    } else {
        // Posiciona o navio horizontal (valor 3)
        for (coluna = 0; coluna < TAMANHO_NAVIO; coluna++) {
            tabuleiro[navio1_linha_inicial][navio1_coluna_inicial + coluna] = 3; // 3 representa parte do navio
        }
    }

    // Navio 2: Vertical
    // Coordenadas de início (linha, coluna) para o navio vertical.
    // Garantido que está dentro dos limites e não se sobrepõe ao outro navio.
    int navio2_linha_inicial = 4;
    int navio2_coluna_inicial = 6;
    bool navio2_posicionado = true; // Flag para verificar se o navio foi posicionado com sucesso

    // Validação de limites para o navio vertical
    if (navio2_linha_inicial + TAMANHO_NAVIO > TABULEIRO_TAMANHO) {
        printf("Erro: Navio Vertical fora dos limites do tabuleiro!\n");
        navio2_posicionado = false;
    } else {
        // Posiciona o navio vertical (valor 3)
        for (linha = 0; linha < TAMANHO_NAVIO; linha++) {
            // Verifica sobreposição antes de posicionar (simplificado para este desafio)
            // No desafio, assume-se que as coordenadas são escolhidas para não sobrepor.
            // Aqui, apenas colocamos o valor 3.
            tabuleiro[navio2_linha_inicial + linha][navio2_coluna_inicial] = 3;
        }
    }
    
    // 3. Exiba o Tabuleiro
    printf("Tabuleiro de Batalha Naval (0 = Agua, 3 = Navio):\n");
    for (linha = 0; linha < TABULEIRO_TAMANHO; linha++) {
        for (coluna = 0; coluna < TABULEIRO_TAMANHO; coluna++) {
            printf("%d ", tabuleiro[linha][coluna]); // Imprime o valor da célula seguido de um espaço
        }
        printf("\n"); // Quebra de linha no final de cada linha do tabuleiro
    }
    printf("\n");

    return 0; // Indica que o programa terminou com sucesso
}
