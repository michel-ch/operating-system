#define _DEFAULT_SOURCE
#define MY_OFFSETOF(type, member) ((size_t)&((type*)0)->member)
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define HEADER_SIZE sizeof(size_t)
#define MAX_DATA 1024

typedef struct {
    size_t size;
    char data[1];
} block_t;

void* mon_malloc(size_t size) {
    block_t* block;
    size_t total_size;
    size_t page_size;
    size_t aligned_size;

    if (size == 0) return NULL;
    
    total_size = size + sizeof(block_t);
    page_size = sysconf(_SC_PAGESIZE);
    aligned_size = (total_size + page_size - 1) & ~(page_size - 1);
    
    block = mmap(NULL, 
                aligned_size, 
                PROT_READ | PROT_WRITE,
                MAP_PRIVATE | MAP_ANON,
                -1, 
                0);
    
    if (block == MAP_FAILED) {
        perror("mmap failed");
        return NULL;
    }
    
    block->size = aligned_size;
    
    return block->data;
}

void mon_free(void* ptr) {
    block_t* block;
    if (ptr == NULL) return;
    
    block = (block_t*)((char*)ptr - MY_OFFSETOF(block_t, data));
    
    if (munmap(block, block->size) == -1) {
        perror("munmap failed");
    }
}

int main(void) {
    int* numbers;
    int i;
    char* str;
    void* ptr;
    void* big;

    /* Test 1: Allouer et libérer un tableau d'entiers */
    printf("Test 1: Tableau d'entiers\n");
    numbers = (int*)mon_malloc(5 * sizeof(int));
    if (numbers) {
        for (i = 0; i < 5; i++) {
            numbers[i] = i + 1;
            printf("numbers[%d] = %d\n", i, numbers[i]);
        }
        mon_free(numbers);
    }
    
    /* Test 2: Allouer et libérer une chaîne */
    printf("\nTest 2: Chaîne de caractères\n");
    str = (char*)mon_malloc(20);
    if (str) {
        strcpy(str, "Hello, World!");
        printf("str = %s\n", str);
        mon_free(str);
    }
    
    /* Test 3: Allocation taille 0 */
    printf("\nTest 3: Allocation taille 0\n");
    ptr = mon_malloc(0);
    if (ptr == NULL) {
        printf("Allocation taille 0 correctement gérée\n");
    }
    
    /* Test 4: Grande allocation */
    printf("\nTest 4: Grande allocation\n");
    big = mon_malloc(1024 * 1024);
    if (big) {
        printf("Grande allocation réussie\n");
        mon_free(big);
    }
    
    return 0;
}