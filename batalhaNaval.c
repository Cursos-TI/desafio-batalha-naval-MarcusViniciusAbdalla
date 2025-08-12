#include <stdio.h>   // Biblioteca padrão para entrada e saída de dados
#include <stdbool.h> // Para usar tipos booleanos (true/false)
#include <stdlib.h>  // Para usar abs() para o cálculo das formas das habilidades

// --- Constantes para o Tabuleiro de Batalha Naval ---
#define TABULEIRO_TAMANHO 10 // Tabuleiro 10x10
#define TAMANHO_NAVIO 3      // Navios de 3 posições
#define VALOR_AGUA 0         // Representa água no tabuleiro
#define VALOR_NAVIO 3        // Representa parte de um navio no tabuleiro
#define VALOR_HABILIDADE 5   // Representa área afetada por habilidade

// --- Constantes para as Matrizes de Habilidade ---
#define HABILIDADE_TAMANHO 7 // Tamanho das matrizes de habilidade (ex: 7x7)
#define HABILIDADE_CENTRO (HABILIDADE_TAMANHO / 2) // Centro para cálculos de forma

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
        if (tabuleiro[r][c] != VALOR_AGUA) { // Se não for água, já está ocupado
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
        tabuleiro[r][c] = VALOR_NAVIO; // Marca a posição como parte do navio
    }
}

// Função para exibir o tabuleiro de Batalha Naval com diferentes caracteres
void exibirTabuleiro(int tabuleiro[TABULEIRO_TAMANHO][TABULEIRO_TAMANHO]) {
    int r_tab, c_tab; // Variáveis de controle para loops do tabuleiro

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
            // Usa caracteres diferentes para representar água, navio e área de habilidade
            if (tabuleiro[r_tab][c_tab] == VALOR_AGUA) {
                printf("~ "); // Água
            } else if (tabuleiro[r_tab][c_tab] == VALOR_NAVIO) {
                printf("N "); // Navio
            } else if (tabuleiro[r_tab][c_tab] == VALOR_HABILIDADE) {
                printf("A "); // Área de Habilidade
            } else {
                printf("%d ", tabuleiro[r_tab][c_tab]); // Qualquer outro valor inesperado
            }
        }
        printf("|\n"); // Quebra de linha no final de cada linha do tabuleiro
    }
    printf("  --------------------------------\n"); // Separador final
    printf("\n");
}

// Função para criar a matriz de habilidade em forma de CONE (apontando para baixo)
void criarHabilidadeCone(int matriz_habilidade[HABILIDADE_TAMANHO][HABILIDADE_TAMANHO]) {
    int r, c;
    for (r = 0; r < HABILIDADE_TAMANHO; r++) {
        for (c = 0; c < HABILIDADE_TAMANHO; c++) {
            // Lógica para formar um cone apontando para baixo
            // O centro da base do cone está no meio da última linha (HABILIDADE_CENTRO)
            // A largura do cone aumenta com a linha 'r'
            // abs(c - HABILIDADE_CENTRO) calcula a distância horizontal do centro
            if (abs(c - HABILIDADE_CENTRO) <= r) {
                matriz_habilidade[r][c] = 1;
            } else {
                matriz_habilidade[r][c] = 0;
            }
        }
    }
}

// Função para criar a matriz de habilidade em forma de CRUZ
void criarHabilidadeCruz(int matriz_habilidade[HABILIDADE_TAMANHO][HABILIDADE_TAMANHO]) {
    int r, c;
    for (r = 0; r < HABILIDADE_TAMANHO; r++) {
        for (c = 0; c < HABILIDADE_TAMANHO; c++) {
            // Lógica para formar uma cruz centrada
            if (r == HABILIDADE_CENTRO || c == HABILIDADE_CENTRO) {
                matriz_habilidade[r][c] = 1;
            } else {
                matriz_habilidade[r][c] = 0;
            }
        }
    }
}

