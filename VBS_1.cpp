#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"
#include "screenfunctions.h"

char filename[20];
int artikelNummer;
int update;

// Bij het starten van het programma moet de filename worden meegegeven

int main(int argc, char *argv[]){



    if (argc == 2) {
    strcpy(filename, argv[1]);
    
    }
    else {
        printf("Geef de naam van het bestand: \n");
        scanf("%s",filename);
    }
    
    
    fflush(stdin);

    makeMenu(filename, artikelNummer, update);
        
    return 0;
}