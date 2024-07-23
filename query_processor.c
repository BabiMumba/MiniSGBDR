//
// Created by Babi Mumba on 09/07/2024.
//

#include "query_processor.h"

#include <stdio.h>

#include "table.h"


void query_processor() {
    int choice;
    do {
        printf("\n\nQuery Processor\n");
        printf("1. Create Table\n");
        printf("2. Drop Table\n");
        printf("3. Show Tables\n");
        printf("4. Show Table\n");
        printf("5. Insert Into Table\n");
        printf("6. Delete From Table\n");
        printf("7. Update Table\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                query_processor_create_table();
                break;
            case 2:
                query_processor_drop_table();
                break;
            case 3:
                query_processor_show_tables();
                break;
            case 4:
                query_processor_show_table();
                break;
            case 5:
                query_processor_insert_into_table();
                break;
            case 6:
                query_processor_delete_from_table();
                break;
            case 7:
                query_processor_update_table();
                break;
            case 8:
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 8);
}

void query_processor_create_table() {
    char table_name[100];
    char columns[100];
    char data_types[100];
    int num_columns;
    printf("Enter table name: ");
    scanf("%s", table_name);
    printf("Enter columns: ");
    scanf("%s", columns);
    printf("Enter data types: ");
    scanf("%s", data_types);
    printf("Enter number of columns: ");
    scanf("%d", &num_columns);
    create_table(table_name, columns, data_types, num_columns);
}