// Função para criar a matriz de habilidade em forma de OCTAEDRO (losango)
void criarHabilidadeOctaedro(int matriz_habilidade[HABILIDADE_TAMANHO][HABILIDADE_TAMANHO]) {
    int r, c;
    int raio = HABILIDADE_CENTRO; // Raio máximo do losango (distância do centro até a borda)

    for (r = 0; r < HABILIDADE_TAMANHO; r++) {
        for (c = 0; c < HABILIDADE_TAMANHO; c++) {
            // Lógica para formar um losango (octaedro 2D)
            // abs(r - HABILIDADE_CENTRO) + abs(c - HABILIDADE_CENTRO) calcula a "distância Manhattan" do centro
            if (abs(r - HABILIDADE_CENTRO) + abs(c - HABILIDADE_CENTRO) <= raio) {
                matriz_habilidade[r][c] = 1;
            } else {
                matriz_habilidade[r][c] = 0;
            }
        }
    }
}

// Função para aplicar a área de efeito de uma habilidade ao tabuleiro principal
// origin_row, origin_col: centro da habilidade no tabuleiro principal.
void aplicarHabilidadeAoTabuleiro(int tabuleiro[TABULEIRO_TAMANHO][TABULEIRO_TAMANHO],
                                 int matriz_habilidade[HABILIDADE_TAMANHO][HABILIDADE_TAMANHO],
                                 int origin_row, int origin_col) {
    int r_hab, c_hab; // Coordenadas na matriz de habilidade
    int r_tab, c_tab; // Coordenadas correspondentes no tabuleiro principal

    // Itera sobre a matriz de habilidade
    for (r_hab = 0; r_hab < HABILIDADE_TAMANHO; r_hab++) {
        for (c_hab = 0; c_hab < HABILIDADE_TAMANHO; c_hab++) {
            // Se a célula na matriz de habilidade é afetada (valor 1)
            if (matriz_habilidade[r_hab][c_hab] == 1) {
                // Calcula a coordenada correspondente no tabuleiro principal,
                // centrando a habilidade no ponto de origem.
                r_tab = origin_row + (r_hab - HABILIDADE_CENTRO);
                c_tab = origin_col + (c_hab - HABILIDADE_CENTRO);

                // --- Validação de Limites ---
                // Verifica se a posição calculada está dentro dos limites do tabuleiro principal
                if (r_tab >= 0 && r_tab < TABULEIRO_TAMANHO &&
                    c_tab >= 0 && c_tab < TABULEIRO_TAMANHO) {
                    // --- Sobreposição da Habilidade ---
                    // Se a posição no tabuleiro principal é água (0), marca como área de habilidade (5).
                    // Navios (3) permanecem como navios, não são sobrescritos por habilidades visuais neste nível.
                    if (tabuleiro[r_tab][c_tab] == VALOR_AGUA) {
                        tabuleiro[r_tab][c_tab] = VALOR_HABILIDADE;
                    }
                }
            }
        }
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
    // --- Batalha Naval: Posicionando Navios e Habilidades ---
    // ==========================================================
    printf("========================================\n");
    printf("--- Batalha Naval: Posicionamento e Habilidades ---\n");
    printf("========================================\n\n");

    // 1. Represente o Tabuleiro: Matriz 10x10 inicializada com 0 (água)
    int tabuleiro[TABULEIRO_TAMANHO][TABULEIRO_TAMANHO];
    int r_tab, c_tab; // Variáveis de controle para loops do tabuleiro

    // Inicializa todas as posições do tabuleiro com VALOR_AGUA
    for (r_tab = 0; r_tab < TABULEIRO_TAMANHO; r_tab++) {
        for (c_tab = 0; c_tab < TABULEIRO_TAMANHO; c_tab++) {
            tabuleiro[r_tab][c_tab] = VALOR_AGUA;
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
        printf("Erro: Nao foi possivel posicionar Navio 1 (Horizontal) em (%d,%d).\n", n1_r, n1_c);
    }

    // Navio 2: Vertical
    // Coordenadas de início: linha 4, coluna 6
    int n2_r = 4, n2_c = 6;
    if (canPlaceShip(tabuleiro, n2_r, n2_c, TAMANHO_NAVIO, VERTICAL)) {
        placeShip(tabuleiro, n2_r, n2_c, TAMANHO_NAVIO, VERTICAL);
        printf("Navio 2 (Vertical) posicionado com sucesso em (%d,%d).\n", n2_r, n2_c);
    } else {
        printf("Erro: Nao foi possivel posicionar Navio 2 (Vertical) em (%d,%d).\n", n2_r, n2_c);
    }

    // Navio 3: Diagonal (Linha aumenta, Coluna aumenta) - DIAGONAL_DOWN_RIGHT
    // Coordenadas de início: linha 0, coluna 0 (superior esquerda)
    // Movimento: (0,0) -> (1,1) -> (2,2)
    int n3_r = 0, n3_c = 0;
    if (canPlaceShip(tabuleiro, n3_r, n3_c, TAMANHO_NAVIO, DIAGONAL_DOWN_RIGHT)) {
        placeShip(tabuleiro, n3_r, n3_c, TAMANHO_NAVIO, DIAGONAL_DOWN_RIGHT);
        printf("Navio 3 (Diagonal Baixo-Direita) posicionado com sucesso em (%d,%d).\n", n3_r, n3_c);
    } else {
        printf("Erro: Nao foi possivel posicionar Navio 3 (Diagonal Baixo-Direita) em (%d,%d).\n", n3_r, n3_c);
    }

    // Navio 4: Diagonal (Linha diminui, Coluna aumenta) - DIAGONAL_UP_RIGHT
    // Coordenadas de início: linha 2, coluna 7 (para ir para (1,8) e (0,9))
    // Movimento: (2,7) -> (1,8) -> (0,9)
    int n4_r = 2, n4_c = 7;
    if (canPlaceShip(tabuleiro, n4_r, n4_c, TAMANHO_NAVIO, DIAGONAL_UP_RIGHT)) {
        placeShip(tabuleiro, n4_r, n4_c, TAMANHO_NAVIO, DIAGONAL_UP_RIGHT);
        printf("Navio 4 (Diagonal Cima-Direita) posicionado com sucesso em (%d,%d).\n", n4_r, n4_c);
    } else {
        printf("Erro: Nao foi possivel posicionar Navio 4 (Diagonal Cima-Direita) em (%d,%d).\n", n4_r, n4_c);
    }
    printf("\n");

    // Exibe o tabuleiro após o posicionamento dos navios
    printf("--- Tabuleiro com Navios Posicionados ---\n");
    exibirTabuleiro(tabuleiro);
    printf("\n");

    // === HABILIDADES ESPECIAIS E ÁREAS DE EFEITO ===
    printf("========================================\n");
    printf("--- Habilidades Especiais (Areas de Efeito) ---\n");
    printf("========================================\n\n");

    // 1. Criar Matrizes de Habilidade: Cone, Cruz, Octaedro
    int cone_habilidade[HABILIDADE_TAMANHO][HABILIDADE_TAMANHO];
    int cruz_habilidade[HABILIDADE_TAMANHO][HABILIDADE_TAMANHO];
    int octaedro_habilidade[HABILIDADE_TAMANHO][HABILIDADE_TAMANHO];

    // Preenche as matrizes de habilidade
    criarHabilidadeCone(cone_habilidade);
    criarHabilidadeCruz(cruz_habilidade);
    criarHabilidadeOctaedro(octaedro_habilidade);

    printf("Matriz de Habilidade - CONE:\n");
    for (int r = 0; r < HABILIDADE_TAMANHO; r++) {
        for (int c = 0; c < HABILIDADE_TAMANHO; c++) {
            printf("%d ", cone_habilidade[r][c]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Matriz de Habilidade - CRUZ:\n");
    for (int r = 0; r < HABILIDADE_TAMANHO; r++) {
        for (int c = 0; c < HABILIDADE_TAMANHO; c++) {
            printf("%d ", cruz_habilidade[r][c]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Matriz de Habilidade - OCTAEDRO:\n");
    for (int r = 0; r < HABILIDADE_TAMANHO; r++) {
        for (int c = 0; c < HABILIDADE_TAMANHO; c++) {
            printf("%d ", octaedro_habilidade[r][c]);
        }
        printf("\n");
    }
    printf("\n");


    // 2. Integrar Habilidades ao Tabuleiro: Definir origem e sobrepor

    // Aplicar Habilidade CONE
    // Origem: Linha 2, Coluna 5 (centro do cone no tabuleiro)
    printf("--- Aplicando Habilidade CONE no tabuleiro (Origem: [2,5]) ---\n");
    aplicarHabilidadeAoTabuleiro(tabuleiro, cone_habilidade, 2, 5);
    exibirTabuleiro(tabuleiro); // Exibe o tabuleiro com a área de efeito
    printf("\n");

    // IMPORTANTE: Para ver os efeitos de cada habilidade individualmente,
    // você pode re-inicializar o tabuleiro ou testar um de cada vez.
    // Para este exemplo, as habilidades se sobreporão nas posições de água (0).
    // Para fins de demonstração clara, vou re-inicializar o tabuleiro e os navios
    // antes de cada nova aplicação de habilidade no tabuleiro para melhor visualização
    // de cada área de efeito.

    // Re-inicializa o tabuleiro para a próxima demonstração de habilidade
    for (r_tab = 0; r_tab < TABULEIRO_TAMANHO; r_tab++) {
        for (c_tab = 0; c_tab < TABULEIRO_TAMANHO; c_tab++) {
            tabuleiro[r_tab][c_tab] = VALOR_AGUA;
        }
    }
    // Re-posiciona os navios
    placeShip(tabuleiro, n1_r, n1_c, TAMANHO_NAVIO, HORIZONTAL);
    placeShip(tabuleiro, n2_r, n2_c, TAMANHO_NAVIO, VERTICAL);
    placeShip(tabuleiro, n3_r, n3_c, TAMANHO_NAVIO, DIAGONAL_DOWN_RIGHT);
    placeShip(tabuleiro, n4_r, n4_c, TAMANHO_NAVIO, DIAGONAL_UP_RIGHT);


    // Aplicar Habilidade CRUZ
    // Origem: Linha 5, Coluna 5 (centro da cruz no tabuleiro)
    printf("--- Aplicando Habilidade CRUZ no tabuleiro (Origem: [5,5]) ---\n");
    aplicarHabilidadeAoTabuleiro(tabuleiro, cruz_habilidade, 5, 5);
    exibirTabuleiro(tabuleiro);
    printf("\n");

    // Re-inicializa o tabuleiro para a próxima demonstração de habilidade
    for (r_tab = 0; r_tab < TABULEIRO_TAMANHO; r_tab++) {
        for (c_tab = 0; c_tab < TABULEIRO_TAMANHO; c_tab++) {
            tabuleiro[r_tab][c_tab] = VALOR_AGUA;
        }
    }
    // Re-posiciona os navios
    placeShip(tabuleiro, n1_r, n1_c, TAMANHO_NAVIO, HORIZONTAL);
    placeShip(tabuleiro, n2_r, n2_c, TAMANHO_NAVIO, VERTICAL);
    placeShip(tabuleiro, n3_r, n3_c, TAMANHO_NAVIO, DIAGONAL_DOWN_RIGHT);
    placeShip(tabuleiro, n4_r, n4_c, TAMANHO_NAVIO, DIAGONAL_UP_RIGHT);

    // Aplicar Habilidade OCTAEDRO
    // Origem: Linha 7, Coluna 2 (centro do octaedro/losango no tabuleiro)
    printf("--- Aplicando Habilidade OCTAEDRO no tabuleiro (Origem: [7,2]) ---\n");
    aplicarHabilidadeAoTabuleiro(tabuleiro, octaedro_habilidade, 7, 2);
    exibirTabuleiro(tabuleiro);
    printf("\n");


    return 0; // Indica que o programa terminou com sucesso
}
