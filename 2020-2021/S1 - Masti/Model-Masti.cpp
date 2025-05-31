#include <iostream>
#include <string>
#include <vector>
#include <cmath>


// interfata
class InOut {
public:
    friend std::ostream& operator << (std::ostream&, InOut&);
    friend std::istream& operator >> (std::istream&, InOut&);
    virtual std::ostream& afisare(std::ostream&) const = 0;
    virtual std::istream& citire(std::istream&) = 0;
};


// masca
class Masca : public InOut { // cls abstracta
protected:
    std::string tip_protectie;
public:
    virtual ~Masca() = default;
    Masca& operator = (const Masca&) = default;

    friend std::ostream& operator << (std::ostream&, Masca&);
    friend std::istream& operator >> (std::istream&, Masca&);
    virtual std::ostream& afisare(std::ostream&) const override;
    virtual std::istream& citire(std::istream&) override;
};
std::ostream& Masca::afisare(std::ostream& out) const {
    out << "Tip portectie: " << this->tip_protectie << "\n";
    return out;
}
std::ostream& operator << (std::ostream& out, Masca& obj) {
    return obj.afisare(out);
}
std::istream& Masca::citire(std::istream& in) {
    std::cout << "Alege tipul protectiei: "; in >> tip_protectie;
    return in;
}
std::istream& operator >> (std::istream& in, Masca& obj) {
    return obj.citire(in);
}


// chirurcical !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
class Chirurgical : virtual public Masca {
protected:
    std::string culoare;
    int nr_pliuri;
public:
    Chirurgical() = default;
    Chirurgical(const Chirurgical&) = default;
    virtual ~Chirurgical() = default;
    Chirurgical& operator = (const Chirurgical&) = default;

    friend std::ostream& operator << (std::ostream&, Chirurgical&);
    friend std::istream& operator >> (std::istream&, Chirurgical&);
    virtual std::ostream& afisare(std::ostream&) const override;
    virtual std::istream& citire(std::istream&) override;
};
std::ostream& Chirurgical::afisare(std::ostream& out) const {
    Masca::afisare(out);
    out << "Culoare: " << this->culoare << "\n";
    out << "Nr de pliuri: " << this->nr_pliuri << "\n";
    return out;
}
std::ostream& operator << (std::ostream& out, Chirurgical& obj) {
    return obj.afisare(out);
}
std::istream& Chirurgical::citire(std::istream& in) {
    Masca::citire(in);
    std::cout << "Alege culoarea: "; in >> culoare;
    std::cout << "Alege nr de pliuri: "; in >> nr_pliuri;
    return in;
}
std::istream& operator >> (std::istream& in, Chirurgical& obj) {
    return obj.citire(in);
}


// policarbonat
class Policarbonat : virtual public Masca {
protected:
    std::string tip_prindere;
public:
    Policarbonat() = default;
    Policarbonat(const Policarbonat&) = default;
    virtual ~Policarbonat() = default;
    Policarbonat& operator = (const Policarbonat&) = default;

    friend std::ostream& operator << (std::ostream&, Policarbonat&);
    friend std::istream& operator >> (std::istream&, Policarbonat&);
    virtual std::ostream& afisare(std::ostream&) const override;
    virtual std::istream& citire(std::istream&) override;
};
std::ostream& Policarbonat::afisare(std::ostream& out) const {
    Masca::afisare(out);
    out << "Tip prindere: " << this->tip_prindere << "\n";
    return out;
}
std::ostream& operator << (std::ostream& out, Policarbonat& obj) {
    return obj.afisare(out);
}
std::istream& Policarbonat::citire(std::istream& in) {
    Masca::citire(in);
    std::cout << "Toate mastile de tipul acesta au tipul de prindere ffp0!!\n";
    tip_prindere = "ffp 0";
    return in;
}
std::istream& operator >> (std::istream& in, Policarbonat& obj) {
    return obj.citire(in);
}





// dezinft
class Dezinfectant :public InOut {
protected:
    int nr_specii;
    std::vector<std::string> ingrediente;
    std::vector<std::string> tipuri_suprafete;
public:
    Dezinfectant() = default;
    Dezinfectant(const Dezinfectant&) = default;
    virtual ~Dezinfectant() = default;
    Dezinfectant& operator = (const Dezinfectant&) = default;

    friend std::ostream& operator << (std::ostream&, Dezinfectant&);
    friend std::istream& operator >> (std::istream&, Dezinfectant&);
    virtual std::ostream& afisare(std::ostream&) const override;
    virtual std::istream& citire(std::istream&) override;

