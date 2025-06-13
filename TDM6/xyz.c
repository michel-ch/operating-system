#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    int fd;
    const char debut[] = "XYZ";
    const char fin[] = "xyz";
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nom_fichier>\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    /* Écriture au début */
    if (write(fd, debut, sizeof(debut)-1) == -1) {
        perror("write début");
        close(fd);
        return 1;
    }

    /* Déplacement à la position 100000 */
    if (lseek(fd, 100000, SEEK_SET) == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    /* Écriture à la fin */
    if (write(fd, fin, sizeof(fin)-1) == -1) {
        perror("write fin");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}