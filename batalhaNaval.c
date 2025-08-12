#include <stdio.h>   // Biblioteca padrão para entrada e saída de dados
#include <stdbool.h> // Para usar tipos booleanos (true/false)

// --- Constantes para o Tabuleiro de Batalha Naval ---
#define TABULEIRO_TAMANHO 10 // Tabuleiro 10x10
#define TAMANHO_NAVIO 3      // Navios de 3 posições

// Enumeração para tipos de orientação de navio
// Torna o código mais legível e robusto para definir a orientação dos navios.
typedef enum {
    HORIZONTAL,
    VERTICAL,
    DIAGONAL_UP_RIGHT,   // Linha diminui, coluna aumenta (ex: (2,0) -> (1,1) -> (0,2))
    DIAGONAL_DOWN_RIGHT  // Linha aumenta, coluna aumenta (ex: (0,0) -> (1,1) -> (2,2))
} OrientacaoNavio;


// --- Funções Recursivas para Movimento das Peças de Xadrez ---
// (Estas funções permanecem inalteradas do desafio anterior)

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


// --- Funções Auxiliares para Batalha Naval ---

// Função para verificar se um navio pode ser posicionado no tabuleiro
// Verifica se todas as posições do navio estão dentro dos limites do tabuleiro
// e se não estão ocupadas por outras partes de navio (valor 3).
// Retorna true se o posicionamento é válido, false caso contrário.
bool canPlaceShip(int tabuleiro[TABULEIRO_TAMANHO][TABULEIRO_TAMANHO],
                  int start_row, int start_col, int size, OrientacaoNavio orientation) {
    int r, c; // Variáveis para as coordenadas atuais dentro do loop

    for (int i = 0; i < size; i++) {
        // Calcula as coordenadas da posição atual do navio com base na orientação
        if (orientation == HORIZONTAL) {
            r = start_row;
            c = start_col + i;
        } else if (orientation == VERTICAL) {
            r = start_row + i;
            c = start_col;
        } else if (orientation == DIAGONAL_DOWN_RIGHT) { // Linha aumenta, coluna aumenta
            r = start_row + i;
            c = start_col + i;
        } else if (orientation == DIAGONAL_UP_RIGHT) { // Linha diminui, coluna aumenta
            r = start_row - i;
            c = start_col + i;
        } else {
            // Caso de orientação inválida, embora o enum restrinja isso
            return false;
        }

        // --- Validação de Limites ---
        // Verifica se a posição calculada está dentro dos limites do tabuleiro (0 a TABULEIRO_TAMANHO-1)
        if (r < 0 || r >= TABULEIRO_TAMANHO || c < 0 || c >= TABULEIRO_TAMANHO) {
            return false; // Fora dos limites do tabuleiro
        }

        // --- Validação de Sobreposição ---
        // Verifica se a posição já está ocupada por outro navio (valor 3)
        if (tabuleiro[r][c] != 0) {
            return false; // Sobreposição detectada
        }
    }
    return true; // Se todas as verificações passarem, o posicionamento é válido
}

