#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class InOut {
public:
	friend istream& operator >> (istream&, InOut&);
	friend ostream& operator << (ostream&, InOut&);
	virtual istream& citire(istream&) = 0;
	virtual ostream& afisare(ostream&) const = 0;

	virtual ~InOut() = default;
};



class Proba : virtual public InOut {
public:
	Proba() = default;
	Proba(const Proba&) = default;
	Proba& operator = (const Proba&) = default;
	virtual ~Proba() = default;
	virtual Proba* clone() const = 0;

	virtual void SetTip(string) = 0;
	virtual float CalculeazaValoare() = 0;

	friend istream& operator >> (istream&, Proba&);
	friend ostream& operator << (ostream&, Proba&);
	virtual istream& citire(istream&) = 0;
	virtual ostream& afisare(ostream&) const = 0;
};
istream& operator >> (istream& in, Proba& obj) {
	return obj.citire(in);
}
ostream& operator << (ostream & out, Proba & obj)  {
	return obj.afisare(out);
}


class Sprint : virtual public Proba {
protected:
	int timp_s;
public:
	Sprint() = default;
	Sprint(const Sprint&) = default;
	Sprint& operator = (const Sprint&) = default;
	virtual ~Sprint() = default;
	Proba* clone() const override {
		return new Sprint(*this);
	}

	void SetTip(string) override {}
	float CalculeazaValoare() override;

	friend istream& operator >> (istream&, Sprint&);
	friend ostream& operator << (ostream&, Sprint&);
	virtual istream& citire(istream&) override;
	virtual ostream& afisare(ostream&) const override;
};
istream& Sprint::citire(istream& in){
	cout << "Timpul mas in sec: "; in >> timp_s;
	return in;
}
istream& operator >> (istream& in, Sprint&obj) {
	return obj.citire(in);
}
ostream& Sprint::afisare(ostream& out) const {
	out << "Timpul mas in sec: " << timp_s << '\n';
	return out;
}
ostream& operator << (ostream& out, Sprint& obj) {
	return obj.afisare(out);
}
float Sprint::CalculeazaValoare() {
	if (timp_s < 10)
		return 10;
	return (90 / timp_s);
}


class Cros : virtual public Proba {
protected:
	int timp_min;
public:
	Cros() = default;
	Cros(const Cros&) = default;
	Cros& operator = (const Cros&) = default;
	virtual ~Cros() = default;
	Proba* clone() const override {
		return new Cros(*this);
	}

	void SetTip(string) override {}
	float CalculeazaValoare() override;

	friend istream& operator >> (istream&, Cros&);
	friend ostream& operator << (ostream&, Cros&);
	virtual istream& citire(istream&) override;
	virtual ostream& afisare(ostream&) const override;
};
istream& Cros::citire(istream& in) {
	cout << "Timpul mas in min: "; in >> timp_min;
	return in;
}
istream& operator >> (istream& in, Cros& obj) {
	return obj.citire(in);
}
ostream& Cros::afisare(ostream& out) const {
	out << "Timpul mas in min: " << this->timp_min << '\n';
	return out;
}
ostream& operator << (ostream& out, Cros& obj) {
	return obj.afisare(out);
}
float Cros::CalculeazaValoare() {
	if (timp_min < 30)
		return 10;
	return (120 / timp_min);
}



class Maraton : virtual public Proba {
protected:
	string tip; // semi maraton sau maraton
	int distanta_max;
public:
	Maraton() = default;
	Maraton(const Maraton&) = default;
	Maraton& operator = (const Maraton&) = default;
	virtual ~Maraton() = default;
	Proba* clone() const override {
		return new Maraton(*this);
	}
	float CalculeazaValoare() override;

	void SetTip(string tip) override { this->tip = tip; }

	friend istream& operator >> (istream&, Maraton&);
	friend ostream& operator << (ostream&, Maraton&);
	virtual istream& citire(istream&) override;
	virtual ostream& afisare(ostream&) const override;
};
istream& Maraton::citire(istream& in) {
	cout << "Distanta max: "; in >> distanta_max;
	return in;
}
istream& operator >> (istream& in, Maraton& obj) {
	return obj.citire(in);
}
ostream& Maraton::afisare(ostream& out) const {
	out << "Distanta max: " << this->distanta_max<< '\n';
	return out;
}
ostream& operator << (ostream& out, Maraton& obj) {
	return obj.afisare(out);
}
float Maraton::CalculeazaValoare() {
	if (distanta_max > 50)
		return 10;
	return (distanta_max/5);
}




