#Projekty
Budete pracovať s poľom štruktúr reprezentujúcich projekty realizované v IT firme.

O každom projekte by sme mohli uchovávať veľa rôznych informácií, nás bude zaujímať len:

názov projektu (reťazec),
vedúci projektu (reťazec), 
počet zamestnancov (celé číslo),
rozpočet na mzdy (desatinné číslo).
Údaje o projektoch sa nachádzajú vo vstupnom  textovom súbore. V prvom riadku je počet projektov nasledovaný príslušným počtom riadkov s informáciami o projektoch, napr.:

5
A Fero 5 500.0
B Miso 10 10000.0
C Janka 1 300.0
D Tibor 20 450000.0
E Peter 8 20600.0
Úlohy:

1. Definujte údajový typ TProjekt. Dynamicky alokované pole s prvkami typu TProjekt naplňte údajmi zo súboru. Vypíšte načítané dáta na obrazovku. (5 b)

2. Pomocou funkcie qsort() umožnite údaje usporadúvať podľa 2 kritérií - podľa počtu zamestnancov a nákladov na jedného zamestnanca. (5 b)

3. Zistite celkovú sumu, ktorú má na svoje projekty pridelenú zadaný vedúci. Využite funkciu bsearch() a smerníkovú aritmetiku. (5 b)

4. Implementujte funkciu, ktorá do výstupného textového súboru zapíše názvy a mená vedúcich tých projektov, ktoré sú drahšie ako zadaná suma. Funkcia nech má 3 parametre - pole projektov, názov výstupného súboru a suma.

V hlavnom programe otestujte funkčnosť riešenia jednotlivých čiastkových úloh.  Pred koncom programu uvoľnite alokované pole z pamäti.

Každú časť riešenia vyznačte komentárom, napr.:

// Uloha 1

// Uloha 2 

atď.
alebo naprogramujte riešenia čiastkových úloh v osobitných funkciách uloha1(), uloha2() atď.
