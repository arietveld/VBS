#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "screenfunctions.h"


//Functie voor het startmenu
void startMenu(char klantFile[20], char artikelFile[20]) {

    int choice;

    do {
        clearScreen();

        printf("Voorraad Beheer Systeem rel. 0.1\n\n" );
        printf("Start Menu:\n");
        printf("1. Artikel Menu\n");
        printf("2. Order Menu\n");
        printf("3. Klant Menu \n");

        printf("0. Exit\n");
        printf("Keuze: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Artikel Menu
                artikelMenu(artikelFile);

                break;

            case 2:
                 // Order Menu
                //orderMenu(orderFile);
                
                break;

            case 3:
                //Klant Menu
                klantMenu(klantFile);

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
