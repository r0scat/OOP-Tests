#include <iostream>
#include <string>
#include <vector>
#include <cmath>

class InOut {
public:
    friend std::ostream& operator << (std::ostream&, InOut& obj);
    friend std::istream& operator >> (std::istream&, InOut& obj);
    virtual std::ostream& afisare(std::ostream&)  const = 0;
    virtual std::istream& citire(std::istream&) = 0;

    virtual ~InOut() = default;
};



class Masina : public InOut{
protected:
    std::string nume_model;
    std::string an_productie;
    int viteza;
    int greutate;
public:
    Masina() = default;
    Masina(const Masina&) = default;
    virtual ~Masina() = default;
    Masina& operator=(const Masina&) = default;

    friend std::ostream& operator << ( std::ostream&, Masina& obj);
    friend std::istream& operator >> ( std::istream&, Masina& obj);
    std::ostream& afisare(std::ostream&)  const override;
    std::istream& citire( std::istream&) override;
};

std::ostream &Masina::afisare( std::ostream & out) const {
    out << "Nume Model: " << this->nume_model << "\n";
    out << "Anul productiei: : " << this->an_productie << "\n";
    out << "Viteza: " << this->viteza << " km/h\n";
    out << "Greutate: " << this->greutate << " tone\n";
    return out;
}
std::ostream& operator << (std::ostream& out, Masina& obj) {
    return obj.afisare(out);
}

std::istream &Masina::citire(std::istream & is) {
    std::cout << "Alege numele modelului: "; is >> nume_model;
    std::cout << "Alege anul productiei: "; is >> an_productie;
    std::cout << "Alege viteza: "; is >> viteza;
    std::cout << "Alege greutatea: "; is >> greutate;
    return is;
}
std::istream& operator >> (std::istream& is, Masina& obj) {
    return obj.citire(is);
}


class CombustibilFosil : virtual Masina{
protected:
    int capacitate_rezervor;
    float raport; // raportul capacitate_rezervor/sqrt(greutate)
public:
    CombustibilFosil() : raport(float(capacitate_rezervor/sqrt(greutate))) {}
    CombustibilFosil(const CombustibilFosil&) = default;
    virtual ~CombustibilFosil() = default;
    CombustibilFosil& operator=(const CombustibilFosil&) = default;

    friend std::ostream& operator << ( std::ostream&, CombustibilFosil& obj);
    friend std::istream& operator >> ( std::istream&, CombustibilFosil& obj);
    std::ostream& afisare(std::ostream&)  const override;
    std::istream& citire( std::istream&) override;
};

std::ostream &CombustibilFosil::afisare( std::ostream & out) const {
    Masina::afisare(out);
    out << "Capacitatea rezerovrului: " << this->capacitate_rezervor << "\n";
    out << "Raportul capacitate/greutate: " << this->raport << "\n";
    return out;
}
std::ostream& operator << (std::ostream& out, CombustibilFosil& obj) {
    return obj.afisare(out);
}

std::istream &CombustibilFosil::citire(std::istream & is) {
    Masina::citire(is);
    std::cout << "Alege capacitatea rezervorului: "; is >> capacitate_rezervor;
    std::cout << "Raportul se va calcula in functie de capacitate si greutate! ";
    return is;
}
std::istream& operator >> (std::istream& is, CombustibilFosil& obj) {
    return obj.citire(is);
}



class Electric : virtual public Masina{
protected:
    int capacitate_baterie;
    float raport_baterie_pe_greutate2; // baterie / (greutate*greutate)

public:
    Electric() : raport_baterie_pe_greutate2(float(capacitate_baterie / (greutate* greutate))) {}
    Electric(const Electric&) = default;
    virtual ~Electric() = default;
    Electric& operator=(const Electric&) = default;

    friend std::ostream& operator << ( std::ostream&, Electric& obj);
    friend std::istream& operator >> ( std::istream&, Electric& obj);
    std::ostream& afisare(std::ostream&)  const override;
    std::istream& citire( std::istream&) override;
};

std::ostream &Electric::afisare( std::ostream & out) const {
    Masina::afisare(out);
    out << "Capacitatea bateriei: " << this->capacitate_baterie << "\n";
    out << "Raportul bateriei pe greutate^2: " << this->raport_baterie_pe_greutate2 << "\n";
    return out;
}
std::ostream& operator << (std::ostream& out, Electric& obj) {
    return obj.afisare(out);
}

std::istream &Electric::citire(std::istream & is) {
    Masina::citire(is);
    std::cout << "Alege capacitatea bateriei: "; is >> capacitate_baterie;
    return is;
}
std::istream& operator >> (std::istream& is, Electric& obj) {
    return obj.citire(is);
}




class Hibrid : public CombustibilFosil, public Electric{
protected:
    float suma;
public:
    Hibrid() : suma(raport + raport_baterie_pe_greutate2) {}
    Hibrid(const Hibrid&) = default;
    virtual ~Hibrid() = default;
    Hibrid& operator=(const Hibrid&) = default;

