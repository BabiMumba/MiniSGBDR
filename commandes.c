#include "commandes.h"
#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKENS 100

void gerer_commande(char *input)
{
    char *tokens[MAX_TOKENS];
    int token_count = 0;

    char *token = strtok(input, " ");
    while (token != NULL && token_count < MAX_TOKENS)
    {
        tokens[token_count++] = token;
        token = strtok(NULL, " ");
    }

    if (token_count == 0)
    {
        return;
    }

    if (strcmp(tokens[0], "CREER") == 0 && strcmp(tokens[1], "TABLE") == 0 && token_count > 3)
    {
        creer_table(tokens[2], token_count - 3, &tokens[3]);
    }
    else if (strcmp(tokens[0], "INSERER") == 0 && strcmp(tokens[1], "DANS") == 0 && token_count > 3)
    {
        inserer_dans_table(tokens[2], &tokens[3]);
    }
    else if (strcmp(tokens[0], "METRE_A_JOUR") == 0 && token_count > 5)
    {
        mettre_a_jour_table(tokens[1], tokens[3], &tokens[5]);
    }
    else if (strcmp(tokens[0], "SUPPRIMER") == 0 && strcmp(tokens[1], "DE") == 0 && token_count > 3)
    {
        supprimer_de_table(tokens[2], tokens[3]);
    }
    else if (strcmp(tokens[0], "SELECTIONNER") == 0)
    {
        if (strcmp(tokens[1], "*") == 0 && strcmp(tokens[2], "DE") == 0 && token_count > 3)
        {
            selectionner_de_table(tokens[3], token_count > 4 ? tokens[4] : NULL);
        }
        else
        {
            selectionner_de_table(tokens[1], token_count > 2 ? tokens[2] : NULL);
        }
    }
    else
    {
        printf("Commande non reconnue : %s\n", tokens[0]);
    }
}
