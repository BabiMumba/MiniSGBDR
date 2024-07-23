//
// Created by Babi Mumba on 09/07/2024.
//

#include "storage_manager.h"

#include <stdlib.h>
#include <string.h>

void init_storage_manager() {
    // Initialize the storage manager
    storage_manager = create_storage_manager_instance();
    //storage_manager sera cree dans le main pour eviter les erreurs de segmentation
}

void add_table(Table *table) {
    // Add a table to the storage manager
    storage_manager->tables[storage_manager->num_tables] = table;
    storage_manager->num_tables++;
}

void drop_table(char *table_name) {
    // Drop a table from the storage manager
    int i;
    for (i = 0; i < storage_manager->num_tables; i++) {
        if (strcmp(storage_manager->tables[i]->name, table_name) == 0) {
            free(storage_manager->tables[i]);
            storage_manager->tables[i] = storage_manager->tables[storage_manager->num_tables - 1];
            storage_manager->num_tables--;
            break;
        }
    }
}
