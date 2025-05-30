#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<typeinfo>

using namespace std;

class Jucarie
{
protected:
    string denumire;
    double dimensiune;
    string tip;

public:
    Jucarie()=default;
    Jucarie(const Jucarie&)=default;
    Jucarie& operator=(const Jucarie&)=default;
    friend istream& operator>>(istream&,Jucarie&);
    friend ostream& operator<<(ostream&,Jucarie&);
    virtual istream& citire(istream&);
    virtual ostream& afisare(ostream&) const;
    virtual ~Jucarie(){};
    virtual Jucarie* clone() const = 0;

};

istream&Jucarie::citire(istream&is)
{
    std::cout<<"denumire:";is>>denumire;
    std::cout<<"dimensiune:";is>>dimensiune;
    std::cout<<"tip:";is>>tip;
    return is;
}

istream& operator>>(istream&is,Jucarie&jucarie){
    return jucarie.citire(is);
}

ostream&Jucarie::afisare(ostream&os) const {
    os<<"denumire:"<< this-> denumire<<endl;
    os<<"dimensiune:"<<this->dimensiune <<endl;
    os<<"tip:"<< this->tip<<endl;
    return os;
}

ostream& operator<<(ostream&os,Jucarie&jucarie){
    return jucarie.afisare(os);
}




class Clasic :  public Jucarie
{
private:
    string material;
    string culoare;

public:
    Clasic()=default;
    Clasic(const Clasic&)=default;
    Clasic& operator=(const Clasic&)=default;
    virtual istream& citire(istream&);
    virtual ostream& afisare(ostream&) const;
    virtual ~Clasic(){};
    Jucarie* clone() const override { return new Clasic(*this); }

};

istream& Clasic::citire(istream&is)
{
    Jucarie::citire(is);
    std::cout<<"material:";is>>material;
    std::cout<<"culoare:";is>>culoare;
    return is;
}

ostream& Clasic::afisare(ostream&os) const
{
    Jucarie::afisare(os);
    os<<"material:"<<material<<endl;
    os<<"culoare:"<<culoare<<endl;
    return os;
}




class Educativ : virtual public Jucarie
{
protected:
    string abilitate;
public:
    Educativ()=default;
    Educativ(const Educativ&)=default;
    Educativ& operator=(const Educativ&)=default;
    virtual istream& citire(istream&);
    virtual ostream& afisare(ostream&) const;
    virtual ~Educativ(){};
    Jucarie* clone() const override { return new Educativ(*this); }

};

istream& Educativ::citire(istream&is)
{
    Jucarie::citire(is);
    std::cout<<"abilitate:";is>>abilitate;
    return is;
}

ostream& Educativ::afisare(ostream&os) const
{
    Jucarie::afisare(os);
    os<<"abilitate:"<<abilitate<<endl;
    return os;
}




class Electronic : virtual public Jucarie
{
protected:
    int baterii;

public:
    Electronic()=default;
    Electronic(const Electronic&)=default;
    Electronic& operator=(const Electronic&)=default;
    virtual istream& citire(istream&);
    virtual ostream& afisare(ostream&) const;
    virtual ~Electronic(){};
    Jucarie* clone() const override { return new Electronic(*this); }

};

istream& Electronic::citire(istream&is)
{
    Jucarie::citire(is);
    std::cout<<"baterii:";is>>baterii;
    return is;
}

ostream& Electronic::afisare(ostream&os) const
{
    Jucarie::afisare(os);
    os<<"baterii:"<<baterii<<endl;
    return os;
}




class Modern : public Educativ, public  Electronic
{
protected:
    string brand;
    string model;

public:
    Modern();
    Modern(const Modern&)=default;
    Modern& operator=(const Modern&)=default;
    virtual istream& citire(istream&);
    virtual ostream& afisare(ostream&) const;
    virtual ~Modern(){};
    Jucarie* clone() const override { return new Modern(*this); }

};

Modern::Modern()
{
    this->abilitate="gandire";
    this->baterii=1;
}

istream& Modern::citire(istream&is)
{
    Jucarie::citire(is);
    std::cout<<"brand:";is>>brand;
    std::cout<<"model:";is>>model;
    return is;
}

