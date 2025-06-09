/*
Colocviul pe care l-am dat eu!
Asta este exact ceea ce am scris (n-am modificat decat comentariul asta)
Nota luata: waiting... (a fost groaznic vreau doar sa trec si am scris 600 de linii de cod...) 
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>

class InOut {
public:
    friend std::ostream& operator << (std::ostream&, InOut&);
    friend std::istream& operator >> (std::istream&, InOut&);
    virtual std::ostream& afisare(std::ostream&) const = 0;
    virtual std::istream& citire(std::istream&) = 0;
};

class Produs :public InOut {
protected:
    std::string nume;
    int gramaj;
public:
    Produs() = default;
    Produs(const Produs&) = default;
    virtual ~Produs() = default;
    Produs& operator = (const Produs&) = default;
    virtual Produs* clone() const = 0;

    void SetNume(std::string nume) { this->nume = nume; }
    void SetGramaj(int gramaj) { this->gramaj = gramaj; }
    int GetGramaj() const { return this->gramaj; }
    std::string GetNume() const { return this->nume; }


    virtual float CalculEnergie() = 0;


    friend std::ostream& operator << (std::ostream&, Produs&);
    friend std::istream& operator >> (std::istream&, Produs&);
    virtual std::ostream& afisare(std::ostream&) const;
    virtual std::istream& citire(std::istream&);
};
std::ostream& Produs::afisare(std::ostream& out) const {
    out << "Nume: " << this->nume << "\n";
    out << "gramaj: " << this->gramaj<< "\n";
    return out;
}
std::ostream& operator << (std::ostream& out, Produs& obj) {
    return obj.afisare(out);
}
std::istream& Produs::citire(std::istream& in) {
    std::cout << "nume: "; in >> nume;
    std::cout << "gramaj: "; in >> gramaj;
    return in;
}
std::istream& operator >> (std::istream& in, Produs& obj) {
    return obj.citire(in);
}



class Bautura : virtual public Produs{
protected:
    bool sticla;
public:
    Bautura() = default;
    Bautura(const Bautura&) = default;
    virtual ~Bautura() = default;
    Bautura& operator = (const Bautura&) = default;
    Produs* clone() const override {
        return new Bautura(*this);
    }

    void SetSticla(bool sticla) { this->sticla = sticla; }
    float CalculEnergie() override;

    friend std::ostream& operator << (std::ostream&, Bautura&);
    friend std::istream& operator >> (std::istream&, Bautura&);
    std::ostream& afisare(std::ostream&) const;
    std::istream& citire(std::istream&);
};
float Bautura::CalculEnergie() {
    if (sticla) // ma gandesc ca daca e la sticla e la PET (nu se intelege complet din cerinta ?)
        return 25;
    return (0.25 * gramaj);
}
std::ostream& Bautura::afisare(std::ostream& out) const {
    Produs::afisare(out);
    out << "sticla: " << this->sticla<< "\n";
    return out;
}
std::ostream& operator << (std::ostream& out, Bautura& obj) {
    return obj.afisare(out);
}
std::istream& Bautura::citire(std::istream& in) {
    Produs::citire(in);
    std::cout << "sticla: "; in >> sticla;
    return in;
}
std::istream& operator >> (std::istream& in, Bautura& obj) {
    return obj.citire(in);
}



class Desert : virtual public Produs {
protected:
    std::string format; // felie cupa sau portie
public:
    Desert() = default;
    Desert(const Desert&) = default;
    virtual ~Desert() = default;
    Desert& operator = (const Desert&) = default;
    Produs* clone() const override {
        return new Desert(*this);
    }

    float CalculEnergie() override;

    friend std::ostream& operator << (std::ostream&, Desert&);
    friend std::istream& operator >> (std::istream&, Desert&);
    std::ostream& afisare(std::ostream&) const;
    std::istream& citire(std::istream&);
};
float Desert::CalculEnergie() {
    if (format == "felie")
        return 25;
    if (format == "cupa")
        return 2 * gramaj;
    return (0.5 * gramaj);
}
std::ostream& Desert::afisare(std::ostream& out) const {
    Produs::afisare(out);
    out << "format: " << this->format << "\n";
    return out;
}
std::ostream& operator << (std::ostream& out, Desert& obj) {
    return obj.afisare(out);
}
std::istream& Desert::citire(std::istream& in) {
    Produs::citire(in);
    std::cout << "format (se va accepta doar felie cupa sau portie): "; 
    do {
        in >> format;
    } while (format != "felie" && format != "cupa" && format != "portie");
    return in;
}
std::istream& operator >> (std::istream& in, Desert& obj) {
    return obj.citire(in);
}




class Burger : virtual public Produs {
protected:
    std::vector<std::string> ingrediente;
public:
    Burger() = default;
    Burger(const Burger&) = default;
    virtual ~Burger() = default;
    Burger& operator = (const Burger&) = default;
    Produs* clone() const override {
        return new Burger(*this);
    }

    float CalculEnergie() override;

    friend std::ostream& operator << (std::ostream&, Burger&);
    friend std::istream& operator >> (std::istream&, Burger&);
    std::ostream& afisare(std::ostream&) const;
    std::istream& citire(std::istream&);
};
float Burger::CalculEnergie() {
    return (gramaj * ingrediente.size());
}
std::ostream& Burger::afisare(std::ostream& out) const {
    Produs::afisare(out);
    out << "Ingrediente: ";
    for (auto item : ingrediente) {
        out << item << " ";
    }
    out << "\n";
    return out;
}
std::ostream& operator << (std::ostream& out, Burger& obj) {
    return obj.afisare(out);
}
std::istream& Burger::citire(std::istream& in) {
    Produs::citire(in);
    
    std::cout << "Cate ingrediente ai vrea sa aiba burgerul???\n";
    int nr;
    in >> nr;
    for (int i = 0; i < nr; i++) {
        std::string nou;
        std::cout << "introdu ingredient: "; in >> nou;
        ingrediente.push_back(nou);
    }  
    return in;
}
std::istream& operator >> (std::istream& in, Burger& obj) {
    return obj.citire(in);
}



class Angajat :public InOut {
protected:
    std::string nume;
    int energie;
public:
    Angajat() : nume(""), energie(100) {}
    Angajat(const Angajat&) = default;
    virtual ~Angajat() = default;
    Angajat& operator = (const Angajat&) = default;

    void SetNume(std::string nume) { this->nume = nume; }
    void SetEnergie(int energie) { this->energie= energie; }
    int GetEnergie() const { return this->energie; }
    std::string GetNume() const { return this->nume; }

    virtual void ResetEnergie() = 0;
    virtual std::string ReturnTipAngajat() = 0;


    friend std::ostream& operator << (std::ostream&, Angajat&);
    friend std::istream& operator >> (std::istream&, Angajat&);
    virtual std::ostream& afisare(std::ostream&) const;
    virtual std::istream& citire(std::istream&);
};
std::ostream& Angajat::afisare(std::ostream& out) const {
    out << "Nume: " << this->nume << "\n";
    out << "energie: " << this->energie << "\n";
    return out;
}
std::ostream& operator << (std::ostream& out, Angajat& obj) {
    return obj.afisare(out);
}
std::istream& Angajat::citire(std::istream& in) {
    std::cout << "nume: "; in >> nume;
    std::cout << "energie: "; in >> energie;
    return in;
}
std::istream& operator >> (std::istream& in, Angajat& obj) {
    return obj.citire(in);
}



class Casier :public Angajat {
public:
    Casier() = default;
    Casier(const Casier&) = default;
    virtual ~Casier() = default;
    Casier& operator = (const Casier&) = default;

    virtual void ResetEnergie() {
        energie = 100;
    }
    virtual std::string ReturnTipAngajat() {
        return "casier";
    }
};




class Livrator :public Angajat {
public:
    Livrator() = default;
    Livrator(const Livrator&) = default;
    virtual ~Livrator() = default;
    Livrator& operator = (const Livrator&) = default;

    virtual void ResetEnergie() {
        energie = 100;
    }
    virtual std::string ReturnTipAngajat() {
        return "livrator";
    }
};



class Bucatar :public Angajat {
private:
    int nr_cicluri;
public:
    Bucatar() : nr_cicluri(0) {}
    Bucatar(const Bucatar&) = default;
    virtual ~Bucatar() = default;
    Bucatar& operator = (const Bucatar&) = default;

    virtual void ResetEnergie() {
        this->nr_cicluri += 1;
        energie = nr_cicluri * 100 + 100; // pt primul ciclu are 100 pt al doilea 200 lalala
    }
    virtual std::string ReturnTipAngajat() {
        return "bucatar";
    }
};



class Comanda : public InOut {
protected:
    static int contor;
    int id;
    bool terminata;
    std::vector<Produs*> produse;
public:
    Comanda() : id(++contor) , terminata(false) {
        this->produse.resize(0);
    }
    ~Comanda() {
        for (int i = 0; i < produse.size(); i++)
            delete produse[i];
    }
    Comanda(const Comanda& c) {
        produse.resize(0);
        for (int i = 0; i < c.produse.size(); i++) {
            produse.push_back(c.produse[i]->clone());
        }

    }
    /*friend std::ostream& operator << (std::ostream&, Comanda&);
    friend std::istream& operator >> (std::istream&, Comanda&);
    std::ostream& afisare(std::ostream&) const;
    std::istream& citire(std::istream&);*/
};
//std::ostream& Comanda::afisare(std::ostream& out) const {
//
//    return out;
//}
//std::ostream& operator << (std::ostream& out, Comanda& obj) {
//    return obj.afisare(out);
//}
//std::istream& Comanda::citire(std::istream& in) {
//
//    return in;
//}
//std::istream& operator >> (std::istream& in, Comanda& obj) {
//    return obj.citire(in);
//}


