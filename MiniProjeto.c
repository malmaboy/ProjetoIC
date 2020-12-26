#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 25
#define EMPTY '_'
#define ARMED '.'
#define DISARMED '*'

void menu();
void choices();
void readFile(char filename[200], char grid[][MAX]);
void show(char empty[][MAX], char armed[][MAX]);

int main()
{
    menu();
    choices();
}

/// Imprime o menu
void menu()
{
    puts("+-----------------------------------------------------");
    puts("read <filename>     - read input file");
    puts("show                - show the mine map");
    puts("trigger <x> <y>     - trigger mine at <x> <y>");
    puts("plant <x> <y>       - place armed mine at <x> <y>");
    puts("export <filename>   - save file with current map");
    puts("quit                - exit program");
    puts("+-----------------------------------------------------");
}

void choices()
{
    int i = 1;
    char choice[20];
    char filename[200];
    char game[MAX][MAX];
    int count = 0;


    do
    {
        printf("\n>");
        // lê a escolha e o path do ficheiro
        ///scanf("%s",choice);
        if (scanf("\n%s", &choice))
        {
            // compares the input with the menu options
            if (strcmp(choice, "read") == 0)
            {
                if (scanf("%s", &filename))
                {
                    readFile(filename, game);
                    /*
                    for (int i = 0; i < MAX; i++)
                    {
                        for (int j = 0; j < MAX; j++)
                        {
                            printf("%c", game[i][j]);
                        }
                    }*/
                    count++;
                }
            }
            else if (strcmp(choice, "show") == 0)
            {
                for (int i = 0; i < MAX; i++){
                    for (int j = 0; j < MAX; j++){
                        if(count <= 0){
                            game[i][j] = EMPTY;
                            
                        }
                        else
                        {
                            game[i][j];

                        }
                        
                    printf("%c", game[i][j]);
                }
        }
            }
            else if (strcmp(choice, "trigger") == 0)
            {
                int posx, posy;
                scanf("%d%d\n", &posx, &posy);
                //Problem here
                if((posx >= 0 && posx <= MAX)  && (posy >= 0 && posy < MAX)){
                    
                    int count1 = 0;

                    for(int i = 0; i < MAX; i++){
                        for (int j = 0; j < MAX; j++)
                        {
                            if((game[i][j] == ARMED) && (game[posx][posy] == game[i][j])){ 
                                game[i][j] = DISARMED;
                            }
                            else if((game[i][j] == EMPTY) && (game[i][j] == game[posx][posy])){
                                count1 == 1;
                            }
                            



                        }
                    }
                    if(count1 == 1){
                        printf("No mine at specified coordinate.\n");
                        count1 == 0;
                    }
                }
                ///PROBLEM HERE
                else
                {
                    /// Problem here se o input for 2
                    printf("Invalid coordinate");
                }
                


            }
            else if (strcmp(choice, "plant") == 0)
            {
                int posx, posy;
                scanf("%d%d\n", &posx, &posy);
                
               for(int i = 0; i < MAX; i++)
               {
                    for (int j = 0; j < MAX; j++)
                    {
                        if((game[i][j] == DISARMED) && (game[i][j] == game[posx][posy])){ 
                            game[i][j] = ARMED;
                        }
                        if((game[i][j] == ARMED) && (game[i][j] == game[posx][posy])){ 
                            game[i][j] = ARMED;
                        }
                        if((game[i][j] == EMPTY) && (game[i][j] == game[posx][posy])){
                           game[i][j] = EMPTY;
                        }
                    }
                }

            }
            else if (strcmp(choice, "export") == 0)
            {
            }
            else if (strcmp(choice, "quit") == 0)
            {
                exit(1);
            }
            else if (strcmp(choice, "sos") == 0)
            {
                menu();
            }
            else
            {
                printf("Inputs errados.\n");
            }
        }

    } while (i != 0);
}

// Lê o ficheiro
void readFile(char filename[200], char grid[][MAX])
{
    int chx;
    int chy;
    int x;
	int i, j;

    //Apontador para o ficheiro
    FILE *file;

    // nome do ficheiro
    // localização do ficheiro

    //Abre o ficheiro
    file = fopen(filename, "r");

    // Verifica se o ficheiro é valido

    if (filename == NULL)
    {
        printf("Impossivel abrir o ficheiro %s", filename);
    }
    else
    {
        for (i = 0; i < MAX; i++)
        {
            for ( j = 0; j < MAX; j++)
            {
                grid[i][j] = EMPTY;
            }
        }

        //Imprime tudo que está no ficheiro
        while (fscanf(file, "%d %d", &chx, &chy) != EOF)
        {

            grid[chx][chy] = ARMED;
        }
        fclose(file);
    }
	
}

