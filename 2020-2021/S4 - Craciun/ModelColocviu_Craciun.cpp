
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

//class Chichite
//{
//public:
//    virtual void 
//};
//


class Jucarie
{
protected:
    std::string nume;
    int dimensiune;
    std::string tip;
public:
    Jucarie()
    {
        this->nume = "unknown";
        this->dimensiune = 0;
        this->tip = "unknown";
    }
    Jucarie(std::string nume, int dimensiune, std::string tip)
    {
        this->nume = nume;
        this->dimensiune = dimensiune;
        this->tip = tip;
    }
    Jucarie(const Jucarie& obj)
    {
        this->dimensiune = obj.dimensiune;
        this->nume = obj.nume;
        this->tip = obj.tip;
    }
    virtual ~Jucarie() = default;

    std::string GetNume() const
    {
        return this->nume;
    }
    std::string GetTip() const
    {
        return this->tip;
    }
    int GetDimensiune() const
    {
        return this->dimensiune;
    }

    void SetNume(std::string nume);
    void SetDimensiune(int dimensiune);
    void SetTip(std::string tip);

    friend std::ostream operator << (const std::ostream& out, const Jucarie& obj);
    friend std::istream operator >> (const std::istream& in, Jucarie& obj);
    virtual std::ostream& afisare(std::ostream&) const;
    virtual std::istream& citire(std::istream&);
};

void Jucarie::SetNume(std::string nume) { this->nume = nume; }
void Jucarie::SetDimensiune(int dimensiune) { this->dimensiune = dimensiune; }
void Jucarie::SetTip(std::string tip) { this->tip = tip; }

std::ostream& Jucarie::afisare(std::ostream& out)const
{
    out << "Nume: " << this->nume << "\n";
    out << "Dimensiune: " << this->dimensiune << "\n";
    out << "Tip: " << this->tip << "\n";
    return out;
}
std::ostream& operator << (std::ostream& out, const Jucarie& obj)
{
    return obj.afisare(out);
} 

std::istream& Jucarie::citire(std::istream &in)
{
    std::cout << "Nume: "; in >> nume; std::cout << "\n";
    std::cout << "Dimensiune: "; in >> dimensiune; std::cout << "\n";
    std::cout << "Tip: "; in >> tip; std::cout << "\n";
    return in;
}
std::istream& operator >> (std::istream& is, Jucarie& obj)
{
    return obj.citire(is);
}


// clasic
class Clasic : virtual public Jucarie
{
    std::string material;
    std::string culoare;
public:
    Clasic() = default;
    Clasic(const Clasic&) = default;
    virtual ~Clasic() = default;
    virtual std::ostream& afisare(std::ostream&) const override;
    virtual std::istream& citire(std::istream&) override;
};

std::ostream& Clasic::afisare(std::ostream& out) const
{
    Jucarie::afisare(out);
    out << "Material: " << this->material << "\n";
    out << "Culoare: " << this->culoare << "\n";
    return out;
}
std::istream& Clasic::citire(std::istream& in)
{
    Jucarie::citire(in);
    std::cout << "Material: "; in >> material; std::cout << "\n";
    std::cout << "Culoare: "; in >> culoare; std::cout << "\n";
    return in;
}


// educativ
class Educativ : virtual public Jucarie
{
    std::string abilitate_dezvoltata;
public:
    Educativ() = default;
    Educativ(const Educativ&) = default;
    virtual ~Educativ() = default;
    virtual std::ostream& afisare(std::ostream&) const override;
    virtual std::istream& citire(std::istream&) override;
};

std::ostream& Educativ::afisare(std::ostream& out) const
{
    Jucarie::afisare(out);
    out << "Abilitate Dezvoltata: " << this->abilitate_dezvoltata << "\n";
    return out;
}
std::istream& Educativ::citire(std::istream& in)
{
    Jucarie::citire(in);
    std::cout << "Abilitate Dezvoltata: "; in >> abilitate_dezvoltata; std::cout << "\n";
    return in;
}

// electronic
class Electronic : virtual public Jucarie
{
    int nr_baterii;
public:
    Electronic() = default;
    Electronic(const Electronic&) = default;
    virtual ~Electronic() = default;
    virtual std::ostream& afisare(std::ostream&) const override;
    virtual std::istream& citire(std::istream&) override;
};


