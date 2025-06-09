

#include <iostream>
#include <string>
#include <vector>

class InOut {
public:
    friend std::ostream& operator << (std::ostream&, InOut&);
    friend std::istream & operator >> (std::istream&, InOut&);
    virtual std::istream& citire(std::istream&) = 0;
    virtual std::ostream& afisare(std::ostream&) const = 0;
};



class Artefact: public InOut {
protected:
    static int contor;
    const int id;
    std::string nume;
    std::string data;
    int pretI; // pretul initial de listare 

public:
    Artefact() : id(++contor) {}
    Artefact(const Artefact&) = default;
    Artefact& operator =(const Artefact&) = default;
    virtual ~Artefact() = default;
    virtual Artefact* clone() const = 0;

    virtual std::string ReturnColectibitate() = 0;
    virtual int GetId() { return this->id; }

    friend std::ostream& operator << (std::ostream&, Artefact&);
    friend std::istream& operator >> (std::istream&, Artefact&);
    virtual std::istream& citire(std::istream&) override;
    virtual std::ostream& afisare(std::ostream&) const override ;
};

std::ostream& Artefact::afisare(std::ostream& out) const{
    out << "Id: " << this->id << "\n";
    out << "Nume: " << this->nume << "\n";
    out << "Data/Era: " << this->data << "\n";
    out << "Pret initial: " << this->pretI << "\n";
    return out;
}
std::ostream& operator << (std::ostream& out, Artefact& obj) {
    return obj.afisare(out);
}
std::istream& Artefact::citire(std::istream& in) {
    std::cout << "Introdu numele: "; in >> nume;
    std::cout << "Introdu data/era: "; in >> data;
    std::cout << "Introdu pretul initial: "; in >> pretI;
    return in;
}
std::istream& operator >> (std::istream& in, Artefact& obj) {
    return obj.citire(in);
}


class Istoric : virtual public Artefact {
protected:
    std::vector<std::string> persoane;

public:
    Istoric() = default;
    Istoric(const Istoric&) = default;
    Istoric& operator =(const Istoric&) = default;
    virtual ~Istoric() = default;
    Artefact* clone() const override {
        return new Istoric(*this);
    }
    std::string ReturnColectibitate(){
        if (persoane.size() >= 3)
            return "ridicat";
        return "scazut";
    }

    friend std::ostream& operator << (std::ostream&, Istoric&);
    friend std::istream& operator >> (std::istream&, Istoric&);
    virtual std::istream& citire(std::istream&) override;
    virtual std::ostream& afisare(std::ostream&) const override;
};
std::ostream& Istoric::afisare(std::ostream& out) const {
    Artefact::afisare(out);
    for (int i = 0; i < persoane.size(); i++)
        std::cout << persoane[i];
    return out;
}
std::ostream& operator << (std::ostream& out, Istoric& obj) {
    return obj.afisare(out);
}
std::istream& Istoric::citire(std::istream& in) {
    Artefact::citire(in);
    int nr;
    std::cout << "Cate persoane istorice sunt mentionate?\n"; in >> nr;
    for (int i = 0; i < nr; i++) {
        std::string persoana;
        std::cout << "Introdu persoana asociata: "; in >> persoana;
        persoane.push_back(persoana);
    }
    return in;
}
std::istream& operator >> (std::istream& in, Istoric& obj) {
    return obj.citire(in);
}



class Artistic : virtual public Artefact {
protected:
    std::string tip;
    std::string material;
public:
    Artistic() = default;
    Artistic(const Artistic&) = default;
    Artistic& operator =(const Artistic&) = default;
    virtual ~Artistic() = default;
    Artefact* clone() const override {
        return new Artistic(*this);
    }
    std::string ReturnColectibitate() {
        if (material == "ulei" || material == "marmura")
            return "ridicat";
        return "scazut";
    }

