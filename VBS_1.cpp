#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char filename[20];

struct Artikel {
    int artikelnummer;
    char omschrijving[100];
    double prijs;
    int voorraad;
};

// Clearscreen functie
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

//wis bovenste tekstblok
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

//functie voor het bewerken van de dBase in excel
void editDBase() {

    char commando[200];
    sprintf(commando, "notepad.exe %s", filename);

    // Open het bestand met Notepad
    system(commando);

    return;
}

//functie voor het aanmaken van artikelen
int makeProduct() {
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

        printf("Voer de omschrijving in: ");
        scanf(" %[^\n]s", artikel.omschrijving);

        printf("Voer de prijs in: ");
        scanf("%lf", &artikel.prijs);

        printf("Voer de voorraad in: ");
        scanf("%d", &artikel.voorraad);

        // Schrijf de artikelinformatie naar het bestand
        fprintf(bestand, "%d,%s,%.2lf,%d\n", artikel.artikelnummer, artikel.omschrijving, artikel.prijs, artikel.voorraad);

        printf("Artikel opgeslagen in het bestand.\n");
        //Toon de volledige QSO op het scherm
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
void makeMenu(){

    int choice;

    do {
        clearScreen();

        printf("Voorraad Beheer Systeem rel. 0.1\n\n" );
        printf("Menu:\n");
        printf("1. Zoek Product\n");
        printf("2. Nieuw Product\n");
        printf("3. Print voorraadlijst\n");
        printf("4. --\n");
        printf("5. Bewerk de database in Notepad\n");
        printf("0. Exit\n");
        printf("Keuze: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Vraag de gebruiker om de Header parameters in te vullen
                //searchProduct();

                break;

            case 2:
                 // Vraag de gebruiker om de QSO parameters in te vullen
                makeProduct();
                
                break;

            case 3:
                //log afsluiten
                //printDBase();

                break;
            
            case 4:
                //laat logbook zien
                

                break;

            case 5:
                //bewerk het logboek met notepad
                editDBase();
                
                
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



// Bij het starten van het programma kan de filename en callsign worden meegegeven

int main(int argc, char *argv[]){
    

    if (argc == 2) {
    strcpy(filename, argv[1]);
    
    }
    else {
        printf("Geef de naam van het bestand: \n");
        scanf("%s",filename);
    }
    
    
    fflush(stdin);

    makeMenu();
        
    return 0;
}