std::ostream& Electronic::afisare(std::ostream& out) const
{
    Jucarie::afisare(out);
    out << "Nr baterii: " << this->nr_baterii<< "\n";
    return out;
}
std::istream& Electronic::citire(std::istream& in)
{
    Jucarie::citire(in);
    std::cout << "Nr baterii: "; in >> nr_baterii; std::cout << "\n";
    return in;
}


class Modern: public Electronic, public Educativ
{
    std::string brand;
    std::string model;
public:
    Modern() = default;
    Modern(const Modern&) = default;
    virtual ~Modern() = default;
    virtual std::ostream& afisare(std::ostream&) const override;
    virtual std::istream& citire(std::istream&) override;
};

std::ostream& Modern::afisare(std::ostream& out) const
{
    Jucarie::afisare(out);
    out << "Brand: " << this->brand<< "\n";
    return out;
}
std::istream& Modern::citire(std::istream& in)
{
    Jucarie::citire(in);
    std::cout << "Brand: "; in >> brand; std::cout << "\n";
    return in;
}

class Copil
{
protected:
    static int counter;
    const int id;
    std::string nume;
    std::string prenume;
    std::string adresa;
    int varsta; // in ani
    int nr_bune;  
    std::vector<Jucarie*> jucarii;
public:
    Copil():id(++counter) {}
    Copil(const Copil&) = default;
    virtual ~Copil() = default;
    std::string GetNume() const;
    int GetId() const { return this->id; }
    int GetNrBune() const { return this->nr_bune; }
    int GetVarsta() const { return this->varsta; }
    void PlusJucarie(Jucarie* noua) { jucarii.push_back(noua); }
    std::vector<Jucarie*> GetVectorJucarii() { return this->jucarii; }

    friend std::ostream operator << (const std::ostream& out, const Copil& obj);
    friend std::istream operator >> (const std::istream& in, Copil& obj);
    virtual std::ostream& afisare(std::ostream&) const;
    virtual std::istream& citire(std::istream&);
};

std::ostream& Copil::afisare (std::ostream& out) const
{
    out << "\n";
    out << "Id: " << this->id << "\n";
    out << "Nume complet: " << this->nume << " " << this->prenume << "\n";
    out << "Adresa: " << this->adresa << "\n";
    out << "Varsta: " << this->varsta << " ani \n";
    out << "Numar de fapte bune: " << this->nr_bune << "\n";
    return out;
}

std::ostream& operator<<(std::ostream& out, const Copil& obj)
{
   return obj.afisare(out);
}

std::istream& Copil::citire(std::istream& is)
{
    std::cout << "Alege numele copilului: "; is >> nume; std::cout << "\n";
    std::cout << "Alege prenumele: "; is >> prenume; std::cout << "\n";
    std::cout << "Alege adresa (nu poti introduce spatii): "; is >> adresa; std::cout << "\n";
    std::cout << "Alege varsta: "; is >> varsta; std::cout << "\n";
    std::cout << "Alege nr de fapte bune: "; is >> nr_bune; std::cout << "\n";
    return is;
}

std::istream& operator >> (std::istream& is, Copil& obj)
{
    return obj.citire(is);
}

int Copil::counter = 0;

std::string Copil::GetNume() const { return this->nume; }

class Cuminte : public Copil
{
    int nr_dulciuri;

public:
    Cuminte() = default;
    Cuminte(const Cuminte&) = default;
    virtual ~Cuminte() = default;
    Cuminte& operator =(const Cuminte&) = default;
    bool VerificaNrDulciuri()
    {
        if (nr_dulciuri < 10)
            return false;
        return true;
    }
    void SetDulciuri(int nr)
    {
        this->nr_dulciuri = nr;
    }
    virtual std::ostream& afisare(std::ostream&) const override;
    virtual std::istream& citire(std::istream&) override;
};

std::ostream& Cuminte::afisare(std::ostream& out) const
{
    Copil::afisare(out);
    out << "Numar dulciuri: " << this->nr_dulciuri << "\n";
    return out;
}
std::istream& Cuminte::citire(std::istream& in)
{
    Copil::citire(in);
    std::cout << "Numar dulciuri (trebuie date minim 10 dulciuri unui copil, orice numar mai mic nu va fi luat in calcul): "; 
    do
    {
        in >> nr_dulciuri;
    } while (this->nr_dulciuri < 10);
    
    return in;
}




class Neastamparat : public Copil
{
    int nr_carbuni;
public:
    Neastamparat() = default;
    Neastamparat(const Neastamparat&) = default;
    virtual ~Neastamparat() = default;
    Neastamparat& operator = (const Neastamparat&) = default;

