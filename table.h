//
// Created by Babi Mumba on 09/07/2024.
//

#ifndef TABLE_H
#define TABLE_H

void create_table(char *table_name, char *columns);//pour creer une table
void drop_table(char *table_name);//pour supprimer une table
void show_tables();//pour afficher les tables
void show_table(char *table_name);//pour afficher une table
void insert_into_table(char *table_name, char *values);//pour inserer dans une table
void delete_from_table(char *table_name, char *condition);//pour supprimer dans une table
void update_table(char *table_name, char *column, char *value, char *condition);//pour mettre a jour une table

#endif //TABLE_H
