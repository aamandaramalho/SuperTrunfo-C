#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- CONSTANTES E DEFINIÇÕES ---
#define MAX_ATRIBUTOS 4       // População, Área, PIB, Densidade
#define ATRIBUTO_ESPECIAL 3   // Índice da "Densidade Demográfica" (regra: menor valor vence)

// Estrutura da Carta
typedef struct {
    char nome[50];
    double valores[MAX_ATRIBUTOS]; 
} Carta;

// Nomes dos atributos para exibição e menu (Mapeamento do índice)
const char* nomes_atributos[MAX_ATRIBUTOS] = {
    "Populacao (Milhoes)", 
    "Area_Km2 (Milhoes)", 
    "PIB_Bilhoes (Trilhoes)", 
    "Densidade_Demografica (Menor Vence)" 
};

// --- FUNÇÕES DE SUPORTE: CARREGAMENTO DE CARTAS ---

// Função para popular as cartas com dados de países (JÁ COM SEUS DADOS)
void carregar_cartas(Carta *c1, Carta *c2) {
    // 1. Definição da Estrutura de Cartas
    // (Incluí mais cartas aqui, mas o desafio compara apenas 2)
    Carta cartas_disponiveis[] = {
        // Carta 0: BRASIL
        {"Brasil", {214.0, 8.51, 1.6, 25.1}},
        // Carta 1: FRANÇA
        {"Franca", {68.0, 0.64, 2.8, 105.0}},
        // Carta 2: CHINA
        {"China", {1412.0, 9.6, 17.7, 146.0}},
        // Carta 3: CANADÁ
        {"Canada", {38.0, 9.98, 2.2, 4.0}}
    };

    // Apenas copiamos as duas primeiras cartas para c1 e c2, como no desafio
    *c1 = cartas_disponiveis[0]; // Carta 1 é o Brasil
    *c2 = cartas_disponiveis[1]; // Carta 2 é a França
}

// --- FUNÇÕES DE INTERAÇÃO E LÓGICA ---

// Função para obter uma escolha de atributo válida e robusta
int obter_escolha_atributo(int atributo_ja_escolhido) {
    int escolha;
    
    do {
        printf("\n--- Escolha um Atributo (1 a %d) ---\n", MAX_ATRIBUTOS);
        for (int i = 0; i < MAX_ATRIBUTOS; i++) {
            // Requisito: Menus Dinâmicos - não exibe o atributo já escolhido
            if (i + 1 != atributo_ja_escolhido) {
                printf("%d. %s\n", i + 1, nomes_atributos[i]);
            }
        }
        printf("Sua opcao: ");
        
        // Entrada robusta: garante que é um número e limpa o buffer
        if (scanf("%d", &escolha) != 1) {
            printf("[ERRO] Entrada invalida. Digite um numero.\n");
            while (getchar() != '\n');
            escolha = 0;
            continue;
        }
        while (getchar() != '\n'); // Limpa o restante do buffer

        // Lógica de Validação: trata entradas inválidas ou repetidas
        if (escolha < 1 || escolha > MAX_ATRIBUTOS) {
            printf("[ERRO] Opcao fora do intervalo. Tente novamente.\n");
        } else if (escolha == atributo_ja_escolhido) {
            printf("[ALERTA] Atributo ja selecionado. Escolha outro.\n");
        } else {
            return escolha; // Escolha válida
        }
    } while (1);
}

// Função que gerencia a escolha dos dois atributos (Requisito 1)
void interacao_jogador(int *attr1_idx, int *attr2_idx) {
    int escolha1, escolha2;

    printf("\n>>> SELECIONE O PRIMEIRO ATRIBUTO: <<<\n");
    escolha1 = obter_escolha_atributo(0); 
    *attr1_idx = escolha1 - 1; 
    printf("[OK] Atributo 1 escolhido: %s\n", nomes_atributos[*attr1_idx]);
    
    printf("\n>>> SELECIONE O SEGUNDO ATRIBUTO: <<<\n");
    escolha2 = obter_escolha_atributo(escolha1); // Passa a primeira escolha
    *attr2_idx = escolha2 - 1; 
    printf("[OK] Atributo 2 escolhido: %s\n", nomes_atributos[*attr2_idx]);
}