    virtual double CalculeazaEficienta() { return 0; }; // eficienta 0 pt un dezinfectant fara tip
};
std::ostream& Dezinfectant::afisare(std::ostream& out) const {
    out << "Numarul de specii pe care le ucide dezinfectantul: " << this->nr_specii << "\n";
    out << "Ingrediente:\n";
    for (auto item : ingrediente)
        out << " - " << item << "\n";
    out << "Tipuri de suprafete asupra carora poate fi aplicat:\n";
    for (auto item : tipuri_suprafete)
        out << " - " << item << "\n";
    return out;
}
std::ostream& operator << (std::ostream& out, Dezinfectant& obj) {
    return obj.afisare(out);
}
std::istream& Dezinfectant::citire(std::istream& in) {
    int nr_ingrediente, nr_suprafete;
    std::cout << "Aleget cate specii ucide dezinfectantul: "; in >> nr_specii;
    std::cout << "Alege cate ingrediente are: (va trebui introdus numele fiecaruia) "; in >> nr_ingrediente;
    for (int i = 0; i < nr_ingrediente; i++) {
        std::string cr_ingredient;
        std::cout << "Introdu numele ingredientului nr " << (i + 1) << ": ";
        in >> cr_ingredient;
        ingrediente.push_back(cr_ingredient);
    }
    std::cout << "Alege cate suprafete afecteaza: (va trebui introdus numele fiecareia) "; in >> nr_suprafete;
    for (int i = 0; i < nr_suprafete; i++) {
        std::string cr_supr;
        std::cout << "Introdu numele suprafetei cu nr " << (i + 1) << ": ";
        in >> cr_supr;
        tipuri_suprafete.push_back(cr_supr);
    }
    return in;
}
std::istream& operator >> (std::istream& in, Dezinfectant& obj) {
    return obj.citire(in);
}


class Bacterial : virtual public Dezinfectant {
public:
    Bacterial() = default;
    Bacterial(const Bacterial&) = default;
    virtual ~Bacterial() = default;

    double CalculeazaEficienta() override;

    friend std::ostream& operator << (std::ostream&, Bacterial&);
    friend std::istream& operator >> (std::istream&, Bacterial&);
    virtual std::ostream& afisare(std::ostream&) const override;
    virtual std::istream& citire(std::istream&) override;
};
double Bacterial::CalculeazaEficienta() {
    return (this->nr_specii) / (pow(10, 9));
}
std::ostream& Bacterial::afisare(std::ostream& out) const {
    Dezinfectant::afisare(out);
    return out;
}
std::ostream& operator << (std::ostream& out, Bacterial& obj) {
    return obj.afisare(out);
}
std::istream& Bacterial::citire(std::istream& is) {
    Dezinfectant::citire(is);
    return is;
}
std::istream& operator >> (std::istream& is, Bacterial& obj) {
    return obj.citire(is);
}



class Fungic : virtual public Dezinfectant {
public:
    Fungic() = default;
    Fungic(const Fungic&) = default;
    virtual ~Fungic() = default;

    double CalculeazaEficienta() override;

    friend std::ostream& operator << (std::ostream&, Fungic&);
    friend std::istream& operator >> (std::istream&, Fungic&);
    virtual std::ostream& afisare(std::ostream&) const override;
    virtual std::istream& citire(std::istream&) override;
};
double Fungic::CalculeazaEficienta() {
    return (this->nr_specii) / 1.5 * (pow(10, 6));
}
std::ostream& Fungic::afisare(std::ostream& out) const {
    Dezinfectant::afisare(out);
    return out;
}
std::ostream& operator << (std::ostream& out, Fungic& obj) {
    return obj.afisare(out);
}
std::istream& Fungic::citire(std::istream& is) {
    Dezinfectant::citire(is);
    return is;
}
std::istream& operator >> (std::istream& is, Fungic& obj) {
    return obj.citire(is);
}


class Virusuri : virtual public Dezinfectant {
public:
    Virusuri() = default;
    Virusuri(const Virusuri&) = default;
    virtual ~Virusuri() = default;

    double CalculeazaEficienta() override;

    friend std::ostream& operator << (std::ostream&, Virusuri&);
    friend std::istream& operator >> (std::istream&, Virusuri&);
    virtual std::ostream& afisare(std::ostream&) const override;
    virtual std::istream& citire(std::istream&) override;
};
double Virusuri::CalculeazaEficienta() {
    return (this->nr_specii) / (pow(10, 8));
}
std::ostream& Virusuri::afisare(std::ostream& out) const {
    Dezinfectant::afisare(out);
    return out;
}
std::ostream& operator << (std::ostream& out, Virusuri& obj) {
    return obj.afisare(out);
}
std::istream& Virusuri::citire(std::istream& is) {
    Dezinfectant::citire(is);
    return is;
}
std::istream& operator >> (std::istream& is, Virusuri& obj) {
    return obj.citire(is);
}