ostream&  Modern::afisare(ostream&os) const
{
    Educativ::afisare(os);
    os<<"baterii:"<<baterii<<endl;
    os<<"brand:"<<brand<<endl;
    os<<"model:"<<model<<endl;
    return os;
}




class Copil
{
protected:
    static int count;
    const int id;
    string nume;
    string prenume;
    string adresa;
    int varsta;
    int fapteBune;
    vector<Jucarie*>jucariiPrimite;

public:
    Copil();
    Copil(const Copil&);
    Copil& operator=(const Copil&);
    friend istream& operator>>(istream&,Copil&);
    friend ostream& operator<<(ostream&,Copil&);
    virtual istream& citire(istream&);
    virtual ostream& afisare(ostream&) const;
    virtual ~Copil();
    int get_fapte_bune(){return this->fapteBune;}
    void add_jucarie(Jucarie*j);
    string get_nume(){return this->nume;}
    int get_varsta(){return this->varsta;}
    int get_id(){return this->id;}
    void set_fapte_bune(int x){this->fapteBune+=x;}
};

int Copil::count=0;

Copil::Copil():id(count++),nume(""),prenume(""),adresa(""),varsta(0),fapteBune(0)
{
    jucariiPrimite.resize(0);
}

Copil::Copil(const Copil&c):id(c.id),nume(c.nume),prenume(c.prenume),adresa(c.adresa),varsta(c.varsta),fapteBune(c.fapteBune)
{
    jucariiPrimite.resize(0);
    for(int i=0;i<c.jucariiPrimite.size();i++)
        jucariiPrimite.push_back(c.jucariiPrimite[i]->clone());
}

Copil& Copil::operator=(const Copil&c)
{
    if(this!=&c)
    {
        this->nume=c.nume;
        this->prenume=c.prenume;
        this->adresa=c.adresa;
        this->varsta=c.varsta;
        this->fapteBune=c.fapteBune;
        for(int i=0;i<jucariiPrimite.size();i++)
            delete jucariiPrimite[i];
        jucariiPrimite.clear();
        for(int i=0;i<c.jucariiPrimite.size();i++)
            jucariiPrimite.push_back(c.jucariiPrimite[i]->clone());
    }
    return *this;
}

Copil::~Copil()
{
   int n=jucariiPrimite.size();
   for(int i=0;i<n;i++)
        delete jucariiPrimite[i];
    jucariiPrimite.clear();
}

istream& Copil::citire(istream&is)
{
    std::cout<<"nume:";is>>nume;
    std::cout<<"prenume:";is>>prenume;
    std::cout<<"adresa:";is>>adresa;
    std::cout<<"varsta:";is>>varsta;
    std::cout<<"fapte bune:";is>>fapteBune;
    return is;
}

istream& operator>>(istream&is,Copil&copil)
{
    return copil.citire(is);
}

ostream&Copil::afisare(ostream&os) const 
{
    os<<"nume:"<< nume<<endl;
    os<<"prenume:"<< prenume<<endl;
    os<<"adresa:"<< adresa<<endl;
    os<<"varsta:"<<varsta <<endl;
    os<<"fapte bune:"<<fapteBune<<endl;
    os<<"jucarii:"<<endl;
    for(int i=0;i<fapteBune;i++)
    {
        std::cout<<*jucariiPrimite[i]<<std::endl;
        std::cout<<"-   -   -   -   -   -   -   -   -"<<std::endl;
    }
    return os;
}

ostream& operator<<(ostream&os,Copil&copil)
{
    return copil.afisare(os);
}

void Copil::add_jucarie(Jucarie*j)
{
    jucariiPrimite.push_back(j);
}




class copilCuminte:public Copil
{

protected:
    int dulciuri;
public:
    copilCuminte();
    copilCuminte(const copilCuminte&);
    copilCuminte& operator=(const copilCuminte&);
    virtual istream& citire(istream&);
    virtual ostream& afisare(ostream&) const;
    virtual ~copilCuminte(){};

};

copilCuminte::copilCuminte()
{
    this->dulciuri=0;
}

copilCuminte::copilCuminte(const copilCuminte&c):Copil(c)
{
    this->dulciuri=c.dulciuri;
}

copilCuminte& copilCuminte::operator=(const copilCuminte&c)
{
    if(this!=&c)
    {
        this->Copil::operator=(c);
        this->dulciuri=c.dulciuri;
    }
    return *this;
}

