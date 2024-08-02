#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Table tables[MAX_TABLES];
int table_count = 0;

// Fonction pour calculer la largeur maximale de chaque colonne
void calculer_largeur_colonnes(Table *table, int *largeur_colonnes)
{
    for (int c = 0; c < table->columns; c++)
    {
        largeur_colonnes[c] = strlen(table->column_defs[c].name);
        for (int r = 0; r < table->rows; r++)
        {
            int len = strlen(table->data[r][c]);
            if (len > largeur_colonnes[c])
            {
                largeur_colonnes[c] = len;
            }
        }
    }
}

// Fonction pour afficher un séparateur de ligne de tableau
void afficher_separateur(int *largeur_colonnes, int colonne_count)
{
    for (int i = 0; i < colonne_count; i++)
    {
        printf("+");
        for (int j = 0; j < largeur_colonnes[i] + 2; j++)
        {
            printf("-");
        }
    }
    printf("+\n");
}

// Fonction pour afficher une ligne du tableau
void afficher_ligne(char **ligne, int *largeur_colonnes, int colonne_count)
{
    for (int i = 0; i < colonne_count; i++)
    {
        printf("| %-*s ", largeur_colonnes[i], ligne[i]);
    }
    printf("|\n");
}

void free_table(Table *table)
{
    if (table == NULL)
        return;
    free(table->name);
    for (int i = 0; i < table->columns; i++)
    {
        free(table->column_defs[i].name);
    }
    for (int i = 0; i < table->rows; i++)
    {
        for (int j = 0; j < table->columns; j++)
        {
            free(table->data[i][j]);
        }
    }
}

void free_all_tables(void)
{
    for (int i = 0; i < table_count; i++)
    {
        free_table(&tables[i]);
    }
}

void creer_table(char *name, int columns, char *column_defs[])
{
    if (table_count >= MAX_TABLES)
    {
        printf("Erreur : Nombre maximum de tables atteint.\n");
        return;
    }

    if (columns < 1)
    {
        printf("Erreur : Vous devez spécifier au moins une colonne.\n");
        return;
    }

    Table *table = &tables[table_count];
    table->name = strdup(name);
    table->columns = columns;
    table->rows = 0;
    table->primary_key_index = -1;

    for (int i = 0; i < columns; i++)
    {
        char *col_def = strdup(column_defs[i]);
        char *col_name = strtok(col_def, ":");
        char *col_type = strtok(NULL, ":");
        table->column_defs[i].name = strdup(col_name);

        if (strcmp(col_type, "ENTIER") == 0)
        {
            table->column_defs[i].type = ENTIER;
        }
        else if (strcmp(col_type, "CHAINE") == 0)
        {
            table->column_defs[i].type = CHAINE;
        }
        else if (strcmp(col_type, "DECIMAL") == 0)
        {
            table->column_defs[i].type = DECIMAL;
        }
        else if (strcmp(col_type, "BINAIRE") == 0)
        {
            table->column_defs[i].type = BINAIRE;
        }
        else if (strcmp(col_type, "DATE") == 0)
        {
            table->column_defs[i].type = DATE;
        }
        else
        {
            printf("Erreur : Type de colonne '%s' non valide.\n", col_type);
            free(col_def);
            return;
        }

        if (strstr(column_defs[i], "PRIMARY") != NULL)
        {
            table->primary_key_index = i;
        }
        free(col_def);
    }

    table_count++;
    printf("Table '%s' créée avec %d colonnes.\n", name, columns);
}

void inserer_dans_table(char *name, char *values[])
{
    Table *table = NULL;
    for (int i = 0; i < table_count; i++)
    {
        if (strcmp(tables[i].name, name) == 0)
        {
            table = &tables[i];
            break;
        }
    }

    if (table == NULL)
    {
        printf("Erreur : Table '%s' non trouvée.\n", name);
        return;
    }

    if (table->rows >= MAX_ROWS)
    {
        printf("Erreur : Nombre maximum de lignes atteint pour la table '%s'.\n", name);
        return;
    }

    if (table->primary_key_index != -1)
    {
        for (int r = 0; r < table->rows; r++)
        {
            if (strcmp(table->data[r][table->primary_key_index], values[table->primary_key_index]) == 0)
            {
                printf("Erreur : Valeur de clé primaire en double.\n");
                return;
            }
        }
    }

    for (int j = 0; j < table->columns; j++)
    {
        table->data[table->rows][j] = strdup(values[j]);
    }
    table->rows++;
    printf("Ligne insérée dans la table '%s'.\n", name);
}