    friend std::ostream& operator << (std::ostream&, Artistic&);
    friend std::istream& operator >> (std::istream&, Artistic&);
    virtual std::istream& citire(std::istream&) override;
    virtual std::ostream& afisare(std::ostream&) const override;
};
std::ostream& Artistic::afisare(std::ostream& out) const {
    Artefact::afisare(out);
    out << "Tip: " << this->tip << "\n";
    out << "Material : " << this->material << "\n";
    return out;
}
std::ostream& operator << (std::ostream& out, Artistic& obj) {
    return obj.afisare(out);
}
std::istream& Artistic::citire(std::istream& in) {
    Artefact::citire(in);
    std::cout << "Introdu tipul : "; in >> tip;
    std::cout << "Introdu materialul: "; in >> material;
    return in;
}
std::istream& operator >> (std::istream& in, Artistic& obj) {
    return obj.citire(in);
}





class Pretios : virtual public Artefact {
protected:
    std::string nume_designer;
    int greutate;
public:
    Pretios() : nume_designer("Necunoscut") {}
    Pretios(const Pretios&) = default;
    Pretios& operator =(const Pretios&) = default;
    virtual ~Pretios() = default;
    Artefact* clone() const override {
        return new Pretios(*this);
    }
    std::string ReturnColectibitate() {
        if (greutate > 250)
            return "ridicat";
        return "scazut";
    }

    friend std::ostream& operator << (std::ostream&, Pretios&);
    friend std::istream& operator >> (std::istream&, Pretios&);
    virtual std::istream& citire(std::istream&) override;
    virtual std::ostream& afisare(std::ostream&) const override;
};
std::ostream& Pretios::afisare(std::ostream& out) const {
    Artefact::afisare(out);
    out << "Nume designer: " << this->nume_designer<< "\n";
    out << "Greutate: " << this->greutate << "\n";
    return out;
}
std::ostream& operator << (std::ostream& out, Pretios& obj) {
    return obj.afisare(out);
}
std::istream& Pretios::citire(std::istream& in) {
    Artefact::citire(in);
    std::cout << "Introdu numele designerului : "; in >> nume_designer;
    std::cout << "Introdu greutatea: "; in >> greutate;
    return in;
}
std::istream& operator >> (std::istream& in, Pretios& obj) {
    return obj.citire(in);
}




//class Entitate : public InOut {
//protected:
//    static int contor;
//    const int id;
//    int buget;
//    const int pas_licitare;
//    int valoare_confort;
//    std::string preferat;
//    std::string ignorat;
//
//public:
//    Entitate() : id(++contor), pas_licitare(buget){}
//    Entitate(const Entitate&) = default;
//    Entitate& operator =(const Entitate&) = default;
//    virtual ~Entitate() {}
//    virtual Entitate* clone() const = 0;
//
//    friend std::ostream& operator << (std::ostream&, Entitate&);
//    friend std::istream& operator >> (std::istream&, Entitate&);
//    virtual std::istream& citire(std::istream&) override;
//    virtual std::ostream& afisare(std::ostream&) const override;
//
//    virtual bool ContinuaLicitarea() = 0;
//
//};
//std::ostream& Entitate::afisare(std::ostream& out) const {
//    out << "Id: " << this->id << "\n";
//    out << "Nume: " << this->buget << "\n";
//    out << "Data/Era: " << this->pas_licitare << "\n";
//    out << "Artefact preferat: " << this->preferat << "\n";
//    out << "Artefact ignorat: " << this->ignorat << "\n";
//    return out;
//}
//std::ostream& operator << (std::ostream& out, Entitate& obj) {
//    return obj.afisare(out);
//}
//std::istream& Entitate::citire(std::istream& in) {
//    std::cout << "Introdu numele: "; in >> buget;
//    std::cout << "Introdu pretul initial: "; in >> valoare_confort;
//    //int id_pref, id_ign;
//    std::cout << "Introdu numele artefactului preferat: "; in >> this->preferat;
//    std::cout << "Introdu numele artefactului ignorat: "; in >> this->ignorat;
//    //std::cout << "Chiar daca aceste artefacte nu exista in stoc problema tot are logica --> o persoana poate aunge la licitatie cu ideea de artefact preferat pe care nu o gaseste si la fel si pt un artefact ignorat"
//    return in;
//}
//std::istream& operator >> (std::istream& in, Entitate& obj) {
//    return obj.citire(in);
//}

