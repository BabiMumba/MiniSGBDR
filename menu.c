//
// Created by Babi Mumba on 23/07/2024.
//

#include "menu.h"

#include <stdio.h>
#include <stdlib.h>


void print_menu() {
    printf("1. Create Table\n");
    printf("2. Drop Table\n");
    printf("3. Insert\n");
    printf("4. Select\n");
    printf("5. Delete\n");
    printf("6. Update\n");
    printf("7. Exit\n");

}

void menu() {
    int choice;
    do {
        print_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                menu_table();
                break;
            case 2:
                menu_table();
                break;
            case 3:
                menu_query_processor();
                break;
            case 4:
                menu_query_processor();
                break;
            case 5:
                menu_query_processor();
                break;
            case 6:
                menu_query_processor();
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    } while (1);
}
