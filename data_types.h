//
// Created by Babi Mumba on 09/07/2024.
//

#ifndef DATA_TYPES_H
#define DATA_TYPES_H
// Data types
typedef enum {
    INT,
    FLOAT,
    STRING
} data_type;

typedef struct {
    data_type type;
    int length;
} column;

//table
typedef struct {
    char *name;
    column *columns;
    int num_columns;
} Table;

#endif //DATA_TYPES_H
