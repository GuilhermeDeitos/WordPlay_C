//Guilherme Deitos
#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"
#include <string.h>

//Biblioteca para usar o sleep
#ifdef _WIN32 || _WIN64
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

int main()
{
    char palavrasOriginal[5][20] = {"elixir", "python", "javascript", "java", "c"}; //Palavras que serão adivinhadas
    char palavrasAdvinhadas[5][20] = {"******", "******", "**********", "****", "*"}; //Palavras que serão mostradas ao usuário, com '*' no lugar das letras
    char dicas[5][100] = {"Linguagem desenvolvida por brasileiros", "Linguagem de programacao mais popular", "Linguagem de programacao feita em 10 dias", "Linguagem de programacao em que o jogo Minecraft foi feito", "Linguagem de programacao utilizada como base para a criacao de diversas outras linguagens"};
    char palavra[20], letra, letraAdvinhada;
    int linhaAdvinhada, errosByWord = 0, errosByLetter = 0, jogoCompleto = 0, opcao;

    mostrarMenu(palavrasOriginal, palavrasAdvinhadas, letraAdvinhada, linhaAdvinhada, opcao);

    printf("Dicas: \n");
    for (int i = 0; i < 5; i++)
    {
        printf("%d - %s \n", i + 1, dicas[i]);
    }
    printf("Numero de tentativas: \n[1] Adivinhar palavra (1 tentativa) \n[2] Adivinhar letra (7 tentativas) \n[0] Sair \n");
    scanf("%d", &opcao);
    do
    {
        jogoCompleto = verifyWin(palavrasOriginal, palavrasAdvinhadas); //Verifica se o jogo acabou

        if (errosByLetter <= 7 && errosByWord <= 1 && jogoCompleto == 0) //Verifica se o jogo ainda não acabou e se o usuário ainda tem tentativas
        {
            switch (opcao)
            {
            case 1:
                do
                {
                    printf("Digite a palavra: ");
                    scanf("%s", palavra);
                    linhaAdvinhada = guessByWord(palavra, palavrasOriginal);
                    verificaRepetida(letra, palavra, palavrasAdvinhadas, opcao); //Verifica se a palavra já foi adivinhada

                    if (linhaAdvinhada == -1) //Se a palavra não for encontrada, o usuário perde uma tentativa
                    {
                        errosByWord++;
                        printf("Voce errou! Voce tem mais %d tentativas \n", 2 - errosByWord);
                    }
                    else
                    {
                        break;
                    }
                } while (errosByWord <= 1);
                break;
            case 2:
                do
                {
                    printf("Digite a letra: ");
                    scanf(" %c", &letra);
                    letraAdvinhada = guessByLetter(letra, palavrasOriginal);
                    verificaRepetida(letra, palavra, palavrasAdvinhadas, opcao); //Verifica se a letra já foi adivinhada
                    if (letraAdvinhada == '*')
                    {
                        errosByLetter++;
                        printf("Voce errou! Voce tem mais %d tentativas \n", 8 - errosByLetter);
                    }
                    else
                    {
                        break;
                    }
                } while (errosByLetter <= 7); //Se a letra não for encontrada, o usuário perde uma tentativa
                break;
            case 0:
                printf("Saindo...");
                break;
            default:
                printf("Opcao inválida");
                break;
            }
            system("cls"); //Limpa a tela
            mostrarMenu(palavrasOriginal, palavrasAdvinhadas, letraAdvinhada, linhaAdvinhada, opcao);
            printf("Dicas: \n");
            for (int i = 0; i < 5; i++)
            {
                printf("%d - %s \n", i + 1, dicas[i]);
            }
        }
        else if (jogoCompleto == 1) //Se o jogo acabar, o usuário ganha
        {
            system("cls"); //Limpa a tela
            printf("Parabéns! Voce ganhou!");
            mostrarMenu(palavrasOriginal, palavrasAdvinhadas, letraAdvinhada, linhaAdvinhada, 3);
            break;
        }
        else //Se o usuário atingir o limite de tentativas, o jogo acaba
        {
            system("cls");
            printf("Limite de tentativas atingido!\nGabarito\n");
            mostrarMenu(palavrasOriginal, palavrasAdvinhadas, letraAdvinhada, linhaAdvinhada, 3);
            break;
        }

    } while (opcao != 0);
    return 0;
}
