#include <stdint.h>
#include <stdbool.h>
#include "lib/bitvector.h"
#include "lib/contracts.h"
#include "lib/xalloc.h"
#include "board-ht.h"
#include "lib/queue.h"
#include "lib/boardutil.h"

bitvector press_button(bitvector board, uint8_t row, uint8_t col, uint8_t width, uint8_t height)
{
    board = bitvector_flip(board, get_index(row, col, width, height));
    if (row - 1 >= 0) board = bitvector_flip(board, get_index(row-1, col, width, height));
    if (col - 1 >= 0) board = bitvector_flip(board, get_index(row, col-1, width, height));
    if (row + 1 < height) {
        board = bitvector_flip(board, get_index(row+1,col,width,height));
    } if (col + 1 < width) {
        board = bitvector_flip(board, get_index(row,col+1,width,height));
    }
    return board;
    // if (width * height == 1){
    //     board = bitvector_flip(board, get_index(row, col, width, height));
    //     return board;
    // }
    // else if (row == 0 && col == 0){
    //     board = bitvector_flip(board, get_index(row, col, width, height));
    //     board = bitvector_flip(board, get_index(row, col + 1, width, height));
    //     board = bitvector_flip(board, get_index(row + 1, col, width, height));
    //     return board;
    // }
    // else if (row == 0 && col == width - 1){
    //     board = bitvector_flip(board, get_index(row, col, width, height));
    //     board = bitvector_flip(board, get_index(row, col - 1, width, height));
    //     board = bitvector_flip(board, get_index(row + 1, col, width, height));
    //     return board;
    // }
    // else if (row == height - 1 && col == 0){
    //     board = bitvector_flip(board, get_index(row, col, width, height));
    //     board = bitvector_flip(board, get_index(row, col + 1, width, height));
    //     board = bitvector_flip(board, get_index(row - 1, col, width, height));
    //     return board;
    // }
    // else if (row == height - 1 && col == width - 1){
    //     board = bitvector_flip(board, get_index(row, col, width, height));
    //     board = bitvector_flip(board, get_index(row, col - 1, width, height));
    //     board = bitvector_flip(board, get_index(row - 1, col, width, height));
    //     return board;
    // }
    // else if (row == 0 && col != 0 && col != width - 1){
    //     board = bitvector_flip(board, get_index(row, col, width, height));
    //     board = bitvector_flip(board, get_index(row, col - 1, width, height));
    //     board = bitvector_flip(board, get_index(row, col + 1, width, height));
    //     board = bitvector_flip(board, get_index(row + 1, col, width, height));
    //     return board;
    // }
    // else if (row == height - 1 && col != 0 && col != width - 1){
    //     board = bitvector_flip(board, get_index(row, col, width, height));
    //     board = bitvector_flip(board, get_index(row, col - 1, width, height));
    //     board = bitvector_flip(board, get_index(row, col + 1, width, height));
    //     board = bitvector_flip(board, get_index(row - 1, col, width, height));
    //     return board;
    // }
    // else if (col == 0 && row != 0 && row != height - 1){
    //     board = bitvector_flip(board, get_index(row, col, width, height));
    //     board = bitvector_flip(board, get_index(row - 1, col, width, height));
    //     board = bitvector_flip(board, get_index(row + 1, col, width, height));
    //     board = bitvector_flip(board, get_index(row, col + 1, width, height));
    //     return board;
    // }
    // else if (col == width - 1 && row != 0 && row != height - 1){
    //     board = bitvector_flip(board, get_index(row, col, width, height));
    //     board = bitvector_flip(board, get_index(row - 1, col, width, height));
    //     board = bitvector_flip(board, get_index(row + 1, col, width, height));
    //     board = bitvector_flip(board, get_index(row, col - 1, width, height));
    //     return board;
    // }
    // else{
    //     ASSERT(row != 0);
    //     ASSERT(row != height - 1);
    //     ASSERT(col != 0);
    //     ASSERT(col != width - 1);
    //     board = bitvector_flip(board, get_index(row, col, width, height));
    //     board = bitvector_flip(board, get_index(row - 1, col, width, height));
    //     board = bitvector_flip(board, get_index(row + 1, col, width, height));
    //     board = bitvector_flip(board, get_index(row, col - 1, width, height));
    //     board = bitvector_flip(board, get_index(row, col + 1, width, height));
    //     return board;
    // }
}

void print_steps(struct board_data* B)
{
    queue_t Q = queue_new();
    while (B -> back != NULL){
        enq(Q, (void*)B);
        B = B -> back;
    }
    while(!queue_empty(Q)){
        struct board_data* temp = (struct board_data*)(deq(Q));
        printf("%d:%d\n", temp -> row, temp -> col);
    }
    queue_free(Q, NULL);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: lightsout <board name>\n");
        return EXIT_FAILURE; // see below for what this means
    }
    char *board_filename = argv[1];
    bitvector* test_bv = xcalloc(1, sizeof(bitvector));
    uint8_t* width = xcalloc(1, sizeof(uint8_t));
    uint8_t* height = xcalloc(1, sizeof(uint8_t));
    if (!file_read(board_filename, test_bv, width, height)){
        free(test_bv);
        free(width);
        free(height);
        fprintf(stderr, "Does not exist");
        return EXIT_FAILURE;
    }
    bitvector solved = bitvector_new();
    if (bitvector_equal(*test_bv, solved))
    {
        free(width);
        free(height);
        free(test_bv);
        fprintf(stderr, "Solved\n");
        return EXIT_SUCCESS;
    }
    queue_t Q = queue_new();
    struct board_data* test_board = xcalloc(1, sizeof(struct board_data));
    test_board -> board = *test_bv;
    test_board -> back = NULL;
    enq(Q, (void*)(test_board));
    hdict_t H = ht_new(10000);
    ht_insert(H, (void*)test_board);
    while (!queue_empty(Q)) {
        struct board_data* B = (struct board_data*)deq(Q);
        for (uint8_t row = 0; row < *height; row++) {
            for (uint8_t col = 0; col < *width; col++) {
                bitvector newboard = press_button(B->board, row, col, *width, *height);
                if (bitvector_equal(newboard, solved)) {
                    struct board_data* result = xcalloc(1, sizeof(struct board_data));
                    result -> board = newboard;
                    result -> back = B;
                    result -> row = row;
                    result -> col = col;
                    print_steps(result);
                    ht_insert(H, result);
                    queue_free(Q, NULL);
                    free(test_bv);
                    free(width);
                    free(height);
                    hdict_free(H);
                    printf("solved\n");
                    return EXIT_SUCCESS;
                }
                if (ht_lookup(H, newboard) == NULL) {
                    struct board_data* new = xcalloc(1, sizeof(struct board_data));
                    new -> board = newboard;
                    new -> back = B;
                    new -> row = row;
                    new -> col = col;
                    enq(Q, (void*)new);
                    ht_insert(H, new);
                }
            }
        }
    }
    free(width);
    free(height);
    queue_free(Q, NULL);
    hdict_free(H);
    free(test_bv);
    fprintf(stderr, "Not solvable");
    return EXIT_FAILURE;
}