class Candidat : public InOut {
protected:
	string nume;
	string prenume;
	string data_n;
	string tip_proba;
	Proba* proba_aleasa;
public:
	Candidat() {
		std::cout << "La ce fel de proba va participa acest candidat?\n";
		std::cout << "1. sprint\n";
		std::cout << "2. cros\n";
		std::cout << "3. maraton\n";
		std::cout << "4. semi-maraton\n";

		int opt;
		std::cin >> opt;
		switch (opt)
		{
		case 1:
		{
			Proba* proba_aleasa = new Sprint();
			cin >> *proba_aleasa;
			break;
		}
		case 2:
		{
			Proba* proba_aleasa = new Cros();
			cin >> *proba_aleasa;
			break;
		}
		case 3:
		{
			Proba* proba_aleasa = new Maraton();
			cin >> *proba_aleasa;
			proba_aleasa->SetTip(string("maraton"));
			break;
		}
		case 4:
		{

			Proba* proba_aleasa = new Maraton();
			cin >> *proba_aleasa;
			proba_aleasa->SetTip(string("semi-maraton"));
			break;
		}
		}
	}
	Candidat(const Candidat&) = default;
	Candidat& operator = (const Candidat&) = default;
	virtual ~Candidat() {
		delete proba_aleasa;
	}

	Proba* GetProba() { return proba_aleasa; }
	

	friend istream& operator >> (istream&, Candidat&);
	friend ostream& operator << (ostream&, Candidat&);
	virtual istream& citire(istream&) override;
	virtual ostream& afisare(ostream&) const override;
};
istream& Candidat::citire(istream& in) {
	cout << "nume: "; in >> nume;
	cout << "prenume: "; in >> prenume;
	cout << "data nasterii: "; in >> data_n;
	//cout << "tip proba: "; in >> tip_proba;
	return in;
}
istream& operator >> (istream& in, Candidat& obj) {
	return obj.citire(in);
}
ostream& Candidat::afisare(ostream& out) const {
	out << "nume: " << this->nume<< '\n';
	out << "prenume: " << this->prenume << '\n';
	out << "data nasterii: " << this->data_n << '\n';
	out << "proba aleasa: " << this->tip_proba << '\n';
	return out;
}
ostream& operator << (ostream& out, Candidat& obj) {
	return obj.afisare(out);
}


class Singleton {
private:
	static Singleton* ptr;
	Singleton() = default;
	Singleton(const Singleton&) = delete;
	Singleton& operator = (const Singleton&) = delete;
	static vector<Candidat> inscrieri;
	static bool ongoing;
public:
	~Singleton() { delete ptr; }
	static Singleton* GetInstance() {
		if (ptr == nullptr)
			ptr = new Singleton();
		return ptr;
	}

	void ShowMenu();
	void SwitchCase(int opt);
	void RunMenu();
	void TurnOff() { ongoing = false; }
	static bool IsOngoing() { return ongoing; }

	void AdaugaCandidat();
	void InchideAplicatia();
	void Ordonare();
	bool VerifParola(string parola) {
		if (parola == "1234567890")
			return true;
		return false;
	}

	template <typename Comparator> void ordonare(Comparator comp) {
		sort(inscrieri.begin(), inscrieri.end(), comp);
	}
};
void Singleton::AdaugaCandidat() {
	Candidat nou;
	cin >> nou;
	inscrieri.push_back(nou);
}
void Singleton::Ordonare() {
	ordonare([](Candidat a, Candidat b) {
		return a.GetProba()->CalculeazaValoare() < b.GetProba()->CalculeazaValoare();
	});
}
void Singleton::InchideAplicatia() {
	Ordonare();

	int n;
	if (inscrieri.size() < 500)
		n = inscrieri.size();
	else
		n = 500;

	for (int i = 0; i < n; i++)
		cout << inscrieri[i];
	TurnOff();
}
void Singleton::ShowMenu() {
	std::cout << "1. inscrie candidat\n";
	std::cout << "2. incheie inscrieri (tb introdusa o parola de admit)\n";
}
void Singleton::SwitchCase(int opt) {
	switch (opt)
	{
	case 1:
	{
		AdaugaCandidat();
		break;
	}
	case 2:
	{
		string parola;
		cout << "Introdu parola de admin\n";
		cin >> parola;
		if (VerifParola(parola)) {
			InchideAplicatia();
		}
		else
			cout << "Parola incorecta\n";
		break;
	}
	}
}
void Singleton::RunMenu() {
	int opt;
	ShowMenu();
	try {
		cout << "opt aleasa: ";
		cin >> opt;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			throw string("ERR: tip de date invalid\n");
		}
		if (opt < 1 || opt > 2)
			throw string("Optiune nu exista\n");
		SwitchCase(opt);
	}
	catch (const string& e) {
		cout << e << "\n";
	}
}



Singleton* Singleton::ptr = nullptr;
vector<Candidat> Singleton::inscrieri;
bool Singleton::ongoing = true;

int main()
{
	Singleton* sistem = Singleton::GetInstance();

	do {
		sistem->RunMenu();
	} while (Singleton::IsOngoing());
	return 0;
}
