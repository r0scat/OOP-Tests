
#include <vector>
#include <iostream>
#include <string>

class InOut {
public:
	friend std::ostream& operator << (std::ostream&, InOut&);
	friend std::istream& operator >> (std::istream&, InOut&);
	virtual std::ostream& afisare(std::ostream&) const = 0;
	virtual std::istream& citire(std::istream&) = 0;
};

class Drum {
protected:
	std::string nume;
	float lungime;
	int tronsoane;
	std::vector<int> frecvente; // pastreaza tronsoanele drumului care au fost asociate cu un contract
public:
	Drum() = default;
	Drum(const Drum&) = default;
	virtual ~Drum() = default;
	Drum& operator = (Drum&) = default;

	std::vector<int> GetFrecvente() { return this->frecvente; }
	void AdaugaFrecv(int nr) { frecvente.push_back(nr); }
	float GetLungime() { return this->lungime; }
	std::string GetNume() { return this->nume; }

	friend std::ostream& operator << (std::ostream&, Drum&);
	friend std::istream& operator >> (std::istream&, Drum&);
	virtual std::ostream& afisare(std::ostream&) const;
	virtual std::istream& citire(std::istream&);
	
	virtual bool IsAutostrada() { return false; }
	virtual double CalculeazaCost() {
		double tr_lng = lungime / tronsoane;
		return 3000 * tr_lng;
	}
};
std::ostream& Drum::afisare(std::ostream& out) const {
	out << "Nume: " << this->nume << "\n";
	out << "Lungime: " << this->lungime<< "\n";
	out << "Nr de tronsoane: " << this->tronsoane << "\n";
	return out;
}
std::ostream& operator << (std::ostream& out, Drum& obj) {
	return obj.afisare(out);
}
std::istream& Drum::citire(std::istream& in) {
	std::cout << "Introdu numele drumului: "; in >> nume;
	std::cout << "Introdu lungimea drumului :"; in >> lungime;
	std::cout << "Introdu nr de tronsoane ale drumului: "; in >> tronsoane;
	return in;
}
std::istream& operator >> (std::istream&in, Drum&obj) {
	return obj.citire(in);
}

// national
class National: virtual public Drum {
protected:
	int nr_judete;
public:
	National() = default;
	National(const National&) = default;
	virtual ~National() = default;
	National& operator = (National&) = default;

	friend std::ostream& operator << (std::ostream&, National&);
	friend std::istream& operator >> (std::istream&, National&);
	virtual std::ostream& afisare(std::ostream&) const;
	virtual std::istream& citire(std::istream&);

	bool IsAutostrada() override{ return false; }
};
std::ostream& National::afisare(std::ostream& out) const {
	Drum::afisare(out);
	out << "Nr judete prin care trece: " << this->nr_judete << "\n";
	return out;
}
std::ostream& operator << (std::ostream& out, National& obj) {
	return obj.afisare(out);
}
std::istream& National::citire(std::istream& in) {
	Drum::citire(in);
	std::cout << "Introdu nr de judete prin care trece: "; in >> this->nr_judete;
	return in;
}
std::istream& operator >> (std::istream& in, National& obj) {
	return obj.citire(in);
}

//european
class European : virtual public Drum {
protected:
	int nr_tari;
public:
	European() = default;
	European(const European&) = default;
	virtual ~European() = default;
	European& operator = (European&) = default;

	friend std::ostream& operator << (std::ostream&, European&);
	friend std::istream& operator >> (std::istream&, European&);
	virtual std::ostream& afisare(std::ostream&) const;
	virtual std::istream& citire(std::istream&);

	bool IsAutostrada() override{ return false; }
	double CalculeazaCost() override {
		return Drum::CalculeazaCost() + 500 * nr_tari;
	}
};
std::ostream& European::afisare(std::ostream& out) const {
	Drum::afisare(out);
	out << "Nr tari prin care trece: " << this->nr_tari << "\n";
	return out;
}
std::ostream& operator << (std::ostream& out, European& obj) {
	return obj.afisare(out);
}
std::istream& European::citire(std::istream& in) {
	Drum::citire(in);
	std::cout << "Introdu nr de tari prin care trece: "; in >> this->nr_tari;
	return in;
}
std::istream& operator >> (std::istream& in, European& obj) {
	return obj.citire(in);
}

// autostrada
class Autostrada : virtual public Drum {
protected:
	int nr_benzi;
public:
	Autostrada() = default;
	Autostrada(const Autostrada&) = default;
	virtual ~Autostrada() = default;
	Autostrada& operator = (Autostrada&) = default;

	friend std::ostream& operator << (std::ostream&, Autostrada&);
	friend std::istream& operator >> (std::istream&, Autostrada&);
	virtual std::ostream& afisare(std::ostream&) const;
	virtual std::istream& citire(std::istream&);