class Menu {
private:
    Menu();
    Menu(const Menu&) = delete;
    Menu& operator = (const Menu&) = delete;
    static Menu* ptr;
    static bool ongoing;
    std::vector<Produs*> meniu;
    std::vector<Angajat*> angajati;
    std::vector<Comanda> comenzi;
public:
    ~Menu();
    static Menu* GetInstance() {
        if (ptr == nullptr)
            ptr = new Menu();
        return ptr;
    }

    void AdaugaBautura(); // citit
    void AdaugaBurger(); // asta va fi citit 
    void AdaugaDesert(); // si asta inl citesc
    void AdaugaCasier(std::string);
    void AdaugaBucatar(std::string);
    void AdaugaLivrator(std::string);
    void AfiseazaAngajati();
    void AfiseazaNrAngajatiPtFiecareTipInParte();
    void StartSimulare();
    void TerminaComanda();
    void AdaugaComanda();

    static bool IsOngoing() { return ongoing; }
    void TurnOff() { ongoing = false; }
    void ShowMenu();
    void SwitchCase(int opt);
    void RunMenu();
};
void Menu::AdaugaComanda() {

}
void Menu::TerminaComanda() {
    std::cout << "Alege ce comanda vrei sa termini: \n";

}
void Menu::StartSimulare() {
    std::cout << "Alege angajatul (dupa index): ";
    int index;
    std::cin >> index;
    if (index <= angajati.size() && index >= 0)
    {
        std::cout << "angajat ales!\nce ai vrea sa faca?";
        std::cout << "1. livreaza comanda\n";
        std::cout << "2. termina comanda (consuma toata energia indiferent de cat a ramas)\n";

        int opt;
        std::cin >> opt;
        switch (opt)
        {
        case 1:
        {

            break;
        }
        case 2:
        {
            TerminaComanda();
            break;
        }
        }
    }
}
void Menu::AfiseazaNrAngajatiPtFiecareTipInParte() {
    int nrB = 0, nrL = 0, nrC = 0;
    for (auto ang : angajati)
    {
        if (ang->ReturnTipAngajat() == "bucatar")
            nrB++;
        if (ang->ReturnTipAngajat() == "livrator")
            nrL++;
        if (ang->ReturnTipAngajat() == "casier")
            nrC++;
    }
    std::cout << "Sunt " << nrB << " bucatari\n";
    std::cout << "Sunt " << nrL << " livrator\n";
    std::cout << "Sunt " << nrC << " casieri\n";
}
void Menu::AdaugaBautura() {
    Produs* nou = new Bautura();
    std::cin >> *nou;
    meniu.push_back(nou);
}
void Menu::AdaugaBurger() {
    Produs* nou = new Burger();
    std::cin >> *nou;
    meniu.push_back(nou);
}
void Menu::AdaugaDesert() {
    Produs* nou = new Desert();
    std::cin >> *nou;
    meniu.push_back(nou);
}
void Menu::AdaugaCasier(std::string nume) {
    Angajat* nou = new Casier();
    nou->SetNume(nume);
    angajati.push_back(nou);
}
void Menu::AdaugaBucatar(std::string nume) {
    Angajat* nou = new Bucatar();
    nou->SetNume(nume);
    angajati.push_back(nou);
}
void Menu::AdaugaLivrator(std::string nume) {
    Angajat* nou = new Livrator();
    nou->SetNume(nume);
    angajati.push_back(nou);
}
void Menu::AfiseazaAngajati() {
    for (auto item : angajati) {
        std::cout << *item << "\n";
    }
}
Menu::Menu() {
    this->angajati.resize(0);
    this->meniu.resize(0);
}
Menu::~Menu() {
    for (int i = 0; i < meniu.size(); i++)
        delete meniu[i];
    for (int i = 0; i < angajati.size(); i++)
        delete angajati[i];
}