class ToateTipurile : public Bacterial, public Fungic, public Virusuri {
public:
    ToateTipurile() = default;
    ToateTipurile(const ToateTipurile&) = default;
    virtual ~ToateTipurile() = default;

    double CalculeazaEficienta() override;

    friend std::ostream& operator << (std::ostream&, ToateTipurile&);
    friend std::istream& operator >> (std::istream&, ToateTipurile&);
    virtual std::ostream& afisare(std::ostream&) const override;
    virtual std::istream& citire(std::istream&) override;
};
double ToateTipurile::CalculeazaEficienta() {
    return ((this->nr_specii) / (pow(10, 8)) + this->nr_specii / pow(10, 9) + this->nr_specii / 1.5 * pow(10, 6));
}
std::ostream& ToateTipurile::afisare(std::ostream& out) const {
    Dezinfectant::afisare(out);
    return out;
}
std::ostream& operator << (std::ostream& out, ToateTipurile& obj) {
    return obj.afisare(out);
}
std::istream& ToateTipurile::citire(std::istream& is) {
    Dezinfectant::citire(is);
    return is;
}
std::istream& operator >> (std::istream& is, ToateTipurile& obj) {
    return obj.citire(is);
}

class Achizitie: public InOut {
protected:
    std::string data;
    std::string nume;
    std::vector<Dezinfectant*> dez_achizitionati;
    std::vector<Masca*> masti_achizitionate;
public:
    Achizitie() = default;
    Achizitie(const Achizitie&) = default;
    virtual ~Achizitie() = default;

    friend std::ostream& operator << (std::ostream&, Achizitie&);
    friend std::istream& operator >> (std::istream&, Achizitie&);
    virtual std::ostream& afisare(std::ostream&) const override;
    virtual std::istream& citire(std::istream&) override;
};
std::ostream& Achizitie::afisare(std::ostream& out) const {
    out << "Data: " << this->data << "\n";
    out << "Nume: " << this->nume << "\n";
    out << "Dezinfectant achiziotionat: " <<"\n";
    for (auto item:dez_achizitionati)
        out << *item << "\n";
    out << "Masti achizitionate: " << "\n";
    for (auto item:masti_achizitionate)
        out << *item << "\n";
    return out;
}
std::ostream& operator << (std::ostream& out, Achizitie& obj) {
    return obj.afisare(out);
}
std::istream& Achizitie::citire(std::istream& in) {
    int n;
    std::cout << "Introdu numele clientului: "; in >> nume;
    std::cout << "Introdu data tranzactiei: "; in >> data;
    std::cout << "Introdu numarul de dezinfectant cumparat"; in >> n;
    for (int i = 0; i < n; i++) {
        std::cout << "Alege tipul dezinfectantului: \n";
        std::cout << "1. \n";
        std::cout << "2. \n";
        std::cout << "3. \n";
        std::cout << "4. \n";


        int option;
        std::cin >> option;
        switch (option) {
            case 1: {
                Dezinfectant* nou = new Bacterial();
                std::cin >> *nou;
                dez_achizitionati.push_back(nou);
                break;;
            }
            case 2: {
                Dezinfectant* nou = new Fungic();
                std::cin >> *nou;
                dez_achizitionati.push_back(nou);
                break;;
            }
            case 3: {
                Dezinfectant* nou = new Virusuri();
                std::cin >> *nou;
                dez_achizitionati.push_back(nou);
                break;;
            }
            case 4: {
                Dezinfectant* nou = new ToateTipurile();
                std::cin >> *nou;
                dez_achizitionati.push_back(nou);
                break;;
            }
        }
    }
    std::cout << "Introdu numarul de masti cumparate"; in >> n;
    for (int i = 0; i < n; i++) {
        std::cout << "Alege tipul mastii: \n";
        std::cout << "1. \n";
        std::cout << "2. \n";

        int option;
        std::cin >> option;
        switch (option) {
            case 1: {
                Masca* nou = new Chirurgical();
                std::cin >> *nou;
                masti_achizitionate.push_back(nou);
                break;;
            }
            case 2: {
                Masca* nou = new Policarbonat();
                std::cin >> *nou;
                masti_achizitionate.push_back(nou);
                break;;
            }
        }
    }
    return in;
}
std::istream& operator >> (std::istream& in, Achizitie& obj) {
    return obj.citire(in);
}



class Menu {
private:
    Menu() = default;
    Menu(const Menu&) = delete;
    virtual ~Menu() = delete;
    static Menu* menu_ptr;
    //static std::vector<>
    static bool ongoing;
    std::vector<Dezinfectant*> stoc_dez;
    std::vector<Masca*> stoc_masti;
    std::vector<Achizitie> achizitii;

public:
    static Menu* GetInstance() {
        if (menu_ptr == nullptr)
            menu_ptr = new Menu();
        return menu_ptr;
    }
    static bool IsOngoing() { return ongoing; }
    static void TurnOff() { ongoing = false; }