	bool IsAutostrada() override { return true; }
	double CalculeazaCost() override {
		double tr_lng = lungime / tronsoane;
		return 2500 * nr_benzi * tr_lng;
	}
};
std::ostream& Autostrada::afisare(std::ostream& out) const {
	Drum::afisare(out);
	out << "Nr de benzi: " << this->nr_benzi << "\n";
	return out;
}
std::ostream& operator << (std::ostream& out, Autostrada& obj) {
	return obj.afisare(out);
}
std::istream& Autostrada::citire(std::istream& in) {
	Drum::citire(in);
	std::cout << "Introdu nr de benzi: "; in >> this->nr_benzi;
	return in;
}
std::istream& operator >> (std::istream& in, Autostrada& obj) {
	return obj.citire(in);
}

// autostrada + drumuri europene
class Ambele : public Autostrada, public European{

public:
	Ambele() = default;
	Ambele(const Ambele&) = default;
	virtual ~Ambele() = default;
	Ambele& operator = (Ambele&) = default;

	friend std::ostream& operator << (std::ostream&, Ambele&);
	friend std::istream& operator >> (std::istream&, Ambele&);
	virtual std::ostream& afisare(std::ostream&) const;
	virtual std::istream& citire(std::istream&);

	bool IsAutostrada() override{ return false; }
	double CalculeazaCost() override {
		return Autostrada::CalculeazaCost() + 500 * nr_tari;
	}
};
std::ostream& Ambele::afisare(std::ostream& out) const {
	European::afisare(out);
	out << "Nr de benzi: " << this->nr_benzi << "\n";
	return out;
}
std::ostream& operator << (std::ostream& out, Ambele& obj) {
	return obj.afisare(out);
}
std::istream& Ambele::citire(std::istream& in) {
	European::citire(in);
	std::cout << "Introdu nr de benzi: "; in >> this->nr_benzi;
	return in;
}
std::istream& operator >> (std::istream& in, Ambele& obj) {
	return obj.citire(in);
}



// contracte
class Contract : public InOut {
	static int contor;
	int id;
	std::string nume;
	std::string CIF;
	Drum* drum_asociat;
	int tronson_asociat;
	double cost;
public:
	Contract() :id(++contor) {}
	Contract(const Contract&) = default;
	Contract& operator = (const Contract&) = default;
	virtual ~Contract() = default;

	std::string GetCIF() const { return this->CIF; }
	double GetCost() const { return this->cost; }
	Drum* GetDrum() const { return this->drum_asociat; }

	friend std::ostream& operator << (std::ostream&, Contract&);
	friend std::istream& operator >> (std::istream&, Contract&);
	virtual std::ostream& afisare(std::ostream&) const;
	virtual std::istream& citire(std::istream&);

	static bool VerificaAsociere(Drum* drum, int tronson) {

		for (int i = 0; i < drum->GetFrecvente().size(); i++) {
			if (drum->GetFrecvente()[i] == tronson)
				return false;
		}
		drum->AdaugaFrecv(tronson);
		return true;
	}
};
std::ostream& Contract::afisare(std::ostream& out) const {

	out << "Id Contract: " << this->id << "\n";
	out << "Nume: " << this->nume << "\n";
	out << "CIF: " << this->CIF << "\n";
	out << "Drum asociat: " << this->drum_asociat << "\n";
	out << "Tronson asociat: " << this->drum_asociat << "\n";
	out << "Cost: " << this->cost << "\n";
	return out;
}
std::ostream& operator << (std::ostream& out, Contract& obj) {
	return obj.afisare(out);
}
std::istream& Contract::citire(std::istream& in) {
	std::cout << "Alege nume: "; in >> this->nume;
	std::cout << "Alege CIF: "; in >> this->CIF;
	std::cout << "Alege drum asociat: "; in >> *this->drum_asociat;
	do
	{
		std::cout << "Alege un tronson asociat: "; in >> this->tronson_asociat;
	} while (VerificaAsociere(this->drum_asociat, this->tronson_asociat) == false);
	std::cout << "Costul se va calcula in functie de tronsoanele drumului si de tipul drumului ales!\n";
	this->cost = this->drum_asociat->CalculeazaCost();
	return in;
}
std::istream& operator >> (std::istream& in, Contract& obj) {
	return obj.citire(in);
}




// menu singleton
class Menu {
private:
	static Menu* menu_ptr;
	Menu() = default;
	static bool ongoing;
	std::vector<Drum*> drumuri;
	std::vector<Contract> contracte;
public:
	Menu(const Menu&) = delete;
	virtual ~Menu() = delete;
	static Menu* GetInstance() {
		if (menu_ptr == nullptr)
			menu_ptr = new Menu();
		return menu_ptr;
	}
	static void TurnOff() {
		ongoing = false;
	}
	static bool IsOngoing() {
		return ongoing;
	}

	void ShowMenu();
	void SwitchCaseMenu(int op);
	void RunMenu();