void Menu::ShowMenu() {
    std::cout << "1. Afiseaza nr de angajati pt fiecare tip in parte\n";
    std::cout << "2. Start simulare\n";
    std::cout << "3. Adauga comenzi prioritare\n";
    std::cout << "4. Optimizare ciclu\n";
    std::cout << "5. Selecteaza strategia de preluare comenzi\n";
    std::cout << "5. Exit\n";
}
void Menu::SwitchCase(int opt) {
    switch (opt)
    {
    case 1:
    {
        AfiseazaNrAngajatiPtFiecareTipInParte();
        break;
    }
    case 2:
    {
        StartSimulare();
        break;
    }
    case 3:
    {
        std::cout << "nope...\n";
        break;
    }
    case 4:
    {
        std::cout << "nope...\n";
        break;
    }
    case 5:
    {
        std::cout << "nope...\n";
        break;
    }
    case 6:
    {
        TurnOff();
        break;
    }
    }
}
void Menu::RunMenu() {
    int opt;
    ShowMenu();
    try {
        std::cout << "optiunea ta: ";
        std::cin >> opt;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw std::string("tip de date invalid\n");
        }
        if (opt < 1 || opt > 5)
            throw std::string("optiune invalida\n");
        SwitchCase(opt);
    }
    catch (const std::string& e) {
        std::cout << e << "\n";
    }
}