// Função para comparar um atributo individualmente (Requisito 2)
// Retorna 1 se Carta A vence, 2 se Carta B vence, 0 se empate.
int comparar_atributo(double valorA, double valorB, int indice_atributo) {
    // Verifica a regra de exceção (Densidade Demográfica)
    if (indice_atributo == ATRIBUTO_ESPECIAL) {
        // Regra Especial: MENOR VALOR VENCE
        if (valorA < valorB) return 1; 
        if (valorB < valorA) return 2; 
    } else {
        // Regra Geral: MAIOR VALOR VENCE
        if (valorA > valorB) return 1; 
        if (valorB > valorA) return 2; 
    }
    return 0;
}

// Função principal de comparação e exibição de resultados (Requisito 3, 4 e 6)
void comparar_cartas(const Carta *c1, const Carta *c2, int idx1, int idx2) {
    double soma1, soma2;
    int resultado_attr1, resultado_attr2;
    
    // Comparações individuais (apenas para exibição dos placares individuais)
    resultado_attr1 = comparar_atributo(c1->valores[idx1], c2->valores[idx1], idx1);
    resultado_attr2 = comparar_atributo(c1->valores[idx2], c2->valores[idx2], idx2);
    
    // Cálculo da Soma dos Atributos (Critério de Vitória Principal - Requisito 3)
    soma1 = c1->valores[idx1] + c1->valores[idx2];
    soma2 = c2->valores[idx1] + c2->valores[idx2];

    // Uso do Operador Ternário para exibir o resultado de forma elegante
    const char* resultado_c1_attr1 = (resultado_attr1 == 1) ? "VENCE" : ((resultado_attr1 == 2) ? "PERDE" : "EMPATE");
    const char* resultado_c1_attr2 = (resultado_attr2 == 1) ? "VENCE" : ((resultado_attr2 == 2) ? "PERDE" : "EMPATE");

    // --- Exibição Clara do Resultado (Requisito 6) ---
    printf("\n=========================================================\n");
    printf("                  RELATORIO DE RODADA\n");
    printf("=========================================================\n");

    printf("ATRIBUTOS: 1. %s | 2. %s\n", nomes_atributos[idx1], nomes_atributos[idx2]);
    printf("---------------------------------------------------------\n");
    printf("| %-22s | %-18s | %-18s |\n", "DADOS", c1->nome, c2->nome);
    printf("---------------------------------------------------------\n");
    
    // Exibe Atributo 1
    printf("| %-22s | %18.2lf | %18.2lf |\n", nomes_atributos[idx1], c1->valores[idx1], c2->valores[idx1]);
    
    // Exibe Atributo 2
    printf("| %-22s | %18.2lf | %18.2lf |\n", nomes_atributos[idx2], c1->valores[idx2], c2->valores[idx2]);
           
    printf("---------------------------------------------------------\n");
    printf("| %-22s | %18.2lf | %18.2lf |\n", "SOMA TOTAL", soma1, soma2);
    printf("=========================================================\n");

    // Exibe Placar Individual (Apenas informativa, a soma decide)
    printf("\nPLACARES INDIVIDUAIS (Informativo):\n");
    printf("- %s no primeiro atributo: %s\n", c1->nome, resultado_c1_attr1);
    printf("- %s no segundo atributo: %s\n", c1->nome, resultado_c1_attr2);
    
    // Vencedor pela Soma (Requisito 4: Tratamento de Empates)
    printf("\n--- VENCEDOR DA RODADA (PELA SOMA) ---\n");
    if (soma1 > soma2) {
        printf(">>> VITORIA! %s VENCE com a soma de %.2lf! <<<\n", c1->nome, soma1);
    } else if (soma2 > soma1) {
        printf(">>> VITORIA! %s VENCE com a soma de %.2lf! <<<\n", c2->nome, soma2);
    } else {
        printf(">>> EMPATE! A soma dos atributos (%.2lf) foi igual. <<<\n", soma1);
    }
    printf("=========================================================\n");
}

// --- FUNÇÃO PRINCIPAL ---
int main() {
    Carta carta1, carta2;
    int attr_indice1 = -1, attr_indice2 = -1;

    // Carrega as cartas (Brasil e França)
    carregar_cartas(&carta1, &carta2);
    
    printf("=========================================================\n");
    printf("        SUPER TRUNFO AVANCADO: DESAFIO FINAL\n");
    printf("=========================================================\n");
    printf("CARTAS EM JOGO:\n");
    printf("Carta 1: %s\n", carta1.nome);
    printf("Carta 2: %s\n", carta2.nome);

    // 1. Interação e Escolha dos Atributos
    interacao_jogador(&attr_indice1, &attr_indice2);

    // 2. Comparação e Exibição do Resultado
    comparar_cartas(&carta1, &carta2, attr_indice1, attr_indice2);

    return 0;
}