    void RunMenu();
    void ShowMenu() {
        std::cout << "Alege o optiune:\n";
        std::cout << "1. Adauga un nou dezinfectatnt in stoc\n";
        std::cout << "2. Adauga masca\n";
        std::cout << "3. Adauga achizitie\n";
        std::cout << "4. Afiseza dezinfectantul cel mai eficient\n";
        std::cout << "5. Calculeaza venit intr-o anumita luna\n";
        std::cout << "6. Modifica reteta unui dezinfectant (ingrediente --> specii ucise --> suprafete aplicabile)\n";
        std::cout << "7. Calculeaza venitul obtinut din mastile chirurgicale cu model\n";
        std::cout << "8. Afis. cel mai fidel client\n";
        std::cout << "9. Afis ziua cu cele mai slabe venituri\n";
        std::cout << "10. Calculeaza TVA-ul (19% din venit) pt un anumit an\n";
        std::cout << "11. Inchide aplicatia\n";
    }
    void SwitchCaseMenu(int optiune) {

        switch (optiune) {
        case 1: {
            AdaugaDezinfectant();
            break;
        }
        case 2: {
            AdaugaMasca();
            break;
        }
        case 3: {
            AdaugaAchizitie();
            break;
        }
        case 4: {
            AfiseazaDezEficient();
            break;
        }
        case 5: {
            break;
        }
        case 6: {
            break;
        }
        case 7: {
            break;
        }
        case 8: {
            break;
        }
        case 9: {
            break;
        }
        case 10: {
            break;
        }
        case 11: {
            TurnOff();
            break;
        }
        }
    }

    void AdaugaDezinfectant() {
        std::cout << "Alege tipul dezinfectantului: \n";
        std::cout << "1. bacterial\n";
        std::cout << "2. fungic\n";
        std::cout << "3. virtusuir\n";
        std::cout << "4. toate tipurile\n";


        int option;
        std::cin >> option;
        switch (option) {
            case 1: {
                Dezinfectant* nou = new Bacterial();
                std::cin >> *nou;
                stoc_dez.push_back(nou);
                break;;
            }
            case 2: {
                Dezinfectant* nou = new Fungic();
                std::cin >> *nou;
                stoc_dez.push_back(nou);
                break;;
            }
            case 3: {
                Dezinfectant* nou = new Virusuri();
                std::cin >> *nou;
                stoc_dez.push_back(nou);
                break;;
            }
            case 4: {
                Dezinfectant* nou = new ToateTipurile();
                std::cin >> *nou;
                stoc_dez.push_back(nou);
                break;;
            }
        }
    }
    void AdaugaMasca() {
        std::cout << "Alege tipul mastii: \n";
        std::cout << "1. chirurgicala\n";
        std::cout << "2. policarbonata\n";

        int option;
        std::cin >> option;
        switch (option) {
            case 1: {
                Masca* nou = new Chirurgical();
                std::cin >> *nou;
                stoc_masti.push_back(nou);
                break;;
            }
            case 2: {
                Masca* nou = new Policarbonat();
                std::cin >> *nou;
                stoc_masti.push_back(nou);
                break;;
            }
        }
    }
    void AdaugaAchizitie() {
        Achizitie noua;
        std::cin >> noua;
        achizitii.push_back(noua);
        std::cout << "Achizitie adaugata cu succes!\n";
    }
    void AfiseazaDezEficient() {
        double maxx = 0;
        int pos = -1;
        for (int i = 0; i < stoc_dez.size(); i++) {
            double ef = stoc_dez[i]->CalculeazaEficienta();
            if (ef > maxx) {
                maxx = ef;
                pos = i;
            }
        }
        std::cout << stoc_dez[pos];
    }
};

void Menu::RunMenu() {
    int optiune;
    ShowMenu();
    try {
        std::cout << "Optiunea ta: ";
        std::cin >> optiune;
        system("cls");
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw std::runtime_error("Eroare, tip de date invalid\n");
        }
        if (optiune < 1 || optiune > 11)
            throw std::out_of_range("Eroare, valoarea trebuie sa fie intre 1 si 11\n");
        SwitchCaseMenu(optiune);
    }
    catch (const std::exception& e) {
        std::cerr << e.what();
    }
}

Menu* Menu::menu_ptr = nullptr;
bool Menu::ongoing = true;

int main() {
    Menu* sistem = Menu::GetInstance();
    do {
        sistem->RunMenu();
    } while (Menu::IsOngoing());
    return 0;
}






