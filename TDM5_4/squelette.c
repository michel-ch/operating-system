#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <time.h>
#include <getopt.h>
#include <sys/types.h>

#define MAX_FILE 42 /* nombre maximal d'éléments dans la mémoire partagée */
#define MAX_RAND 100 /* valeur maximale des tirages aléatoire */

void reset(){
	printf("reset\n");
	shm_unlink("/shared_memory");
	shm_unlink("/sem_non_plein");
	shm_unlink("/sem_non_vide");
	/* TODO 
	*	shm_unlink();
	*	sem_unlink();
	*	sem_unlink();
	*/
}

int* init_sem_mem(sem_t ** non_plein, sem_t **non_vide){
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
	*non_plein = sem_open("/sem_non_plein", O_CREAT , 0666, MAX_FILE);
    if (non_plein == SEM_FAILED) {
        perror("sem_open non_plein failed");
        sem_unlink("/sem_non_plein");
        exit(1);
    }
    *non_vide = sem_open("/sem_non_vide", O_CREAT , 0666, 0);
    if (non_vide == SEM_FAILED) {
        perror("sem_open non_vide failed");
        sem_unlink("/sem_non_vide");
        exit(1);
    }
	return shared_data;
	/* TODO
	 * shm_open()
	 * ftruncate()
	 * mmap()
	 * sem_open()
	 * sem_open()
	 */
}

void producteur(){
	int *tab;
	sem_t *non_plein, *non_vide;
    int index = 0;
	int valeur;
    tab = init_sem_mem(&non_plein, &non_vide);
	srandom(time(NULL));
    while(1){
        sem_wait(non_plein);
        valeur = (int) ((random()/(double) RAND_MAX)*MAX_RAND)+1;
        tab[index] = valeur;
        index = (index + 1 ) % MAX_FILE;
        sem_post(non_vide);
    }
	munmap(tab, MAX_FILE * sizeof(int));
	/* TODO
	 * int * tab;
	 * sem_t * nonVide;
	 * sem_t * nonPlein;
	 * init_sem_mem(); => initialise tab, nonVide et nonPlein
	 * boucle production
	 * munmap()
	 */
}

void consommateur(){
	int *tab;
	sem_t *non_plein, *non_vide;
    int index = 0;
	int valeur;
	tab = init_sem_mem(&non_plein, &non_vide);
    while(1){
        sem_wait(non_vide);
        valeur = tab[index];
        printf("Consommation: %d à l'index %d\n", valeur, index);
        index = (index + 1) % MAX_FILE;
        sem_post(non_plein);
    };
	munmap(tab, MAX_FILE * sizeof(int));
	/* TODO
	 * int * tab;
	 * sem_t * nonVide;
	 * sem_t * nonPlein;
	 * init_sem_mem(); => initialise tab, nonVide et nonPlein
	 * boucle consommation
	 * munmap()
	 */
}

void usage()
{
	printf("must be run with either one of these option : -reset or -r, -producer or -p, -consumer or -c\n");

}

int main(int argc , char * argv[]){
	static struct option long_options[] =
	{
		{"reset",     no_argument, 0, 'r'},
		{"producer",  no_argument, 0, 'p'},
		{"consumer",  no_argument, 0, 'c'},
		{0, 0, 0, 0}
	};
	/* getopt_long stores the option index here. */
	int option_index = 0;
	int c = getopt_long (argc, argv, "rpc",
			long_options, &option_index);

	/* Detect the end of the options. */
	if (c == -1)
		usage();
	else
		switch (c)
		{

			case 'r':
				reset();
				break;

			case 'p':
				producteur();
				break;

			case 'c':
				consommateur();
				break;

			default: break;
		}
	if (optind < argc)
	{
		usage();
		while (optind < argc)
			printf ("%s ", argv[optind++]);
		putchar ('\n');
	}

	return 0;
}