void mettre_a_jour_table(char *name, char *condition, char *new_values[])
{
    Table *table = NULL;
    for (int i = 0; i < table_count; i++)
    {
        if (strcmp(tables[i].name, name) == 0)
        {
            table = &tables[i];
            break;
        }
    }

    if (table == NULL)
    {
        printf("Erreur : Table '%s' non trouvée.\n", name);
        return;
    }

    char *col_name = strtok(condition, "=");
    char *col_value = strtok(NULL, "=");
    int col_index = -1;

    for (int j = 0; j < table->columns; j++)
    {
        if (strcmp(table->column_defs[j].name, col_name) == 0)
        {
            col_index = j;
            break;
        }
    }

    if (col_index == -1)
    {
        printf("Erreur : Colonne '%s' non trouvee.\n", col_name);
        return;
    }

    for (int r = 0; r < table->rows; r++)
    {
        if (strcmp(table->data[r][col_index], col_value) == 0)
        {
            for (int c = 0; c < table->columns; c++)
            {
                free(table->data[r][c]);
                table->data[r][c] = strdup(new_values[c]);
            }
        }
    }
    printf("Table '%s' mise a jour.\n", name);
}

void supprimer_de_table(char *name, char *condition)
{
    Table *table = NULL;
    for (int i = 0; i < table_count; i++)
    {
        if (strcmp(tables[i].name, name) == 0)
        {
            table = &tables[i];
            break;
        }
    }

    if (table == NULL)
    {
        printf("Erreur : Table '%s' non trouvée.\n", name);
        return;
    }

    char *col_name = strtok(condition, "=");
    char *col_value = strtok(NULL, "=");
    int col_index = -1;

    for (int j = 0; j < table->columns; j++)
    {
        if (strcmp(table->column_defs[j].name, col_name) == 0)
        {
            col_index = j;
            break;
        }
    }

    if (col_index == -1)
    {
        printf("Erreur : Colonne '%s' non trouvée.\n", col_name);
        return;
    }

    int new_row_count = 0;
    for (int r = 0; r < table->rows; r++)
    {
        if (strcmp(table->data[r][col_index], col_value) != 0)
        {
            for (int c = 0; c < table->columns; c++)
            {
                table->data[new_row_count][c] = table->data[r][c];
            }
            new_row_count++;
        }
        else
        {
            for (int c = 0; c < table->columns; c++)
            {
                free(table->data[r][c]);
            }
        }
    }
    table->rows = new_row_count;
    printf("Lignes supprimées de la table '%s'.\n", name);
}

void selectionner_de_table(char *name, char *condition)
{
    Table *table = NULL;
    for (int i = 0; i < table_count; i++)
    {
        if (strcmp(tables[i].name, name) == 0)
        {
            table = &tables[i];
            break;
        }
    }

    if (table == NULL)
    {
        printf("Erreur : Table '%s' non trouvée.\n", name);
        return;
    }

    int col_index = -1;
    char *col_value = NULL;

    if (condition != NULL && strcmp(condition, "*") != 0)
    {
        char *col_name = strtok(condition, "=");
        col_value = strtok(NULL, "=");

        for (int j = 0; j < table->columns; j++)
        {
            if (strcmp(table->column_defs[j].name, col_name) == 0)
            {
                col_index = j;
                break;
            }
        }

        if (col_index == -1)
        {
            printf("Erreur : Colonne '%s' non trouvée.\n", col_name);
            return;
        }
    }

    int largeur_colonnes[MAX_COLUMNS];
    calculer_largeur_colonnes(table, largeur_colonnes);

    afficher_separateur(largeur_colonnes, table->columns);

    // Afficher les noms des colonnes
    char *col_names[MAX_COLUMNS];
    for (int c = 0; c < table->columns; c++)
    {
        col_names[c] = table->column_defs[c].name;
    }
    afficher_ligne(col_names, largeur_colonnes, table->columns);

    afficher_separateur(largeur_colonnes, table->columns);

    // Afficher les données des lignes
    for (int r = 0; r < table->rows; r++)
    {
        if (col_value == NULL || strcmp(table->data[r][col_index], col_value) == 0)
        {
            afficher_ligne(table->data[r], largeur_colonnes, table->columns);
        }
    }

    afficher_separateur(largeur_colonnes, table->columns);
}