Menu* Menu::ptr = nullptr;
bool Menu::ongoing = true;
int Comanda::contor = 0;

int main()
{
    Menu* sistem = Menu::GetInstance();

    // angajatii sunt hardcoded pt ca asa are sens
    sistem->AdaugaCasier("Albert");
    sistem->AdaugaLivrator("Radu");
    sistem->AdaugaBucatar("Visan");
    sistem->AdaugaBucatar("Mara");

    std::cout << "Angajatii localului sunt: \n";
    sistem->AfiseazaAngajati();

    // produse alese inainte de afisare meniu
    std::cout << "Cate produse vrei sa pui in meniu? (va trebui sa introduci atatea + specifici pt fiecare tipul)\n";
    int nr;
    std::cin >> nr;
    for (int i = 0; i < nr; i++)
    {
        std::cout << "Ce fel de produs vr sa adaugi?\n";
        std::cout << "1. burger\n";
        std::cout << "2. bautura\n";
        std::cout << "3. desert\n";

        int opt;
        std::cin >> opt;
        switch (opt)
        {
        case 1:
        {
            sistem->AdaugaBurger();
            break;
        }
        case 2:
        {
            sistem->AdaugaBautura();
            break;
        }
        case 3:
        {
            sistem->AdaugaDesert();
            break;
        }
        }
    }

    //sistem->AdaugaProdus(burger);


    do {
        sistem->RunMenu();
    } while (Menu::IsOngoing());
    return 0;
}