	void AdaugaUnDrum();
	void AfiseazaDrumuri();
	float LungimeTotala();
	float LungimeAutostrazi();
	void AdaugaContract();
	void StergeContractCIF();
	double CalcCostTotal(Drum* ales);
	Drum* GasesteDupaNume(std::string nume);
};

void Menu::AdaugaUnDrum() {
	std::cout << "Ce fel de drum vrei sa adaugi?\n";
	std::cout << "1. national\n";
	std::cout << "2. european\n";
	std::cout << "3. autostrada\n";
	std::cout << "4. european+autostrada\n";

	int opt;
	std::cin >> opt;
	switch (opt)
	{
	case 1: {
		Drum* nou = new National();
		std::cin >> *nou;
		drumuri.push_back(nou);
		break;
	}
	case 2: {
		Drum* nou = new European();
		std::cin >> *nou;
		drumuri.push_back(nou);
		break;
	}
	case 3: {

		Drum* nou = new Autostrada();
		std::cin >> *nou;
		drumuri.push_back(nou);
		break;
	}
	case 4: {

		Drum* nou = new Ambele();
		std::cin >> *nou;
		drumuri.push_back(nou);
		break;
	}
	default:
		break;
	}
}
void Menu::AfiseazaDrumuri() {
	std::cout << "Toate drumurile sunt:\n";
	for (auto item : drumuri)
		std::cout << *item << "\n";
}
float Menu::LungimeTotala() {
	float suma = 0;
	for (auto item : drumuri)
		suma += item->GetLungime();
	return suma;
}
float Menu::LungimeAutostrazi() {
	float suma = 0;
	for (auto item : drumuri)
	if(item->IsAutostrada())
		suma += item->GetLungime();
	return suma;
}
void Menu::AdaugaContract() {
	Contract nou;
	std::cin >> nou;
	contracte.push_back(nou);
}
void Menu::StergeContractCIF() {
	std::cout << "Introdu CIF-ul al caror contracte vrei sa le stergi:\n";
	std::string cif;
	std::cin >> cif;
	for (int i = 0; i < contracte.size(); i++)
		if (contracte[i].GetCIF() == cif)
			contracte.erase(contracte.begin() + i - 1);
}
double Menu::CalcCostTotal(Drum* ales) {
	double suma = 0;
	for (auto item : contracte)
		if (item.GetDrum() == ales)
			suma += item.GetCost();
	return suma;
}
Drum* Menu::GasesteDupaNume(std::string nume) {
	for (auto item : drumuri)
		if (item->GetNume() == nume)
			return item;
	return nullptr;
}

void Menu::ShowMenu() {
	std::cout << "1. Adauga un drum\n";
	std::cout << "2. Afiseaza toate drumurile\n";
	std::cout << "3. Calculeaza lungimea totala a tuturor tipurilor de drumuri\n";
	std::cout << "4. Afis lungimea totala doar a drumurilor de tip autostrada\n";
	std::cout << "5. Sterge contractele de la o anumita firma (de la un anumit CIF)\n";
	std::cout << "6. Calc. costul total al contractelor asociate cu un drum identificat dupa denumire\n";
	std::cout << "7. Adauga un contract\n";
	std::cout << "7. Exit\n";
}
void Menu::SwitchCaseMenu(int optiune) {
	switch (optiune)
	{
	case 1:
	{
		AdaugaUnDrum();
		break;
	}
	case 2:
	{
		AfiseazaDrumuri();
		break;
	}
	case 3:
	{
		std::cout << "Lungimea totala a drumurilor este: " << LungimeTotala() << "\n";
		break;
	}
	case 4:
	{
		std::cout << "Lungmea autostrazilor este: " << LungimeAutostrazi() << "\n";
		break;
	}
	case 5:
	{
		StergeContractCIF();
		break;
	}
	case 6:
	{
		std::cout << "Alege un drum pt care vrei sa calculezi suma: \n";
		std::string nume;
		std::cin >> nume;
		Drum* drum = GasesteDupaNume(nume);
		std::cout << "Costul total cerut este: " << CalcCostTotal(drum);
		break;
	}
	case 7:
	{
		AdaugaContract();
		break;
	}
	case 8:
	{
		TurnOff();
		break;
	}
	}
}
void Menu::RunMenu(){
	int option;
	ShowMenu();
	try {
		std::cout << "optiunea ta: ";
		std::cin >> option;
		system("cls");
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			throw std::string("Eroare, tip de date invalid\n");
		}
		if (option < 1 || option > 8)
			throw std::string("Eroare, introdu o optiune existenta\n");
		SwitchCaseMenu(option);
	}
	catch (std::string& e) {
		std::cout << e;
	}
}


int Contract::contor = 0;
bool Menu::ongoing = true;
Menu* Menu::menu_ptr = nullptr;

int main()
{
	Menu* sistem = Menu::GetInstance();
	do {
		sistem->RunMenu();
	} while (Menu::IsOngoing());
	return 0;
}