class Entitate : public InOut {
protected:
    static int contor_e;
    const int id_e;
    int buget;
    const int pas_de_licitare;
    int valoare_confort;
    std::string preferat;
    std::string ignorat;

public:
    Entitate() : id_e(++contor_e), pas_de_licitare(buget) {}
    Entitate(const Entitate&) = default;
    Entitate& operator =(const Entitate&) = default;
    virtual ~Entitate() = default;
    virtual Entitate* clone() const = 0;

    virtual bool ContinuaLicitare() = 0;

    friend std::ostream& operator << (std::ostream&, Entitate&);
    friend std::istream& operator >> (std::istream&, Entitate&);
    virtual std::istream& citire(std::istream&) override;
    virtual std::ostream& afisare(std::ostream&) const override;
};

std::ostream& Entitate::afisare(std::ostream& out) const {
    out << "Id: " << this->id_e << "\n";
    out << "Buget: " << this->buget<< "\n";
    out << "Pas de licitare: " << this->pas_de_licitare<< "\n";
    out << "Val comfort: " << this->valoare_confort << "\n";
    out << "Nume artefact pref: " << this->preferat << "\n";
    out << "Nume artefact ignorat: " << this->ignorat << "\n";
    return out;
}
std::ostream& operator << (std::ostream& out, Entitate& obj) {
    return obj.afisare(out);
}
std::istream& Entitate::citire(std::istream& in) {
    std::cout << "Introdu bugetul: "; in >> buget;
    std::cout << "Introdu val de comfort: "; in >> valoare_confort;
    std::cout << "Introdu numele art pref: "; in >> preferat;
    std::cout << "Introdu numele art ignorat: "; in >> ignorat;
    return in;
}
std::istream& operator >> (std::istream& in, Entitate& obj) {
    return obj.citire(in);
}




class Fizica : public Entitate {
protected:

public:
    Fizica() = default;
    Fizica(const Fizica&) = default;
    Fizica& operator =(const Fizica&) = default;
    virtual ~Fizica() {}
    Entitate* clone() const override {
        return new Fizica(*this);
    }
    bool ContinuaLicitare() override {
        return true;
    }

    /*friend std::ostream& operator << (std::ostream&, Fizica&);
    friend std::istream& operator >> (std::istream&, Fizica&);
    virtual std::istream& citire(std::istream&) override;
    virtual std::ostream& afisare(std::ostream&) const override;*/

};



class Juridica : public Entitate {
protected:

public:
    Juridica() = default;
    Juridica(const Juridica&) = default;
    Juridica& operator =(const Juridica&) = default;
    virtual ~Juridica() {}
    Entitate* clone() const override {
        return new Juridica(*this);
    }
    bool ContinuaLicitare() override {
        return true;
    }

    /*friend std::ostream& operator << (std::ostream&, Fizica&);
    friend std::istream& operator >> (std::istream&, Fizica&);
    virtual std::istream& citire(std::istream&) override;
    virtual std::ostream& afisare(std::ostream&) const override;*/

};








class Menu {
private:
    Menu();
    Menu(const Menu&) = delete;
    Menu& operator = (const Menu&) = delete;
    static Menu* menu_ptr;
    static bool ongoing;
    std::vector<Artefact*> stoc_artefacte;
    std::vector<Entitate*> oameni_prezenti;
    std::vector<Artefact*> istoric_licitatie;
public:
    ~Menu() {
        for (int i = 0; i < stoc_artefacte.size(); i++)
            delete stoc_artefacte[i];
        for (int i = 0; i < oameni_prezenti.size(); i++)
            delete oameni_prezenti[i];
    }
    static Menu* GetInstance() {
        if (menu_ptr == nullptr)
            menu_ptr = new Menu();
        return menu_ptr;
    }
    static bool IsOngoing(){ return ongoing; }
    void TurnOff() { ongoing = false; }

    void ShowMenu();
    void SwitchCase(int opt);
    void RunMenu();
    
