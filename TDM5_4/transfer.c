#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <time.h>

#define MAX_FILE 10 /* nombre maximal d'éléments dans la mémoire partagée */
#define MAX_RAND 100 /* valeur maximale des tirages aléatoire */

void init_sem(sem_t **non_plein, sem_t **non_vide){
    non_plein = sem_open("/sem_non_plein", O_CREAT , 0666, MAX_FILE);
    if (non_plein == -1) {
        perror("sem_open non_plein failed");
        sem_unlink("/sem_non_plein");
        exit(1);
    }
    *non_vide = sem_open("/sem_non_vide", O_CREAT , 0666, 0);
    if (non_vide == -1) {
        perror("sem_open non_vide failed");
        sem_unlink("/sem_non_vide");
        exit(1);
    }
}
void reset(){
    if(sem_unlink(non_plein) == SEM_FAILED){
        perror("sem_unlink non_plein failed");
    }
    if(sem_unlink(non_vide) == SEM_FAILED){
        perror("sem_unlink non_vide failed");
    }
}

void producteur(int *shared_data){
    sem_t *non_plein, *non_vide;
    int index = 0;

    init_sem(&non_plein, &non_vide);
    while(1){
        sem_wait(non_plein);
        int valeur = (int) ((random()/(double) RAND_MAX)*MAX_RAND)+1;
        shared_data[index] = valeur;
        index = (index + 1 ) % MAX_FILE;
        sem_post(non_vide);
    };
}

void consommateur(int *shared_data){
    sem_t *non_plein, *non_vide;
    int index = 0;
    while(1){
        sem_wait(non_vide);
        int valeur = shared_data[index];
        printf("Consommation: %d à l'index %d\n", valeur, index);
        index = (index + 1) % MAX_FILE;
        sem_post(non_plein);
    };
}

int main(){
    srandom(time(NULL));

    int fd = shm_open("/shared_memory", O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open fd failed");
        exit(1);
    }
    if (ftruncate(fd, MAX_FILE*sizeof(int)) == -1){
        perror("ftruncate fd failed");
        shm_unlink("/shared_memory");
        exit(1);
    }
    
    int *shared_data = mmap(NULL, MAX_FILE*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shared_data == MAP_FAILED){
        perror("mmap failed");
        shm_unlink("/shared_memory");
        exit(1);
    }

    munmap(shared_data, MAX_FILE * sizeof(int));
    close(fd);
    shm_unlink("/shared_memory");

    return 0;
}
