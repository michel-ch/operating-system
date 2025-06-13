#define _XOPEN_SOURCE 500
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define TAILLEBUF 8191

int copy1(const char *origin, const char*destination) {
    char buffer[TAILLEBUF];
    int fd_source;
    int fd_destination;
    ssize_t bytes_read;
    ssize_t written;
    int status = 0;
    fd_source = open(origin, O_RDONLY);
    if(fd_source < 0) {
        perror("Error opening source file");
        exit(1);
    }
    fd_destination = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);  /* Utilisez destination */
    if(fd_destination < 0) {
        perror("Error opening destination file");
        if (close(fd_source) == -1) {
            perror("Erreur lors de la fermeture du fichier source (après échec open dest)");
        }
        exit(1);
    }

    while((bytes_read = read(fd_source, buffer, TAILLEBUF)) > 0 ) {
        char *temp = buffer;
        ssize_t byte_to_write = bytes_read;

        while(byte_to_write > 0){
            written = write(fd_destination, temp, byte_to_write);
            if(written < 0){
                perror("Erreur lors de l'écriture dans le fichier destination");
                if (close(fd_source) == -1) {
                     perror("Erreur lors de la fermeture du fichier source (après échec write)");
                }
                if (close(fd_destination) == -1) {
                     perror("Erreur lors de la fermeture du fichier destination (après échec write)");
                }
                return -1;
            }
            byte_to_write -= written;
            temp += written;
        }
    }
    if (bytes_read < 0) {
        perror("Erreur lors de la lecture du fichier source");
        if (close(fd_source) == -1) {
            perror("Erreur lors de la fermeture du fichier source (après échec write)");
        }
        if (close(fd_destination) == -1) {
            perror("Erreur lors de la fermeture du fichier destination (après échec write)");
        }
        return -1;
    }

    if (close(fd_source) == -1) {
        perror("Erreur lors de la fermeture du fichier source (après échec write)");
        status = -1;
    }
    if (close(fd_destination) == -1) {
        perror("Erreur lors de la fermeture du fichier destination (après échec write)");
        status = -1;
    }

    return status;
}

int copy2(const char *origin, const char *destination) {
    FILE *source, *dest;
    char buffer[TAILLEBUF];
    size_t bytes_read;
    
    source = fopen(origin, "rb");
    if (source == NULL) {
        perror("Erreur lors de l'ouverture du fichier source");
        return -1;
    }

    dest = fopen(destination, "wb");
    if (dest == NULL) {
        perror("Erreur lors de l'ouverture du fichier destination");
        fclose(source);
        return -1;
    }

    while ((bytes_read = fread(buffer, 1, TAILLEBUF, source)) > 0) {
        if (fwrite(buffer, 1, bytes_read, dest) != bytes_read) {
            perror("Erreur lors de l'écriture dans le fichier destination");
            fclose(source);
            fclose(dest);
            return -1;
        }
    }

    if (ferror(source)) {
        perror("Erreur lors de la lecture du fichier source");
        fclose(source);
        fclose(dest);
        return -1;
    }

    fclose(source);
    fclose(dest);
    return 0;
}

int copy3(const char *origin, const char *destination) {
    int fd_source, fd_dest;
    struct stat stat_source;
    void *src_addr, *dst_addr;
    
    fd_source = open(origin, O_RDONLY);
    if (fd_source < 0) {
        perror("Erreur lors de l'ouverture du fichier source");
        return -1;
    }

    if (fstat(fd_source, &stat_source) < 0) {
        perror("Erreur lors de la récupération de la taille du fichier");
        close(fd_source);
        return -1;
    }

    if (stat_source.st_size == 0) {
        close(fd_source);
        fd_dest = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_dest < 0) {
            perror("Erreur lors de la création du fichier destination");
            return -1;
        }
        close(fd_dest);
        return 0;
    }

    src_addr = mmap(NULL, stat_source.st_size, PROT_READ, MAP_PRIVATE, fd_source, 0);
    if (src_addr == MAP_FAILED) {
        perror("Erreur lors du mapping du fichier source");
        close(fd_source);
        return -1;
    }

    fd_dest = open(destination, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd_dest < 0) {
        perror("Erreur lors de la création du fichier destination");
        munmap(src_addr, stat_source.st_size);
        close(fd_source);
        return -1;
    }

    if (ftruncate(fd_dest, stat_source.st_size) < 0) {
        perror("Erreur lors de la définition de la taille du fichier");
        munmap(src_addr, stat_source.st_size);
        close(fd_source);
        close(fd_dest);
        return -1;
    }

    dst_addr = mmap(NULL, stat_source.st_size, PROT_WRITE, MAP_SHARED, fd_dest, 0);
    if (dst_addr == MAP_FAILED) {
        perror("Erreur lors du mapping du fichier destination");
        munmap(src_addr, stat_source.st_size);
        close(fd_source);
        close(fd_dest);
        return -1;
    }

    memcpy(dst_addr, src_addr, stat_source.st_size);

    if (munmap(src_addr, stat_source.st_size) < 0) {
        perror("Erreur lors du démapping du fichier source");
    }
    if (munmap(dst_addr, stat_source.st_size) < 0) {
        perror("Erreur lors du démapping du fichier destination");
    }
    
    close(fd_source);
    close(fd_dest);
    return 0;
}

int main(int argc, char *argv[]){
    int method;
    const char *source;
    const char *destination;
    int result;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <méthode> <fichier_source> <fichier_destination>\n", argv[0]);
        fprintf(stderr, "Méthode: 1 (read/write), 2 (fread/fwrite), 3 (mmap)\n");
        return EXIT_FAILURE;
    }
    method = atoi(argv[1]);
    source = argv[2];
    destination = argv[3];

    printf("Copie de '%s' vers '%s' avec la méthode %d...\n", source, destination, method);

    switch(method) {
        case 1:
            result = copy1(source, destination);
            break;
        case 2:
            result = copy2(source, destination);
            break;
        case 3:
            result = copy3(source, destination);
            break;
        default:
            fprintf(stderr, "Méthode invalide\n");
            return EXIT_FAILURE;
    }

    if (result == 0) {
        printf("Copie terminée avec succès.\n");
        return EXIT_SUCCESS;
    } else {
        fprintf(stderr, "La copie a échoué.\n");
        return EXIT_FAILURE;
    }
}