    void AdaugaParticipant();
    void AdaugaArtefact();
    void AfiseazaParticipanti();
    void AfiseazaArticole();
    bool ExistaArtefact(int id);
    void SimulareLicitatie();
    

};
void Menu::AdaugaParticipant() {
    std::cout << "Ce fel de participant ai vrea sa adaugi?\n";
    std::cout << "1. persoana fizica\n";
    std::cout << "2. persoana juridica\n";
    
    int opt;
    std::cin >> opt;
    switch (opt)
    {
    case 1: {
        Entitate* noua = new Fizica();
        std::cin >> *noua;
        oameni_prezenti.push_back(noua);
        break;
    }
    case 2: {
        Entitate* noua = new Juridica();
        std::cin >> *noua;
        oameni_prezenti.push_back(noua);
        break;
    }
    }
}
void Menu::AdaugaArtefact() {
    std::cout << "Ce fel de artefact ai vrea sa adaugi?\n";
    std::cout << "1. istoric\n";
    std::cout << "2. artistic\n";
    std::cout << "3. pretios\n";

    int opt;
    std::cin >> opt;
    switch (opt)
    {
    case 1:
    {
        Artefact* nou = new Istoric();
        std::cin >> *nou;
        stoc_artefacte.push_back(nou);
        break;
    }
    case 2:
    {
        Artefact* nou = new Artistic();
        std::cin >> *nou;
        stoc_artefacte.push_back(nou);
        break;
    }
    case 3:
    {
        Artefact* nou = new Pretios();
        std::cin >> *nou;
        stoc_artefacte.push_back(nou);
        break;
    }
    }
}
void Menu::AfiseazaParticipanti() {
    for (auto pers : oameni_prezenti)
        std::cout << *pers;
}
void Menu::AfiseazaArticole() {
    for (auto item : stoc_artefacte)
        std::cout << *item;
}
void Menu::SimulareLicitatie() {
    std::cout << "Alege ID-ul artefactului ce urmeaza sa fie vandut:\n";
    int id;
    do {
        std::cin >> id;
    } while (ExistaArtefact(id) == false);
    std::cout << "Artefact gasit, incepe licitatia: \n";

}
bool Menu::ExistaArtefact(int id) {
    for (auto item : stoc_artefacte)
        if (item->GetId() == id)
            return true;
    return false;
}

Menu::Menu() {
    stoc_artefacte.resize(0);
    oameni_prezenti.resize(0);
}
void Menu::ShowMenu() {
    std::cout << "1. adauga participant\n";
    std::cout << "2. adauga artefact\n";
    std::cout << "3. afiseaza participanti\n";
    std::cout << "4. afiseaza articolele disponibile licitatiei\n";
    std::cout << "5. afiseaza gradul de colectibitate pt fiecare artefact\n";
    std::cout << "6. simulare sesiune licitatie\n";
    std::cout << "7. afis participantii in ordine descrescatoare numerelor de artefacte cumparate\n";
    std::cout << "8. afiseaza obiectele cumparate in ordinea descrescatoare pretului cu care au fost cumparate\n";
    std::cout << "9. exit\n";
}
void Menu::SwitchCase(int opt) {
    switch (opt)
    {
    case 1: {
        AdaugaParticipant();
        break;
    }
    case 2: {
        AdaugaArtefact();
        break;
    }
    case 3: {
        AfiseazaParticipanti();
        break;
    }
    case 4: {
        AfiseazaArticole();
        break;
    }
    case 5: {
        for (auto item : stoc_artefacte)
        {
            std::cout << "Pentru item-ul cu id-ul " << item->GetId() << " gradul de colectibitate este: " << item->ReturnColectibitate();
        }
        break;
    }
    case 6: {
        SimulareLicitatie();
        break;
    }
    case 7: {
        break;
    }
    case 8: {

        break;
    }
    case 9: {
        TurnOff();
        break;
    }
    }
}
void Menu::RunMenu() {
    int opt;
    ShowMenu();
    try {
        std::cout << "optiune aleasa: ";
        std::cin >> opt;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw std::string("Tip de date incorect \n");
        }
        if (opt < 1 || opt > 9) {
            throw std::string("Optiune inexistenta\n");
        }
        SwitchCase(opt);
    }
    catch (const std::string& e) {
        std::cout << e << "\n";
    }
}

int Entitate::contor_e = 0;
int Artefact::contor = 0;
Menu* Menu::menu_ptr = nullptr;
bool Menu::ongoing = true;

int main()
{
    Menu* sistem = Menu::GetInstance();
    do {
        sistem->RunMenu();
    } while (Menu::IsOngoing());
    return 0;
}

