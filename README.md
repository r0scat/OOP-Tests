# Colectie Subiecte si Rezolvari C++ OOP

Acest repository conține o colecție de subiecte de examen/colocviu la disciplina "Programare Orientată pe Obiecte" (C++) și soluții implementate pentru acestea. Scopul este de a oferi resurse pentru studenți, exemplificând diverse concepte OOP și bune practici de codare.

## Subiecte și Soluții Incluse

### 1. Sistem de Gestiune Mașini

* **Subiect:** `Subiecte/Colocviu OOP 15 ian 2020-1.pdf`
    * _Descriere:_ Gestionarea modelelor de autoturisme (combustibili fosili, electrice, hibride), calculul autonomiei, tranzacții. Necesită implementarea unei ierarhii de clase, polimorfism, și un meniu interactiv. Menționează problema "romb" (moștenire multiplă și virtuală).
* **Rezolvare:** `Rezolvari/ModelColocviuMasini(Momentan incomplet).cpp`
    * _Stare:_ **Incompletă**. Prezintă o structură solidă de clase și meniu, supraîncărcare de operatori și tratare a excepțiilor, dar logica de business (calcul autonomie, tranzacții) este în mare parte lipsă.
    * _Concepte OOP Exemplificate:_ Ierarhie de clase, polimorfism, supraîncărcare operatori, tratarea excepțiilor.

### 2. Sistem de Gestiune Măști și Dezinfectanți

* **Subiect:** `Subiecte/Subiect 01.pdf`
    * _Descriere:_ Gestionarea măștilor (chirurgicale, policarbonat) și dezinfectanților (bacterii, fungi, viruși, toate), calculul eficienței, achiziții.
* **Rezolvare:** `Rezolvari/Model-Masti.cpp`
    * _Concepte OOP Exemplificate:_ Ierarhie de clase (abstracte), polimorfism, supraîncărcare operatori, tratarea excepțiilor, utilizarea vectorilor de pointeri la baza.

### 3. Sistem de Gestiune Moș Crăciun (Copii și Jucării)

* **Subiect:** `Subiecte/Subiect 04.pdf`
    * _Descriere:_ Gestionarea copiilor (fapte bune/rele, vârstă) și a jucăriilor (electronice, pluș, moderne), sortări, rapoarte.
* **Rezolvări:**
    * `Rezolvari/ModelColocviu_Craciun.cpp`
    * `Rezolvari/RezolvareTutoriat.cpp`
    * _Concepte OOP Exemplificate:_ Ierarhie de clase, polimorfism, supraîncărcare operatori, tratarea excepțiilor, **Design Pattern Singleton** (pentru `MosCraciun`/`Craciun`), **Lambda expressions** (pentru sortare), `clone()` (în `RezolvareTutoriat.cpp`).
    
### 4. Sistem de Gestiune Drumuri și Contracte

* **Subiect:** `Subiecte/2022 - 2023 .pdf`
    * _Descriere:_ Gestionarea drumurilor (național, european, autostradă, autostradă-europeană) și a contractelor.
* **Rezolvare:** `Rezolvari/ModelColocviu_Drumuri_2022-2023.cpp`
    * _Concepte OOP Exemplificate:_ Ierarhie de clase (abstracte), polimorfism, supraîncărcare operatori, tratarea excepțiilor, **Moștenire Multiplă și Virtuală**.
    
### 5. Sistem de Gestiune Restaurant (Comenzi, Produse, Angajați)

* **Subiect:** `Subiecte/Colocviu iunie 2025 info.pdf`
    * _Descriere:_ Sistem de gestionare a comenzilor și angajaților dintr-un restaurant. Include diverse tipuri de produse (băuturi, deserturi, burgeri) cu calcul specific de energie, angajați (casieri, bucătari, livratori) cu consum de energie, și un simulator de ciclu zilnic.
* **Rezolvare:** `Rezolvari/ModelColocviu_Restaurant.cpp`
    * _Concepte OOP Exemplificate:_ Ierarhie de clase (abstracte), polimorfism (cu `clone()`), supraîncărcare operatori (inclusiv `+=`), tratarea excepțiilor, **Design Pattern Singleton**.
    
## Cum să Compilezi și să Rulezi

Pentru a compila și rula oricare dintre soluțiile `.cpp`, poți folosi un compilator C++ modern (de exemplu, g++).

Exemplu (pentru `Model-Masti.cpp`):

```bash
g++ Model-Masti.cpp -o masti_app -std=c++11
./masti_app