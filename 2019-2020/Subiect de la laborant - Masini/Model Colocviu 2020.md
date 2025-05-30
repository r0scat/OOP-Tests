# 15 ianuarie 2020

Vezi modelul de colocviu... ce faci?
- avem nevoie de clasa masina ce va avea urmatoarele atribute: anul inceperii productiei, numele, viteza maxima,  greutatea.
- pentru masini cu combustibil fosil se retine ceva si pt masini electrice altceva --> avem inca doua clase ce vor mosteni clasa de baza masina
- avem nevoie de functie de autonomie pt masina electrica, clasica si hibrida = interfata 
- avem nevoie de tranzactii --> clasa tranzactie cu atributele din enunt
- avem nevoie de un meniu interactiv ce va avea urm posibilitati:
  - adauga model masina + atribute = constructor din masina
  - adauga o tranzactie = constructor tranzactie
  - afiseaza cel mai vandut model = functie pe tranzactie care sa verifice cea mai vanduta masina: *CheckMostSold*
  - afiseaza modelul cu autonomia cea mai mare = la creearea obiectului retinem autonomia cea mai mare --> in masina o functie care tine verifica daca are autonomia cea mai mare
  - aduce optimizare
```cpp
// clasa interfata
class CalculatorAutonomie
{

}

class Masina
{
    int an_incepere_productie;
    std::string nume;
    int viteza maxina;
    int greutate;
};
class MasinaClasica: public Masina
{
    std::string tip_combustibil;
    int capacitate_rezervor;
};
class MasinaElectrica: public Masina
{
    int capactitate_baterie;
};
// aici apare mostenirea diamant --> how to fix??
class MasinaHibrit: public MasinaElectrica, public MasinaClasica
{

};
class Tranzactie
{
    std::string nume_client;
    int data;
    Masina lista_achizitii[10];
    // sau putem face o lista dinamica 
}

int main()
{
    return 0;
}
```