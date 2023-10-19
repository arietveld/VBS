#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "screenfunctions.h"

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

void stockUpdate(char filename[20]) {
    FILE *bestand;
    FILE *tijdelijkBestand;
    struct Artikel artikel;
    int gevonden = 0;

    int update;

    printf("Voer artikelnummer in voor voorraadmutatie: ");
    scanf("%d", &artikel.artikelnummer);
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
        if (artikel.artikelnummer == artikel.artikelnummer) {
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
        printf("Voorraadmutatie uitgevoerd voor artikelnummer %d.\n", artikel.artikelnummer);
    } else {
        printf("Artikel met artikelnummer %d niet gevonden.\n", artikel.artikelnummer);
    }
}

//functie om een product te zoeken
void searchProduct(char filename[20]) {
    FILE *bestand;
    int artikelGevonden = 0;

    int gezochtArtikelNummer;
    printf("Voer artikelnummer in om te zoeken: ");
    scanf("%d", &gezochtArtikelNummer);


    // Probeer het bestand te openen voor lezen ("r" modus)
    bestand = fopen(filename, "r");

    if (bestand == NULL) {
        printf("Kan het bestand niet openen voor lezen.\n");
        return;
    }

    // Doorloop het bestand en zoek naar het artikelnummer
    struct Artikel artikel;
    while (fscanf(bestand, "%d,%99[^,],%lf,%d\n", &artikel.artikelnummer, artikel.omschrijving, &artikel.prijs, &artikel.voorraad) != EOF) {
        if (artikel.artikelnummer == gezochtArtikelNummer) {
            printf("Artikelnummer: %d\n", artikel.artikelnummer);
            printf("Omschrijving: %s\n", artikel.omschrijving);
            printf("Prijs: %.2lf\n", artikel.prijs);
            printf("Voorraad: %d\n", artikel.voorraad);
            artikelGevonden = 1;
            break; // Artikel gevonden, stop met zoeken
        }
    }

    if (!artikelGevonden) {
        printf("Artikel met artikelnummer %d niet gevonden.\n", gezochtArtikelNummer);
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


// Functie om het hoogste klantnummer in het bestand te vinden
int vindHoogsteKlantnummer(char filename[20]) {
    FILE *bestand = fopen(filename, "r");

    if (bestand == NULL) {
        printf("Kan het klantenbestand niet openen.\n");
        return 0;
    }

    int hoogsteKlantnummer = 0;
    char regel[200]; // Grotere buffer voor het lezen van de hele struct

    while (fgets(regel, sizeof(regel), bestand)) {
        struct Klant klant;
        if (sscanf(regel, "%[^,], %[^,], %[^,], %[^,], %d", klant.klantNaam, klant.klantAdres, klant.klantPlaats, klant.klantPostcode, &klant.klantNummer) == 5) {
            if (klant.klantNummer > hoogsteKlantnummer) {
                hoogsteKlantnummer = klant.klantNummer;
            }
        }
    }

    fclose(bestand);
    return hoogsteKlantnummer;
}


// Functie voor het aanmaken van een nieuwe Klant
int makeKlant(char filename[20]) {
    FILE *bestand;
    struct Klant klant;
    int keuze;
    

    // Probeer het bestand te openen voor schrijven ("w" modus)
    bestand = fopen(filename, "a");

    if (bestand == NULL) {
        printf("Kan het bestand niet openen voor schrijven.\n");
        return 1;
    }


    do {
        clearScreen();
        // Vraag de gebruiker om klantinformatie in te voeren
        printf("Voer de klantnaam in: ");
        scanf(" %[^\n]s", klant.klantNaam);

        printf("Voer klantadres in (straat): ");
        scanf(" %[^\n]s", &klant.klantAdres);

        printf("Voer de Postcode in: ");
        scanf("%s", &klant.klantPostcode);

        printf("Voer de Plaatsnaam in ");
        scanf("%s", &klant.klantPlaats);

        //Klant krijgt volgend klantnummer 
        //tijdelijk voor de test even een vast nummer


klant.klantNummer = vindHoogsteKlantnummer(filename) + 1;


        // Schrijf de artikelinformatie naar het bestand
        fprintf(bestand, "%s,%s,%s,%s,%d\n", klant.klantNaam, klant.klantAdres, klant.klantPostcode, klant.klantPlaats, klant.klantNummer);

        printf("Artikel opgeslagen in het bestand.\n");
        //Toon artikel op het scherm
        //Kleur groen
        /*printf("\e[s");
        printf("\e[32m\e[25;1H\n");
        printf("artnr  omschrijving         prijs    voorraad\n");
        printf("%-6d %-20s %-8.2lf %-6d\n\n", artikel.artikelnummer, artikel.omschrijving, artikel.prijs, artikel.voorraad);
        
        printf("\e[0m\e[1;1H");
        */
        clearScreen();
        // Vraag de gebruiker of ze meer artikelen willen toevoegen
        printf("Wilt u meer klanten toevoegen? (1: Ja, 0: Nee): ");
        scanf("%d", &keuze);
    } while (keuze != 0);

    // Sluit het bestand
    fclose(bestand);

    printf("Klantenbestand is aangemaakt en gesloten.\n");

    return 0;
}

/*
//functie om een product te zoeken
void searchKlant(char filename[20]) {
    FILE *bestand;
    int artikelGevonden = 0;

    int gezochtArtikelNummer;
    printf("Voer artikelnummer in om te zoeken: ");
    scanf("%d", &gezochtArtikelNummer);


    // Probeer het bestand te openen voor lezen ("r" modus)
    bestand = fopen(filename, "r");

    if (bestand == NULL) {
        printf("Kan het bestand niet openen voor lezen.\n");
        return;
    }

    // Doorloop het bestand en zoek naar het artikelnummer
    struct Artikel artikel;
    while (fscanf(bestand, "%d,%99[^,],%lf,%d\n", &artikel.artikelnummer, artikel.omschrijving, &artikel.prijs, &artikel.voorraad) != EOF) {
        if (artikel.artikelnummer == gezochtArtikelNummer) {
            printf("Artikelnummer: %d\n", artikel.artikelnummer);
            printf("Omschrijving: %s\n", artikel.omschrijving);
            printf("Prijs: %.2lf\n", artikel.prijs);
            printf("Voorraad: %d\n", artikel.voorraad);
            artikelGevonden = 1;
            break; // Artikel gevonden, stop met zoeken
        }
    }

    if (!artikelGevonden) {
        printf("Artikel met artikelnummer %d niet gevonden.\n", gezochtArtikelNummer);
    }

    // Sluit het bestand
    fclose(bestand);
}
*/


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

/*
//functie voor het aanmaken van artikelen
int makeOrder(char filename[20], Klant) {
    FILE *bestand;
    struct Order order;
    struct Klant klant;
    int keuze;
    int choice;
    char orderKlant[50];

    // Probeer het bestand te openen voor appending ("a" modus)
    bestand = fopen(filename, "a");

    if (bestand == NULL) {
        printf("Kan het bestand niet openen voor schrijven.\n");
        return 1;
    }



    do {
        clearScreen();
        
        printf("Is het voor een nieuwe (1) of een bestaande klant (2)?");
        switch(choice){

            case 1: 
            makeKlant(filename);

            break;

            case 2:
            searchKlant(filename);

            orderKlant = Klant;
        }
        
        
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
*/

//Functie voor het artikel menu
void artikelMenu(char filename[20]) {

    int choice;

    do {
        clearScreen();

        printf("Voorraad Beheer Systeem rel. 0.1\n\n" );
        printf("Artikel Menu:\n");
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
                searchProduct(filename);

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
                stockUpdate(filename);
                
                break;

            case 5:
                //bewerk het logboek met notepad
                editDBase(filename);
                                
                break;

            case 6:
                //print de databse op de standaard printer
                

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


void orderMenu(char filename[20]) {

    int choice;

    do {
        clearScreen();

        printf("Voorraad Beheer Systeem rel. 0.1\n\n" );
        printf("Order Menu:\n");
        printf("1. Zoek Order\n");
        printf("2. Nieuwe Order\n");
        printf("3. Pakbon\n");
        printf("4. Factuur\n");
        printf("0. Exit\n");
        printf("Keuze: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Zoek bestaande order
                //searchOrder(filename, artikelNummer);

                break;

            case 2:
                 // Maak een order
                //makeOrder(filename);
                
                break;

            case 3:
                //print database
                //makePakbon(filename);

                break;
            
            case 4:
                //muteer voorraad
                //makeFactuur(orderNummer, klantNaam);
                
                break;

            //case 5:
                //bewerk het logboek met notepad
            //    editDBase(filename);
                                
             //   break;

            //case 6:
                //print de databse op de standaard printer
                

            //    break;

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

void klantMenu(char filename[20]) {

    int choice;

    do {
        clearScreen();

        printf("Voorraad Beheer Systeem rel. 0.1\n\n" );
        printf("Klant Menu:\n");
        printf("1. Zoek Klant\n");
        printf("2. Nieuwe Klant\n");

        printf("0. Exit\n");
        printf("Keuze: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
  

                break;

            case 2:
                 // Maak een nieuwe klant
                makeKlant(filename);
                
                break;

            

            case 0:
                printf("Terug naar startmenu.\n");

                return;

            default:
                printf("Ongeldige keuze. Probeer opnieuw.\n");
        }

        printf("\nDruk op Enter om door te gaan...");
        getchar(); // Wacht op Enter-toets
        getchar(); // Verbruik het newline-karakter in de buffer

    } while (choice != 0);
}
