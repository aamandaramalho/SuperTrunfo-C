# SuperTrunfo-C
# Projeto Final: Super Trunfo Avançado em C

Este projeto implementa o desafio final do Super Trunfo em C, focando na integração dos requisitos: menus dinâmicos, soma de atributos, tratamento de empates e exibição organizada do resultado.

## Requisitos Implementados

1.  **Escolha de Dois Atributos** diferentes.
2.  **Soma dos Atributos** para a comparação final.
3.  **Tratamento de Empates** ("Empate!").
4.  **Menus Dinâmicos** (o 1º atributo não aparece na 2ª escolha).
5.  **Exceção da Regra**: Densidade Demográfica é o menor valor que vence.

## Como Compilar e Executar

Para rodar o programa, é necessário ter o compilador **GCC** (MinGW) instalado.

1.  **Baixe** o arquivo `supertrunfo.c` e salve em uma pasta.
2.  **Abra o Terminal** (ou Prompt de Comando) nesta pasta.
3.  **Compile** o código:
    ```bash
    gcc supertrunfo.c -o trunfo.exe
    ```
4.  **Execute** o jogo:
    ```bash
    ./trunfo.exe
    ```

## Atributos Disponíveis

O jogo compara as cartas com base nos seguintes atributos:
1. Populacao (Milhões)
2. Area_Km2 (Milhões)
3. PIB_Bilhoes (Trilhões)
4. Densidade_Demografica (Menor Vence)
