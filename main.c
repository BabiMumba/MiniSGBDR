#include "commandes.h"
#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 256

int main()
{
    atexit(free_all_tables);

    char input[MAX_INPUT_SIZE];
    while (1)
    {
        printf("bievenue dans mini-sgbdr\n");
        printf("Commande> ");
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL)
        {
            break;
        }
        input[strcspn(input, "\n")] = '\0';
        gerer_commande(input);
    }
    return 0;
}
