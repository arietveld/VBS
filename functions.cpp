#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"


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

void printDbase(char filename[20]) {
    FILE *bestand;
    struct Artikel artikel;

    // Probeer het bestand te openen voor lezen ("r" modus)
    bestand = fopen(filename, "r");

    if (bestand == NULL) {
        printf("Kan het bestand niet openen voor lezen.\n");
        return;
    }

    clearScreen();
    printf("Voorraadlijst:\n");
    printf("Artikelnummer | Omschrijving            | Prijs    | Voorraad\n");
    printf("-------------------------------------------------------------\n");

    // Doorloop het bestand en druk de voorraadlijst af
    while (fscanf(bestand, "%d,%99[^,],%lf,%d\n", &artikel.artikelnummer, artikel.omschrijving, &artikel.prijs, &artikel.voorraad) != EOF) {
        printf("%-13d | %-23s | %8.2lf | %8d\n", artikel.artikelnummer, artikel.omschrijving, artikel.prijs, artikel.voorraad);
    }

    // Sluit het bestand
    fclose(bestand);
}

void stockUpdate(char filename[20], int artikelNummer, int update) {
    FILE *bestand;
    FILE *tijdelijkBestand;
    struct Artikel artikel;
    int gevonden = 0;

    printf("Voer artikelnummer in voor voorraadmutatie: ");
    scanf("%d", &artikelNummer);
    printf("Voer de mutatie in (positief voor verhoging, negatief voor verlaging): ");
    scanf("%d", &update);

    // Probeer het bestand te openen voor lezen ("r" modus)
    bestand = fopen(filename, "r");

    if (bestand == NULL) {
        printf("Kan het bestand niet openen voor lezen.\n");
        return;
    }

    // Maak een tijdelijk bestand om wijzigingen op te slaan
    tijdelijkBestand = fopen("temp.txt", "w");

    if (tijdelijkBestand == NULL) {
        printf("Kan het tijdelijke bestand niet aanmaken voor schrijven.\n");
        fclose(bestand);
        return;
    }

    // Doorloop het bestand en zoek naar het artikelnummer
    while (fscanf(bestand, "%d,%99[^,],%lf,%d\n", &artikel.artikelnummer, artikel.omschrijving, &artikel.prijs, &artikel.voorraad) != EOF) {
        if (artikel.artikelnummer == artikelNummer) {
            artikel.voorraad += update;
            if (artikel.voorraad < 0) {
                artikel.voorraad = 0; // Voorraad kan niet negatief zijn
            }
            gevonden = 1;
        }
        fprintf(tijdelijkBestand, "%d,%s,%.2lf,%d\n", artikel.artikelnummer, artikel.omschrijving, artikel.prijs, artikel.voorraad);
    }

    // Sluit beide bestanden
    fclose(bestand);
    fclose(tijdelijkBestand);

    // Verwijder het oorspronkelijke bestand en hernoem het tijdelijke bestand
    remove(filename);
    rename("temp.txt", filename);

    if (gevonden) {
        printf("Voorraadmutatie uitgevoerd voor artikelnummer %d.\n", artikelNummer);
    } else {
        printf("Artikel met artikelnummer %d niet gevonden.\n", artikelNummer);
    }
}

//functie om een product te zoeken
void searchProduct(char filename[20], int artikelNummer) {
    FILE *bestand;
    struct Artikel artikel;
    int artikelGevonden = 0;

    printf("Voer artikelnummer in om te zoeken: ");
    scanf("%d", &artikelNummer);

    // Probeer het bestand te openen voor lezen ("r" modus)
    bestand = fopen(filename, "r");

    if (bestand == NULL) {
        printf("Kan het bestand niet openen voor lezen.\n");
        return;
    }

    // Doorloop het bestand en zoek naar het artikelnummer
    while (fscanf(bestand, "%d,%99[^,],%lf,%d\n", &artikel.artikelnummer, artikel.omschrijving, &artikel.prijs, &artikel.voorraad) != EOF) {
        if (artikel.artikelnummer == artikelNummer) {
            printf("Artikelnummer: %d\n", artikel.artikelnummer);
            printf("Omschrijving: %s\n", artikel.omschrijving);
            printf("Prijs: %.2lf\n", artikel.prijs);
            printf("Voorraad: %d\n", artikel.voorraad);
            artikelGevonden = 1;
            break; // Artikel gevonden, stop met zoeken
        }
    }

    if (!artikelGevonden) {
        printf("Artikel met artikelnummer %d niet gevonden.\n", artikelNummer);
    }

    // Sluit het bestand
    fclose(bestand);
}

//functie voor het bewerken van de dBase in excel
void editDBase(char filename[20]) {

    char commando[200];
    sprintf(commando, "notepad.exe %s", filename);

    // Open het bestand met Notepad
    system(commando);

    return;
}

void getOmschrijving(char *omschrijving) {
    
    do {
        fflush(stdin);     
           printf("Voer de omschrijving in (maximaal 20 karakters): ");
           scanf("%[^\n]s", omschrijving);
           //printf("%s", omschrijving);
           if (strlen(omschrijving) > 20) {
               clearScreen();
               printf("Waarschuwing: Omschrijving mag maximaal 20 karakters bevatten. Probeer opnieuw.\n");
          
            }
        } while (strlen(omschrijving) > 20);
        
        
        return;
        }



//functie voor het aanmaken van artikelen
int makeProduct(char filename[20]) {
    FILE *bestand;
    struct Artikel artikel;
    int keuze;

    // Probeer het bestand te openen voor schrijven ("w" modus)
    bestand = fopen(filename, "a");

    if (bestand == NULL) {
        printf("Kan het bestand niet openen voor schrijven.\n");
        return 1;
    }



    do {
        clearScreen();
        // Vraag de gebruiker om artikelinformatie in te voeren
        printf("Voer het artikelnummer in: ");
        scanf("%d", &artikel.artikelnummer);

        //printf("Voer de omschrijving in: ");
        //scanf(" %[^\n]s", artikel.omschrijving);

        getOmschrijving(artikel.omschrijving);
        
        fflush(stdin); 

        printf("Voer de prijs in: ");
        scanf("%lf", &artikel.prijs);

        printf("Voer de voorraad in: ");
        scanf("%d", &artikel.voorraad);

        // Schrijf de artikelinformatie naar het bestand
        fprintf(bestand, "%d,%s,%.2lf,%d\n", artikel.artikelnummer, artikel.omschrijving, artikel.prijs, artikel.voorraad);

        printf("Artikel opgeslagen in het bestand.\n");
        //Toon artikel op het scherm
        //Kleur groen
        printf("\e[s");
        printf("\e[32m\e[25;1H\n");
        printf("artnr  omschrijving         prijs    voorraad\n");
        printf("%-6d %-20s %-8.2lf %-6d\n\n", artikel.artikelnummer, artikel.omschrijving, artikel.prijs, artikel.voorraad);
        
        printf("\e[0m\e[1;1H");
        clearHigh();
        // Vraag de gebruiker of ze meer artikelen willen toevoegen
        printf("Wilt u meer artikelen toevoegen? (1: Ja, 0: Nee): ");
        scanf("%d", &keuze);
    } while (keuze != 0);

    // Sluit het bestand
    fclose(bestand);

    printf("Artikelbestand is aangemaakt en gesloten.\n");

    return 0;
}



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
