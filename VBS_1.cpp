#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"
#include "screenfunctions.h"

char orderFile[20];
char klantFile[20];
char artikelFile[20];


// Bij het starten van het programma moet de filename worden meegegeven
//probleem oplossen, we hebben 3 bestanden nodig; order,artikel en klantbestand
//deze leggen we nu eerst vast 

int main(){

char klantFile[20] = "klantfile.txt";
char artikelFile[20] = "artikelfile.txt";
char orderFile[20] = "orderfile";

//start het hoofdmenu
    startMenu(klantFile, artikelFile);
        
    return 0;
}