istream& copilCuminte::citire(istream&is){
    Copil::citire(is);
    std::cout<<"dulciuri:";is>>dulciuri;
    return is;
}

ostream&copilCuminte::afisare(ostream&os) const {
    Copil::afisare(os);
    os<<"dulciuri:"<< dulciuri<<endl;
    return os;
}




class copilNeastamparat:public Copil
{

protected:
    int carbuni;
public:
    copilNeastamparat();
    copilNeastamparat(const copilNeastamparat&);
    copilNeastamparat& operator=(const copilNeastamparat&);
    virtual istream& citire(istream&);
    virtual ostream& afisare(ostream&) const;
    virtual ~copilNeastamparat(){};

};

copilNeastamparat::copilNeastamparat()
{
    this->carbuni=0;
}

copilNeastamparat::copilNeastamparat(const copilNeastamparat&c):Copil(c)
{
    this->carbuni=c.carbuni;
}

copilNeastamparat& copilNeastamparat::operator=(const copilNeastamparat&c)
{
    if(this!=&c)
    {
        this->Copil::operator=(c);
        this->carbuni=c.carbuni;
    }
    return *this;
}

istream& copilNeastamparat::citire(istream&is){
    Copil::citire(is);
    std::cout<<"carbuni:";is>>carbuni;
    return is;
}

ostream&copilNeastamparat::afisare(ostream&os) const {
    Copil::afisare(os);
    os<<"carbuni:"<< carbuni<<endl;
    return os;
}



class Craciun
{
private:
    Craciun();
    Craciun(const Craciun&)=delete;
    Craciun &operator=(const Craciun&)=delete;

    inline static Craciun *craciun_gestiune;

    // vectorul de jucarii nu face parte din cerinta propriu-zisa
    // este folosit doar pentru a face teste pentru functiile din clasa  "Jucarie"

    vector<Jucarie*>jucarii; 
    vector<Copil*>copii;

    template<typename Comparator> void ordonare(Comparator comp) 
    {
        sort(copii.begin(), copii.end(), comp);
    }



public:

    ~Craciun();
    static Craciun* getInstance()
    {
        if(craciun_gestiune==nullptr)
            craciun_gestiune=new Craciun();
        return craciun_gestiune;
    }

    void afisareCopii();
    void afisareJucarii();
    void cautareCopil();
    void ordonareVarsta();
    void ordonareFapteBune();
    void actulizareFapteBune();
    void raport();

};

Craciun::Craciun()
{
    this->jucarii.resize(0);
    this->copii.resize(0);
}

Craciun::~Craciun()
{
   int n=jucarii.size();
   for(int i=0;i<n;i++)
        delete jucarii[0];

   n=copii.size();
   for(int i=0;i<n;i++)
        delete copii[0];

    jucarii.clear();
    copii.clear();
}

void Craciun::afisareCopii()
{
    int n;
    string tip_copil;
    std::cout<<"cati copii doriti sa introduceti?: ";std::cin>>n;
    for(int i=0;i<n;i++)
    {
        std::cout<<"copil "<<i<<std::endl;
        std::cout<<"ce fel de copil e?: ";cin>>tip_copil;

        Copil *c=nullptr;
        if(tip_copil=="cuminte")
            c=new copilCuminte;
        else if(tip_copil=="neastamparat")
            c=new copilNeastamparat;
        std::cin>>*c;

        std::cout<<"ce jucarii doreste copilul? poate avea maxim :"<<c->get_fapte_bune()<<std::endl;

        string tip_jucarie;
        for(int i=0;i<c->get_fapte_bune();i++)
        {

            std::cout<<"jucaria: "<<i<<std::endl;
            std::cout<<"ce tip de jucarie e ? (clasic/educativ/electronic/modern): ";
            std::cin>>tip_jucarie;

            Jucarie *j=nullptr;
            if(tip_jucarie=="clasic")
                j=new Clasic;
            else if (tip_jucarie=="educativ")
                j=new Educativ;
            else if (tip_jucarie=="electronic")
                j=new Electronic;
            else if (tip_jucarie=="modern")
                j=new Modern;
            std::cin>>*j;
            c->add_jucarie(j);
            jucarii.push_back(j);
        }

        copii.push_back(c);
    }
}

