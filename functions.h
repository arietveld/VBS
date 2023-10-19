#ifndef FUNCTIONS_H
#define FUNCTIONS_H

struct Artikel {
    int artikelnummer;
    char omschrijving[21];
    double prijs;
    int voorraad;
};

struct Klant {
    char klantNaam[50];
    char klantAdres[50];
    char klantPlaats[50];
    char klantPostcode[10];
    int klantNummer;
};

struct Order {
    int orderNummer;
    int klantReferentie[50];
};

//algemene functies

//VBS programma functies

//klantfuncties
void klantMenu(char filename[20]);
//void searchKlant(char filename[20]);
int vindHoogsteKlantnummer(char filename[20]);


//orderfuncties
void orderMenu(char filename[20]);
//void makeOrder(char filename[20], Klant)

//artikelfuncties
void artikelMenu(char filename[20]);
void printDbase(char filename[20]);
void stockUpdate(char filename[20]);
void searchProduct(char filename[20]);
void editDBase(char filename[20]);
int makeProduct(char filename[20]);





#endif