// Função para posicionar um navio no tabuleiro
// Esta função assume que 'canPlaceShip' já foi chamada e confirmou que o posicionamento é válido.
// Ela simplesmente marca as posições no tabuleiro com o valor '3' (parte do navio).
void placeShip(int tabuleiro[TABULEIRO_TAMANHO][TABULEIRO_TAMANHO],
               int start_row, int start_col, int size, OrientacaoNavio orientation) {
    int r, c; // Variáveis para as coordenadas atuais dentro do loop

    for (int i = 0; i < size; i++) {
        // Calcula as coordenadas da posição atual do navio com base na orientação
        if (orientation == HORIZONTAL) {
            r = start_row;
            c = start_col + i;
        } else if (orientation == VERTICAL) {
            r = start_row + i;
            c = start_col;
        } else if (orientation == DIAGONAL_DOWN_RIGHT) {
            r = start_row + i;
            c = start_col + i;
        } else if (orientation == DIAGONAL_UP_RIGHT) {
            r = start_row - i;
            c = start_col + i;
        }
        tabuleiro[r][c] = 3; // Marca a posição como parte do navio
    }
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
    int x_cavalo = 0;
    while (x_cavalo < passos_horizontais) {
        passo_total++;
        printf("Passo %d do Cavalo: Direita\n", passo_total);
        x_cavalo++;
        // Exemplo de uso de 'break' (não estritamente necessário aqui, mas demonstra o uso):
        // if (x_cavalo == 1) break; // Poderia parar após o primeiro passo horizontal
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
    // (Nível Aventureiro: Tabuleiro Completo e Navios Diagonais)
    // ==========================================================
    printf("========================================\n");
    printf("--- Batalha Naval: Posicionando Navios ---\n");
    printf("========================================\n\n");

    // 1. Represente o Tabuleiro: Matriz 10x10 inicializada com 0 (água)
    int tabuleiro[TABULEIRO_TAMANHO][TABULEIRO_TAMANHO];
    int r_tab, c_tab; // Variáveis de controle para loops do tabuleiro

    // Inicializa todas as posições do tabuleiro com 0 (água)
    for (r_tab = 0; r_tab < TABULEIRO_TAMANHO; r_tab++) {
        for (c_tab = 0; c_tab < TABULEIRO_TAMANHO; c_tab++) {
            tabuleiro[r_tab][c_tab] = 0; // 0 representa água
        }
    }

    // 2. Posicione Quatro Navios:
    // Navio 1: Horizontal
    // Coordenadas de início: linha 2, coluna 1
    int n1_r = 2, n1_c = 1;
    if (canPlaceShip(tabuleiro, n1_r, n1_c, TAMANHO_NAVIO, HORIZONTAL)) {
        placeShip(tabuleiro, n1_r, n1_c, TAMANHO_NAVIO, HORIZONTAL);
        printf("Navio 1 (Horizontal) posicionado com sucesso em (%d,%d).\n", n1_r, n1_c);
    } else {
        printf("Erro: Nao foi possivel posicionar Navio 1 (Horizontal) em (%d,%d). "
               "Verifique limites ou sobreposicao.\n", n1_r, n1_c);
    }

    // Navio 2: Vertical
    // Coordenadas de início: linha 4, coluna 6
    int n2_r = 4, n2_c = 6;
    if (canPlaceShip(tabuleiro, n2_r, n2_c, TAMANHO_NAVIO, VERTICAL)) {
        placeShip(tabuleiro, n2_r, n2_c, TAMANHO_NAVIO, VERTICAL);
        printf("Navio 2 (Vertical) posicionado com sucesso em (%d,%d).\n", n2_r, n2_c);
    } else {
        printf("Erro: Nao foi possivel posicionar Navio 2 (Vertical) em (%d,%d). "
               "Verifique limites ou sobreposicao.\n", n2_r, n2_c);
    }

    // Navio 3: Diagonal (Linha aumenta, Coluna aumenta) - DIAGONAL_DOWN_RIGHT
    // Coordenadas de início: linha 0, coluna 0 (superior esquerda)
    // Movimento: (0,0) -> (1,1) -> (2,2)
    int n3_r = 0, n3_c = 0;
    if (canPlaceShip(tabuleiro, n3_r, n3_c, TAMANHO_NAVIO, DIAGONAL_DOWN_RIGHT)) {
        placeShip(tabuleiro, n3_r, n3_c, TAMANHO_NAVIO, DIAGONAL_DOWN_RIGHT);
        printf("Navio 3 (Diagonal Baixo-Direita) posicionado com sucesso em (%d,%d).\n", n3_r, n3_c);
    } else {
        printf("Erro: Nao foi possivel posicionar Navio 3 (Diagonal Baixo-Direita) em (%d,%d). "
               "Verifique limites ou sobreposicao.\n", n3_r, n3_c);
    }

    // Navio 4: Diagonal (Linha diminui, Coluna aumenta) - DIAGONAL_UP_RIGHT
    // Coordenadas de início: linha 2, coluna 7 (para ir para (1,8) e (0,9))
    // Movimento: (2,7) -> (1,8) -> (0,9)
    int n4_r = 2, n4_c = 7;
    if (canPlaceShip(tabuleiro, n4_r, n4_c, TAMANHO_NAVIO, DIAGONAL_UP_RIGHT)) {
        placeShip(tabuleiro, n4_r, n4_c, TAMANHO_NAVIO, DIAGONAL_UP_RIGHT);
        printf("Navio 4 (Diagonal Cima-Direita) posicionado com sucesso em (%d,%d).\n", n4_r, n4_c);
    } else {
        printf("Erro: Nao foi possivel posicionar Navio 4 (Diagonal Cima-Direita) em (%d,%d). "
               "Verifique limites ou sobreposicao.\n", n4_r, n4_c);
    }
    printf("\n");

    // 3. Exiba o Tabuleiro Completo
    printf("Tabuleiro de Batalha Naval (0 = Agua, 3 = Navio):\n");
    // Imprime cabeçalho de colunas para melhor visualização
    printf("   "); // Espaço para o número da linha
    for (c_tab = 0; c_tab < TABULEIRO_TAMANHO; c_tab++) {
        printf("%d ", c_tab); // Números das colunas
    }
    printf("\n");
    printf("  --------------------------------\n"); // Separador visual

    for (r_tab = 0; r_tab < TABULEIRO_TAMANHO; r_tab++) {
        printf("%d |", r_tab); // Imprime o número da linha e um separador
        for (c_tab = 0; c_tab < TABULEIRO_TAMANHO; c_tab++) {
            printf("%d ", tabuleiro[r_tab][c_tab]); // Imprime o valor da célula (0 ou 3)
        }
        printf("|\n"); // Quebra de linha no final de cada linha do tabuleiro
    }
    printf("  --------------------------------\n"); // Separador final
    printf("\n");

    return 0; // Indica que o programa terminou com sucesso
}