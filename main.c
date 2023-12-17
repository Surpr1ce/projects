#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Úloha 1
typedef struct {
    char nazov[50];
    char veduci[50];
    int pocetZamestnancov;
    double rozpocet;
} TProjekt;

// Načítanie údajov zo súboru do poľa projektov
TProjekt* nacitajProjekty(const char* nazovSuboru, int* pocetProjektov) {
    FILE* subor = fopen(nazovSuboru, "r");
    if (subor == NULL) {
        perror("Chyba pri otvarani suboru");
        exit(EXIT_FAILURE);
    }

    // Načítaj počet projektov
    fscanf(subor, "%d", pocetProjektov);

    // Dynamicky alokuj pole projektov
    TProjekt* projekty = (TProjekt*)malloc(*pocetProjektov * sizeof(TProjekt));
    if (projekty == NULL) {
        perror("Chyba pri alokacii pamati");
        exit(EXIT_FAILURE);
    }

    // Načítaj údaje o projektoch
    for (int i = 0; i < *pocetProjektov; i++) {
        fscanf(subor, "%s %s %d %lf", projekty[i].nazov, projekty[i].veduci,
               &projekty[i].pocetZamestnancov, &projekty[i].rozpocet);
    }

    // Zatvor súbor
    fclose(subor);

    return projekty;
}

// Výpis údajov o projektoch
void vypisProjekty(TProjekt* projekty, int pocetProjektov) {
    for (int i = 0; i < pocetProjektov; i++) {
        printf("%s %s %d %.2lf\n", projekty[i].nazov, projekty[i].veduci,
               projekty[i].pocetZamestnancov, projekty[i].rozpocet);
    }
    printf("\n");
}

// Úloha 2
int podlaPoctuZamestnantcov(const void* a, const void* b) {
    return ((TProjekt*)a)->pocetZamestnancov - ((TProjekt*)b)->pocetZamestnancov;
}

int podlaNakladovNaZamestnanca(const void* a, const void* b) {
    double nakladyA = ((TProjekt*)a)->rozpocet / ((TProjekt*)a)->pocetZamestnancov;
    double nakladyB = ((TProjekt*)b)->rozpocet / ((TProjekt*)b)->pocetZamestnancov;

    // Porovnaj podľa nákladov
    if (nakladyA < nakladyB) return -1;
    if (nakladyA > nakladyB) return 1;

    return 0; // Ak sú náklady rovnaké
}

//Úloha 3
int porovnajProjekty(const void *a, const void *b) {
    return strcmp(((TProjekt *)a)->veduci, ((TProjekt *)b)->veduci);
}

double celkovaSumaPreVeduchoho(TProjekt *projekty, int pocetProjektov, const char *veduci) {
    // Usporiadaj pole projektov podľa vedúceho
    qsort(projekty, pocetProjektov, sizeof(TProjekt), porovnajProjekty);

    // Vytvor dummy projekt so zadaným veducím na vyhľadávanie
    TProjekt hladany;
    strcpy(hladany.veduci, veduci);

    // Vyhľadaj vedúceho v poli projektov
    TProjekt *najdenyVeduci = (TProjekt *)bsearch(&hladany, projekty, pocetProjektov, sizeof(TProjekt), porovnajProjekty);

    // Ak sa vedúci nenašiel, vráť -1
    if (najdenyVeduci == NULL) {
        return -1.0;
    }

    // Vypočítaj celkovú sumu pridelenú vedúcemu
    double celkovaSuma = 0.0;
    for (int i = 0; i < pocetProjektov; i++) {
        if (strcmp(projekty[i].veduci, veduci) == 0) {
            celkovaSuma += projekty[i].rozpocet;
        }
    }

    return celkovaSuma;
}

// Úloha 4
void zapisDrahsieProjektyDoSuboru(TProjekt* projekty, int pocetProjektov, const char* nazovSuboru, double suma) {
    FILE* subor = fopen(nazovSuboru, "w");
    if (subor == NULL) {
        perror("Chyba pri otvarani suboru");
        exit(EXIT_FAILURE);
    }

    // Zapíš drahšie projekty do súboru
    for (int i = 0; i < pocetProjektov; i++) {
        if (projekty[i].rozpocet > suma) {
            fprintf(subor, "%s %s\n", projekty[i].nazov, projekty[i].veduci);
        }
    }

    // Zatvor súbor
    fclose(subor);
}

int main() {
    // Uloha 1
    int pocetProjektov;
    TProjekt* projekty = nacitajProjekty("input.txt", &pocetProjektov);
    vypisProjekty(projekty,pocetProjektov);

    // Uloha 2
    printf("Podla poctu zamestnancov\n");
    qsort(projekty, pocetProjektov, sizeof(TProjekt), podlaPoctuZamestnantcov);
    vypisProjekty(projekty,pocetProjektov);

    printf("Podla nakladov na zamestnanca\n");
    qsort(projekty, pocetProjektov, sizeof(TProjekt), podlaNakladovNaZamestnanca);
    vypisProjekty(projekty,pocetProjektov);

    // Uloha 3
    char veduci[50] = "Miso";
    double suma = celkovaSumaPreVeduchoho(projekty, pocetProjektov, veduci);
    if(suma != -1) {
        printf("Celkova suma, ktoru ma veduci %s na svoje projekty: %0.2f", veduci, suma);
    } else {
        printf("Veduci %s nebol najdeny.\n", veduci);
    }

    // Uloha 4
    zapisDrahsieProjektyDoSuboru(projekty, pocetProjektov, "output.txt", 20000.0);

    // Uvoľnenie alokovanej pamäti
    free(projekty);

    return 0;
}