void Craciun::afisareJucarii()
{
    for(int i=0;i<copii.size();i++)
    {
        cout<<"copil "<<i<<endl;
        cout<<*copii[i];
        cout<<endl;
    }
}

void Craciun::cautareCopil()
{
    string nume;
    cout<<"introduceti numele copilului: ";cin>>nume;

    for(int i=0;i<copii.size();i++)
        if(copii[i]->get_nume()==nume)
            cout<<*copii[i]<<"\n---------------------------------------\n";
}

void Craciun::ordonareVarsta() {
    ordonare([](Copil* a, Copil* b) 
    { return a->get_varsta() < b->get_varsta(); });
}

void Craciun::ordonareFapteBune()
{
    for(int i=0;i<copii.size();i++)
        for(int j=i+1;j<copii.size();j++)
            if(copii[i]->get_fapte_bune()>copii[j]->get_fapte_bune())
                swap(copii[i],copii[j]);
}

void Craciun::actulizareFapteBune()
{
    int id;
    cout<<"id: ";cin>>id;

    for(int i=0;i<copii.size();i++)
    {
        if(copii[i]->get_id()==id)
        {

            cout<<"introduceti x: ";
            int x;cin>>x;
            copii[i]->set_fapte_bune(x);
            cout<<"adauga jucarii:";
            for(int i=0;i<x;i++)
            {
                cout<<"jucaria: "<<i<<endl;
                cout<<"ce tip de jucarie e ?(clasic/educativ/electronic/modern): ";
                string tip_jucarie;
                cin>>tip_jucarie;

                Jucarie *j=nullptr;
                if(tip_jucarie=="clasic")
                    j=new Clasic;
                else if (tip_jucarie=="educativ")
                    j=new Educativ;
                else if (tip_jucarie=="electronic")
                    j=new Electronic;
                else if (tip_jucarie=="modern")
                    j=new Modern;
                cin>>*j;
                copii[i]->add_jucarie(j);
                jucarii.push_back(j);

            }
            break;
        }
    }
}

void Craciun::raport()
{
    cout<<"numar total jucarii: "<<jucarii.size()<<endl;
    int cls=0, edu=0, elctr=0, mod=0;

    for (int i = 0; i < jucarii.size(); i++)
    {
        if (dynamic_cast<Modern*>(jucarii[i]))
            mod++;
        else if (dynamic_cast<Clasic*>(jucarii[i]))
            cls++;
        else if (dynamic_cast<Educativ*>(jucarii[i]))
            edu++;
        else if (dynamic_cast<Electronic*>(jucarii[i]))
            elctr++;
    }

    cout<<"clasic :"<<cls<<endl;
    cout<<"educativ: "<<edu<<endl;
    cout<<"electronic: "<<elctr<<endl;
    cout<<"modern: "<<mod<<endl;

}


void meniu()
{
    int optiune;
    cout<<"1.citire copii+jucarii\n";
    cout<<"2.afisare copii+jucarii\n";
    cout<<"3.cautare copil\n";
    cout<<"4.ordonare copii varsta\n";
    cout<<"5.ordonare copii fapte bune\n";
    cout<<"6.actualizare fapte bune\n";
    cout<<"7.afisare raport\n";
    cout<<"optiune: ";
    cin >> optiune;
    
    switch(optiune)
    {
        case 1:
        {
            Craciun::getInstance()->afisareCopii();
            cout<<endl;
            break;
        }
        case 2:
        {
           Craciun::getInstance()->afisareJucarii();
           cout<<endl;
           break;
        }
        case 3:
        {
            Craciun::getInstance()->cautareCopil();
            cout<<endl;
            break;
        }
        case 4:
        {
            Craciun::getInstance()->ordonareVarsta();
            cout<<endl;
            break;
        }
        case 5:
        {
            Craciun::getInstance()->ordonareFapteBune();
            cout<<endl;
            break;
        }
        case 6:
        {
            Craciun::getInstance()->actulizareFapteBune();
            cout<<endl;
            break;
        }
        case 7:
        {
            Craciun::getInstance()->raport();
            cout<<endl;
            break;
        }
    }

    meniu();
}



int main()
{
    meniu();
 
    return 0;
}