    friend std::ostream& operator << ( std::ostream&, Hibrid& obj);
    friend std::istream& operator >> ( std::istream&, Hibrid& obj);
    std::ostream& afisare(std::ostream&)  const override;
    std::istream& citire( std::istream&) override;
};

std::ostream &Hibrid::afisare( std::ostream & out) const {
    CombustibilFosil::afisare(out);
    out << "Capacitate baterie: " << this->capacitate_baterie << "\n";
    out << "Raport capacitate rezervor si greutate^2: " << this->raport_baterie_pe_greutate2 << "\n";
    out << "Suma capacitatilor: " << this->suma << "\n";
    return out;
}
std::ostream& operator << (std::ostream& out, Hibrid& obj) {
    return obj.afisare(out);
}

std::istream &Hibrid::citire(std::istream & is) {
    CombustibilFosil::citire(is);
    std::cout << "Alege capacitatea bateriei: "; is >> capacitate_baterie;
    return is;
}
std::istream& operator >> (std::istream& is, Hibrid& obj) {
    return obj.citire(is);
}



class Tranzactie:public InOut {
protected:
    std::string nume_client;
    std::string data;
    std::vector<Masina*> modele_achizitionate;
public:
    friend std::ostream& operator << (std::ostream&, Tranzactie&);
    friend std::istream& operator >> (std::istream&, Tranzactie&);
    std::ostream& afisare(std::ostream &) const override;
    std::istream& citire(std::istream&) override;
};

std::ostream& Tranzactie::afisare(std::ostream& out) const {
    out << "Numele Clientului: " << this->nume_client << "\n";
    out << "Data: " << this->data << "\n";
    out << "Achizitii masini: \n";
    for (int i = 0; i < modele_achizitionate.size(); i++) {
        out << "Modelul numarul " << i << "\n";
        out << modele_achizitionate[i] << "\n";
    }
    return out;
}
std::ostream& operator << (std::ostream& out, Tranzactie& obj) {
    return obj.afisare(out);
}

std::istream& Tranzactie::citire(std::istream& is) {
    std::cout << "Alegeti numele clientului: "; is >> nume_client;
    std::cout << "Alegeti data: "; is >> data;
    std::cout << "Pentru a adauga modele achizitionate de catre client, va rugam folositi alta optiune din meniu\n";
}
std::istream& operator >> (std::istream& is, Tranzactie& obj) {
    return obj.citire(is);
}

class Menu {
private:
    Menu() = default;
    static Menu* menu_ptr;
    static bool ongoing;
    std::vector<Masina*> admin_masini;
    std::vector<Tranzactie*> admin_tranzactii;
public:
    virtual ~Menu() = default;
    static Menu* GetInstance() {
        if (menu_ptr == nullptr)
            menu_ptr = new Menu();
        return menu_ptr;
    }
    static bool IsOngoing() {
        return ongoing;
    }
    static void Inchide() {
        ongoing = false;
    }


    void AdaugaMasina();
    void AdaugaTranzactie();
    void AfiseazaCelMaiVandutModel();
    void AfiseazaModelCuCeaMaiMAreAutonomie();
    void OptimizeazaModelSpecific(std::string nume_masina);

    void MesajStart() {
        std::cout << "Alegeti una dintre optiuni:\n";
        std::cout << "1. Adaugati model de masina\n";
        std::cout << "2. Adaugati o tranzactie (specificati insa numele modelului de masina dintre cele deja existente)\n";
        std::cout << "3. Afisati modelul cel mai popular (best seller)\n";
        std::cout << "4. Afisati modelul ce ofera cea mai mare independenta (autonomia cea mai mare)\n";
        std::cout << "5. Optimizati un anumit model (specificati insa numele modelului)\n";
        std::cout << "6. Inchide aplicatia\n";
    }

    void MenuSwitchCase(int optiune) {
        switch (optiune) {
            case 1: {
                AdaugaMasina();
                break;
            }
            case 2: {
                AdaugaTranzactie();
                break;
            }
            case 3: {
                AfiseazaCelMaiVandutModel();
                break;
            }
            case 4: {
                AfiseazaModelCuCeaMaiMAreAutonomie();
                break;
            }
            case 5: {
                std::string nume_masina;
                std::cout << "Introdu numele modelului pe care vrei sa il optimizezi: \n";
                std::cin >> nume_masina;
                OptimizeazaModelSpecific(nume_masina);
                break;
            }
            case 6: {
                Menu::Inchide();
                break;
            }

        }
    }

    void RunMenu() {
        int optiune;
        MesajStart();
        try {
            std::cout << "Optiunea dumneavoastra: ";
            std::cin >> optiune;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw(std::runtime_error("Eroare, tip de date invalid."));
            }

            if (optiune < 1 || optiune > 6)
                throw std::out_of_range("Eroare, introdu un numar intre 1 si 6");
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << "\n";
        }
        MenuSwitchCase(optiune);
    }
};

void Menu::AdaugaMasina() {

}
void Menu::AdaugaTranzactie() {

}
void Menu::AfiseazaCelMaiVandutModel() {

}
void Menu::AfiseazaModelCuCeaMaiMAreAutonomie() {

}
void Menu::OptimizeazaModelSpecific(std::string nume_masina) {

}

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