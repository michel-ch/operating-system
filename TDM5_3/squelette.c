
#define SIZE_TAB 42

void reset(){
	printf("reset\n");
/* TODO 
*	shm_unlink();
*	sem_unlink();
*	sem_unlink();
*/
}

int* init_sem_mem(sem_t ** nonVide, sem_t **nonPlein){


	/* TODO
	 * shm_open()
	 * ftruncate()
	 * mmap()
	 * sem_open()
	 * sem_open()
	 */
}

void producteur(){
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
	printf("must be run with either one of these option : -reset or -r, -producer or -d, -consumer or -c\n");
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
