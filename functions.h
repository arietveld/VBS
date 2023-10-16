#ifndef FUNCTIONS_H
#define FUNCTIONS_H

struct Artikel {
    int artikelnummer;
    char omschrijving[21];
    double prijs;
    int voorraad;
};

//algemene functies
void makeMenu(char filename[20], int artikelNummer, int update);
void clearScreen();
void clearHigh();

//VBS programma functies
void printDbase(char filename[20]);
void stockUpdate(char filename[20], int artikelNummer, int update);
void searchProduct(char filename[20], int artikelNummer);
void editDBase(char filename[20]);
int makeProduct(char filename[20]);




#endif
