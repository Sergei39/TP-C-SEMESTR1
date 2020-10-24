#include "matrix_memory.h"

void clear_mem( int** arr, const int *row ) {
    int i = 0;
    while( i < *row && arr[i] != NULL ) {
        free( arr[i] );
        i++;
    }

    free( arr );
}

int** get_mem( const int *row, const int *col ) {
    int** arr = ( int** )malloc( *row * sizeof( int* ) );
    if( arr == NULL ) {
        fprintf( stderr, "Failed not memory arr**\n" );
        return NULL;
    }

    for( int i = 0; i < *row; i++ ) {
        arr[i] = ( int* )malloc( *col * sizeof( int ) );
        if( arr[i] == NULL ) {
            clear_mem(arr, row);
            fprintf( stderr, "Failed not memory\n" );
            return NULL;
        }
    }

    return arr;
}