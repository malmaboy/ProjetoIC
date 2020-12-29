#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// tamanho do array
#define MAX 25
// sem mina
#define EMPTY '_'
// mina armada
#define ARMED '.'
// mina desarmada
#define DISARMED '*'

void menu();
void choices();
void readFile(char filename[200], char grid[][MAX]);
void show(char empty[][MAX], char armed[][MAX]);
void writeFile(char filenameout[200], char grid[][MAX]);

// Main
int main()
{
    char map[MAX][MAX];
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            map[i][j] = EMPTY;
        }
    }
    menu();
    choices(map);
}

/// Imprime o menu
void menu()
{
    puts("+-----------------------------------------------------");
    puts("read <filename> - read input file");
    puts("show - show the mine map");
    puts("trigger <x> <y> - trigger mine at <x> <y>");
    puts("plant <x> <y> - place armed mine at <x> <y>");
    puts("export <filename> - save file with current map");
    puts("quit                - exit program");
    puts("sos - show menu");
    puts("+-----------------------------------------------------");
}

// Verifica a escolha do utilizador
void choices(char game[][MAX])
{
    int i = 1;
    // nome da escolha
    char choice[20];
    // nome do ficheiro
    char filename[200];
    // nome do ficheiro para fazer export
    char filenameout[200];
    // variavel de ajuda para opção show
    int count = 0;

    do
    {
        printf(">");
        // verifica a escolha do menu
        if (scanf("\n%s", choice))
        {
            // lê a escolha e o path do ficheiro
            if (strcmp(choice, "read") == 0)
            {
                if (scanf("%s", filename))
                {
                    readFile(filename, game);
                    count = 1;
                }
            }
            // Imprime o mapa
            else if (strcmp(choice, "show") == 0)
            {
                for (int i = 0; i < MAX; i++)
                {

                    for (int j = 0; j < MAX; j++)
                    {
                        if (game[i][j] == EMPTY)
                            printf("_");
                        else if ((game[i][j]) == (ARMED))
                            printf(".");
                        else if ((game[i][j]) == (DISARMED))
                            printf("*");
                    }
                    if (count > 0)
                        printf("\n");
                }
            }
            // Recebe coordenas x e y e põe as minas em estado "off"
            else if (strcmp(choice, "trigger") == 0)
            {
                int posx, posy;
                int count1 = 0;
                scanf("%d%d", &posx, &posy);
                if ((posx >= 0 && posx <= MAX) && (posy >= 0 && posy < MAX))
                {

                    for (int i = 0; i < MAX; i++)
                    {
                        for (int j = 0; j < MAX; j++)
                        {
                            if ((game[i][j] == ARMED) && (game[i][j] == game[posx][posy]))
                            {
                                game[posx][posy] = DISARMED;
                            }
                            else if ((game[i][j] == EMPTY) && (game[i][j] == game[posx][posy]))
                            {
                                count1 = 1;
                            }
                        }
                    }
                    if (count1 == 1)
                    {
                        fputs("No mine at specified coordinate", stdout);
                        count1 = 0;
                    }
                }
                else
                {
                    fputs("Invalid coordinate", stdout);
                }
            }
            // recebe coordenadas x e y e põe uma mina em estado "armed"
            else if (strcmp(choice, "plant") == 0)
            {
                int posx, posy;
                scanf("%d%d", &posx, &posy);

                if ((posx >= 0 && posx < MAX) && (posy >= 0 && posy < MAX))
                {
                    count++;
                    for (int i = 0; i < MAX; i++)
                    {
                        for (int j = 0; j < MAX; j++)
                        {
                            if ((game[i][j] == DISARMED) && (game[i][j] == game[posx][posy]))
                            {
                                game[posx][posy] = ARMED;
                            }
                            if ((game[i][j] == ARMED) && (game[i][j] == game[posx][posy]))
                            {
                                game[posx][posy] = ARMED;
                            }
                            if ((game[i][j] == EMPTY) && (game[i][j] == game[posx][posy]))
                            {
                                game[posx][posy] = ARMED;
                            }
                        }
                    }
                }
                else
                {
                    fputs("Invalid coordinate", stdout);
                }
            }

            // Exporta as posições das bombas para outro ficheiro
            else if (strcmp(choice, "export") == 0)
            {
                if (scanf("%s", filenameout))
                {
                    writeFile(filenameout, game);
                }
            }
            // Fecha a aplicação
            else if (strcmp(choice, "quit") == 0)
            {
                exit(1);
            }
            // Imprime o menu
            else if (strcmp(choice, "sos") == 0)
            {
                menu();
            }
            else
            {
                fputs("Invalid input", stdout);
            }
        }

    } while (i != 0);
}