    virtual std::ostream& afisare(std::ostream&) const override;
    virtual std::istream& citire(std::istream&) override;
};

std::ostream& Neastamparat::afisare(std::ostream& out) const
{
    Copil::afisare(out);
    out << "Numar carbuni: " << this->nr_carbuni<< "\n";
    return out;
}
std::istream& Neastamparat::citire(std::istream& in)
{
    Copil::citire(in);
    std::cout << "Numar carbuni: "; in >> nr_carbuni; std::cout << "\n";
    return in;
}



class Menu
{
private:
    Menu() = default;
    Menu(const Menu& obj) = delete;
    Menu& operator=(const Menu&) = delete;
    static Menu* menu_ptr;
    static bool ongoing;
    std::vector<Copil*> toti_copii;
public:
    static Menu* GetInstance()
    {
        if (menu_ptr == nullptr)
        {
            menu_ptr = new Menu();
        }
        return menu_ptr;
    }

    static bool GetOngoing() { return ongoing; }
    static void TurnOff() { ongoing = false; }
    
    std::vector<Copil*> GetCopii();
    Copil* CitesteCopil();
    void AdaugaCopil(Copil* &copil);
    void AfiseazaTotiCopii();
    void AfiseazaNCopii(int n);
    void AfiseazaMenu();
    void AlegeOptiune(int optiune);
    void PornesteMenu();
    void AdaugaJucarii(int id_copil);
    Copil* GasesteCopilDupaId(int id);
    int GasestePozitieCopilDupaId(int id);
    Jucarie* CitesteJucarie();
    void AdaugaJucariePerCopil(Jucarie*, int);
    void AfiseazaToateJucariileTuturor();
    bool LamdaVarsta(Copil* a, Copil* b);
    bool LamdaFapteBune(Copil* a, Copil* b);
};

Menu* Menu::menu_ptr = nullptr;
bool Menu::ongoing = true;

Copil* Menu::CitesteCopil()
{
    int optiune;
    std::cout << "Ce fel de copil vrei sa adaugi in baza de date/ vector?\n";
    std::cout << "1. cuminte\n";
    std::cout << "2. neastamparat\n";
    std::cin >> optiune; std::cout << "\n";
    if (optiune == 1)
    {
        Copil* de_adaugat = new Cuminte();
        std::cin >> *de_adaugat;
        return de_adaugat;
    }
    else
        if (optiune == 2)
        {
            Copil* de_adaugat = new Neastamparat();
            std::cin >> *de_adaugat;
            return de_adaugat;
        } 
        else
            std::cout << "Alegere invalida...\n";
    return nullptr;
}

void Menu::AfiseazaTotiCopii()
{
    for (auto item : this->GetCopii())
    {
        std::cout << *item;
        std::cout << "\n";
    }
}

std::vector<Copil*> Menu::GetCopii()
{
    return toti_copii;
}

void Menu::AfiseazaNCopii(int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << *this->GetCopii()[i];
        std::cout << "\n";
    }
}

void Menu::AdaugaCopil(Copil* &copil)
{
    toti_copii.push_back(copil);
}

Copil* Menu::GasesteCopilDupaId(int id)
{
    for (int i = 0; i < this->GetCopii().size(); i++)
    {
        Copil ajutator = *this->GetCopii()[i];
        if (ajutator.GetId() == id)
            return this->GetCopii()[i];
    }
}

int Menu::GasestePozitieCopilDupaId(int id)
{
    for (int i = 0; i < this->GetCopii().size(); i++)
    {
        Copil ajutator = *this->GetCopii()[i];
        if (ajutator.GetId() == id)
            return i;
    }
}

Jucarie* Menu::CitesteJucarie()
{
    int optiune;
    std::cout << "Ce fel de jucarie vreo sa adaugi?\n";
    std::cout << "1. clasica\n";
    std::cout << "2. educativa\n";
    std::cout << "3. electronica\n";
    std::cout << "4. moderna\n";

    std::cin >> optiune;
    switch (optiune)
    {
    case 1:
    {
        Jucarie* de_adaugat = new Clasic();
        std::cin >> *de_adaugat;
        return de_adaugat;
        break;
    }
    case 2:
    {
        Jucarie* de_adaugat = new Educativ();
        std::cin >> *de_adaugat;
        return de_adaugat;
        break;
    }
    case 3:
    {
        Jucarie* de_adaugat = new Electronic();
        std::cin >> *de_adaugat;
        return de_adaugat;
        break;
    }
    case 4:
    {
        Jucarie* de_adaugat = new Modern();
        std::cin >> *de_adaugat;
        return de_adaugat;
        break;
    }
    default:
    {
        std::cout << "Optiune invalida...\n";
        return nullptr;
        break;
    }
        
    }
}

