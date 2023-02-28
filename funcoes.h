//Guilherme Deitos
void mostrarMenu(char palavras[5][20], char palavrasAdvinhadas[5][20], char letraAdvinhada, int linhaAdvinhada, int opcao)
{
    // Opção 1 = Adivinhar palavra
    // Opção 2 = Adivinhar letra
    // Opção 3 = Gabarito
    int i;
    printf("=-=-=-=-=-=--=-= WORD PLAY - Guilherme Deitos =-=-=-=-=-=--=-=\n");
    for (i = 0; i < 5; i++)
    {
        int j;
        printf("%d -", i + 1);
        for (j = 0; j < 20; j++)
        {
            if (opcao == 3) //Se o usuário escolher a opção 3, o gabarito é mostrado
            {
                if (hasLetter(palavras[i][j])) //Verifica se a posição da matriz é uma letra
                {
                    printf("| %c |", palavras[i][j]);  //Se for, mostra a letra
                }
                else
                {
                    printf("| * |"); //Se não for, mostra um asterisco
                }
            }
            else
            {
                if (palavrasAdvinhadas[i][j] == '*') //Verifica se o espaço do vetor deveria conter uma letra(mascara feita utilizando '*')
                {

                    if (opcao == 2) //Se o usuário escolher a opção 2, a letra é mostrada
                    {
                        if (letraAdvinhada == palavras[i][j]) //Verifica se a letra está em alguma palavra
                        {
                            palavrasAdvinhadas[i][j] = palavras[i][j];  //Se estiver, a matriz com a mascara do usuário é atualizada com a letra
                            printf("| %c |", palavrasAdvinhadas[i][j]);
                        }
                        else
                        {
                            printf("|   |"); //Se não estiver, mostra um espaço vazio
                        }
                    }
                    else if (opcao == 1) //Se o usuário escolher a opção 1, a palavra é mostrada
                    {
                        if (linhaAdvinhada == i) //Verifica se a linhas da matriz é a mesma retornada pela função guessByWord
                        {
                            palavrasAdvinhadas[i][j] = palavras[i][j]; //Se for, a matriz com a mascara do usuário é atualizada com a palavra
                            printf("| %c |", palavrasAdvinhadas[i][j]);
                        }
                        else
                        {
                            printf("|   |"); //Se não for, mostra um espaço vazio
                        }
                    }
                    else
                    {
                        printf("|   |");
                    }
                }
                else if (hasLetter(palavrasAdvinhadas[i][j])) //Caso não seja um '*' pode ser uma letra, entao é verificado isso
                {
                    printf("| %c |", palavrasAdvinhadas[i][j]); //Se for uma letra, mostra a letra
                }
                else //Se não for um '*' nem uma letra, mostra um asterisco
                {
                    printf("| * |");
                }
            }
        }
        printf("\n");
    }
}

int verifyWin(char palavras[5][20], char palavrasAdvinhadas[5][20]) //Verifica se o usuário ganhou
{
    int i, j;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 20; j++)
        {
            if (palavras[i][j] != palavrasAdvinhadas[i][j]) //Verifica se a matriz com a mascara do usuário é igual a matriz com as palavras
            {
                return 0; //Se não for, retorna 0(falso)
            }
        }
    }
    return 1; //Se for, retorna 1(verdadeiro)
}

void verificaRepetida(char letra, char palavra[20], char palavras[5][20], int opcao) //Verifica se a letra ou palavra já foi escolhida
{
    int i, j, ehRepetida = 0;
    for (i = 0; i < 5; i++)
    {
        if(opcao == 1){ //Se a opção for 1, a palavra é verificada
            if(strcmp(palavra, palavras[i]) == 0) ehRepetida = 1; //Se a palavra for igual a alguma palavra da matriz mascara, ehRepetida é atualizada
        } else if(opcao == 2){ //Se a opção for 2, a letra é verificada
            for (j = 0; j < 20; j++)
            {
                if (letra == palavras[i][j]) ehRepetida = 1;  //Se a letra for igual a alguma letra da matriz mascara, ehRepetida é atualizada
            }
        }
    }
    if (ehRepetida == 1) //Se ehRepetida for verdadeira, a letra ou palavra é repetida
    {
        printf("%s repetida", opcao == 1 ? "Palavra" : "Letra");
        // Verifica o sistema operacional
        #ifdef _WIN32 || _WIN64
            Sleep(500); // Sleep 0,5 segundo (500 milisegundos) para um delay e mostrar a mensagem
        #else
            usleep(500 * 1000); // Sleep 0,5 segundo (500 milisegundos)
        #endif
    }

}

int guessByWord(char palavra[20], char palavras[5][20]) //Verifica se a palavra escolhida está na matriz com as palavras e retorna a linha
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if (strcmp(palavra, palavras[i]) == 0) //Verifica se a palavra é igual a alguma palavra da matriz com as palavras
        {
            return i; //Se for, retorna a linha
        }
    }
    return -1; // retorna -1 indicando que a palavra não está na matriz
}

char guessByLetter(char letra, char palavras[5][20]) //Verifica se a letra escolhida está na matriz com as palavras e retorna a letra
{
    int i;
    for (i = 0; i < 5; i++)
    {
        int j;
        for (j = 0; j < 20; j++)
        {
            if (letra == palavras[i][j])
            {
                return letra; //Se a letra estiver na matriz, retorna a letra
            }
        }
    }
    return  '*'; //retorna '*' indicando que a letra não está na matriz
}

int hasLetter(char *letra) //Verifica se a letra é uma letra
{
    char letras[26] = "abcdefghijklmnopqrstuvwxyz"; //Vetor com todas as letras do alfabeto
    int i;
    for (i = 0; i < 26; i++)
    {
        if (letra == letras[i]) //Verifica se a letra é igual a alguma letra do vetor
        {
            return 1; //Se for, retorna 1(verdadeiro)
        }
    }
    return 0; //Se não for, retorna 0(falso)
}