// Lê o ficheiro
void readFile(char filename[200], char grid[][MAX])
{
    char ch;
    // Variavel que recebe a posição x
    int chx;
    // Variavel que recebe a posição y
    int chy;
    int hasx;
    int hasy;
    // Variaveis que vão receber as posições do array
    int turn;
    int i, j;
    //int k[200];

    //Apontador para o ficheiro
    FILE *file;

    //Abre o ficheiro
    file = fopen(filename, "r");

    // Verifica se o ficheiro é valido
    if (file == NULL)
    {
        fputs("Error opening file\n", stdout);
        choices(grid);
    }
    else
    {
        // Se o ficheiro for valido lê as posições que estão ficheiro
        // e aplica no array
        for (i = 0; i < MAX; i++)
        {
            for (j = 0; j < MAX; j++)
            {
                grid[i][j] = EMPTY;
            }
        }

        turn = 0;
        chx = 0;
        chy = 0;
        hasx = 0;
        hasy = 0;

        // recebe as posições das minas e imprime-as
        while (1)
        {
            if (fscanf(file, "%c", &ch) != EOF)
            {

                if (turn == 0)
                {
                    if (ch == '\n')
                    {
                        if (hasx)
                        {
                            fputs("File is corrupted\n", stdout);
                        }
                        turn = 0;
                        chx = 0;
                        chy = 0;
                        hasx = 0;
                        hasy = 0;
                    }

                    else if (ch == ' ')
                    {
                        if (hasx)
                        {
                            turn = 1;
                        }
                    }

                    else
                    {
                        if (chx == 0)
                        {
                            chx = ch - 48;
                            hasx = 1;
                        }

                        else
                        {
                            chx *= 10;
                            chx += ch - 48;
                            hasx = 1;
                        }
                    }
                }

                else if (turn == 1)
                {
                    if (((ch == '\n') && (hasy)) || (ch == ' '))
                    {
                        grid[chx][chy] = ARMED;

                        turn = 0;
                        chx = 0;
                        chy = 0;
                        hasx = 0;
                        hasy = 0;
                    }
                    else if (ch == '\n')
                    {
                        fputs("File is corrupted\n", stdout);

                        turn = 0;
                        chx = 0;
                        chy = 0;
                        hasx = 0;
                        hasy = 0;
                    }
                    else
                    {
                        if (chy == 0)
                        {
                            chy = ch - 48;
                            hasy = 1;
                        }
                        else
                        {
                            chy *= 10;
                            chy += ch - 48;
                            hasy = 1;
                        }
                    }
                }
            }
            else
            {
                if (turn == 0)
                {
                    if (hasx)
                    {
                        fputs("File is corrupted\n", stdout);
                    }
                }
                else if ((turn == 1) && (hasy))
                {
                    grid[chx][chy] = ARMED;
                }
                else
                {
                    fputs("File is corrupted\n", stdout);
                }
                break;
            }
        }
    }
    fclose(file);
    // Fecha o ficheiro
}

// cria um ficheiro novo
void writeFile(char filenameout[200], char grid[][MAX])
{

    // Apontador para o ficheiro
    FILE *file;
    // variaveis da grelha
    int i, j;

    //abre o ficheiro em modo escrita
    file = fopen(filenameout, "w");
    // Verifica se o ficheiro é null
    if (file == NULL)
    {
        fputs("Error opening the file\n", stdout);
    }
    // Abre a grelha
    // Verifica se há bombas armadas no array
    // E verifica se há bombas desarmadas no array
    else
    {
        for (i = 0; i < MAX; i++)
        {
            for (j = 0; j < MAX; j++)
            {
                // Bombas armadas no array(posições)
                if (grid[i][j] == ARMED)
                {
                    // Escreve no ficheiro as posições das bombas armadas
                    fprintf(file, "%d %d\n", i, j);
                }
                // Bombas desarmadas no array(posições)
                if (grid[i][j] == DISARMED)
                {
                    // Escreve no ficheiro as posições das bombas desarmadas
                    fprintf(file, "%d %d\n", i, j);
                }
            }
        }
        // Fecha o ficheiro
        fclose(file);
    }
}