void Menu::AdaugaJucariePerCopil(Jucarie* noua, int pos)
{
    toti_copii[pos]->PlusJucarie(noua);
}

void Menu::AdaugaJucarii(int id)
{
    int pos = GasestePozitieCopilDupaId(id);
    std::cout << pos << "\n";
    for (int i = 0; i < toti_copii[pos]->GetNrBune(); i++)
    {
        Jucarie* noua = CitesteJucarie();
        AdaugaJucariePerCopil(noua, pos);
    }
}

void Menu::AfiseazaToateJucariileTuturor()
{
    for (auto copil : toti_copii)
    {
        std::cout << "\nPentru copilul cu id-ul " << copil->GetId() << " avem urmatoarele jucarii: \n";
        for (auto jucarie : copil->GetVectorJucarii())
            std::cout << *jucarie << "\n";
        std::cout << "\n";
    }
        
}

void Menu::AfiseazaMenu()
{
    std::cout << "1. Citeste si adauga datele citite pentru un copil\n";
    std::cout << "2. Afiseaza primii n copii memorati (n va fi introdus de la tastatura)\n";
    std::cout << "3. Pentru un copil (trebuie introdus id-ul copilului) citeste si memoreaza jucariile necesare (se vor citi atatea jucarii cate fapte bune)\n";
    std::cout << "4. Pentru toti copii afiseaza jucariile acestora\n";
    std::cout << "5. Ordoneaza copii dupa varsta\n";
    std::cout << "6. Ordoneaza copii dupa numarul de fapte bune\n";
    std::cout << "7. Afiseaza raportul jucariilor\n";
    std::cout << "8. Inchide aplicatia\n";
}

bool Menu::LamdaVarsta(Copil* a, Copil* b)
{
    return a->GetVarsta() < b->GetVarsta();
}

bool LamdaFapteBune(Copil* a, Copil* b)
{
    return a->GetNrBune() < b->GetNrBune();
}

void Menu::AlegeOptiune(int optiune)
{
    system("cls");
    switch (optiune)
    {
    case 1:
    {
        Copil* de_adaugat = CitesteCopil();
        AdaugaCopil(de_adaugat);
        break;
    }
    case 2:
    {
        int n;
        std::cout << "Introdu un numar n (cati copii vei afisa; daca introduci 0 se vor afisa toti)\n";
        std::cin >> n;
        if (n == 0)
            AfiseazaTotiCopii();
        else
            AfiseazaNCopii(n);
        break;
    }
    case 3:
    {
        int id_copil;
        std::cout << "Introdu id-ul copilului caruia vrei sa ii adaugi jucarii: \n";
        std::cin >> id_copil;
        AdaugaJucarii(id_copil);
        break;
    }
    case 4:
    {
        AfiseazaToateJucariileTuturor();
        break;
    }
    case 5:
    {
        std::sort(toti_copii.begin(), toti_copii.end(), LamdaVarsta);
        std::cout << "Sortare facuta cu succes!\n";
        break;
    }
    case 6:
    {
        std::sort(toti_copii.begin(), toti_copii.end(), LamdaFapteBune);
        std::cout << "Sortare facuta cu succes!\n";
        break;
    }
    case 7:
    {
        break;
    }
    case 8:
    {
        Menu::TurnOff();
        break;
    }
    default:
        break;
    }
}

void Menu::PornesteMenu()
{
    int optiune;
    AfiseazaMenu();
    try
    {
        std::cout << "Optiunea ta: ";
        std::cin >> optiune;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw std::runtime_error("Eroare, tip de date invalid");
        }

        if (optiune < 1 || optiune > 8) {
            throw std::out_of_range("Eroare, optiune invalida (trebuie sa fie intre 1 si 8)");
        }

        //std::cout << optiune;
        AlegeOptiune(optiune);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << "\n";
    }
}


int main()
{
    Menu* sistem = Menu::GetInstance();

    while (Menu::GetOngoing())
    {
        sistem->PornesteMenu();
    }
    return 0;
}
