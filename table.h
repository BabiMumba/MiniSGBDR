#ifndef TABLE_H
#define TABLE_H

#define MAX_TABLES 10
#define MAX_ROWS 100
#define MAX_COLUMNS 10

typedef enum
{
    ENTIER,
    CHAINE,
    DECIMAL,
    BINAIRE,
    DATE
} ColumnType;

typedef struct
{
    char *name;
    ColumnType type;
} ColumnDef;

typedef struct
{
    char *name;
    int columns;
    int rows;
    int primary_key_index;
    ColumnDef column_defs[MAX_COLUMNS];
    char *data[MAX_ROWS][MAX_COLUMNS];
} Table;

extern Table tables[MAX_TABLES];
extern int table_count;

void free_table(Table *table);
void free_all_tables(void);
void creer_table(char *name, int columns, char *column_defs[]);
void inserer_dans_table(char *name, char *values[]);
void mettre_a_jour_table(char *name, char *condition, char *new_values[]);
void supprimer_de_table(char *name, char *condition);
void selectionner_de_table(char *name, char *condition);

#endif // TABLE_H
