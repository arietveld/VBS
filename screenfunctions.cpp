#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "screenfunctions.h"

//Functie voor het startmenu
void makeMenu(char filename[20], int artikelNummer, int update) {

    int choice;

    do {
        clearScreen();

        printf("Voorraad Beheer Systeem rel. 0.1\n\n" );
        printf("Menu:\n");
        printf("1. Zoek Product\n");
        printf("2. Nieuw Product\n");
        printf("3. Print voorraadlijst\n");
        printf("4. Muteer voorraad\n");
        printf("5. Bewerk de database in Notepad\n");
        printf("0. Exit\n");
        printf("Keuze: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Zoek artikel op artikelnummer
                searchProduct(filename, artikelNummer);

                break;

            case 2:
                 // Voeg een product artikel toe
                makeProduct(filename);
                
                break;

            case 3:
                //print database
                printDbase(filename);

                break;
            
            case 4:
                //muteer voorraad
                stockUpdate(filename, artikelNummer, update);
                
                break;

            case 5:
                //bewerk het logboek met notepad
                editDBase(filename);
                                
                break;

            case 0:
                printf("Programma wordt afgesloten.\n");

                return;

            default:
                printf("Ongeldige keuze. Probeer opnieuw.\n");
        }

        printf("\nDruk op Enter om door te gaan...");
        getchar(); // Wacht op Enter-toets
        getchar(); // Verbruik het newline-karakter in de buffer

    } while (choice != 0);
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void clearHigh() {
 int numberLines = 15;
 for (int i = 0; i < numberLines; i++)
 {
    printf("\e[K");
    if ( i < numberLines - 1)
    {
    printf("\e[B");
}
 }
printf("\e[H");
}
