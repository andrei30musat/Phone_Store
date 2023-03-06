#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <iterator>
#include <map>

using namespace std;

class IO_Interface {
public:
    virtual istream &Citire(istream &in) = 0;

    virtual ostream &Afisare(ostream &out) const = 0;
};

bool isNumber(string s)//functie cu care verific daca un string e un numar
{
    for (int i = 0; i < s.size(); i++)
        if (isdigit(s[i]) == 0)
            return false;

    return true;
}

class Telefon : public IO_Interface {
protected:
    string nume;
    const int ID;
    static int contorID;
public:
    Telefon() : ID(contorID++) {
        this->nume = "";
    }

    Telefon(string nume): ID(contorID) {
        this->nume = nume;
    }

    Telefon(const Telefon &t): ID(contorID) {
        this->nume = t.nume;
    }

    Telefon &operator=(const Telefon &t) {

        if (this != &t) {
            this->nume = t.nume;

        }
        return *this;
    }

    virtual istream &Citire(istream &in) {
        cout << "Brand-ul telefonului: ";
        while (true) {
            try {
                in >> this->nume;
                if (isNumber(this->nume))
                    throw string("\n Numele introdus este invalid. ");
                break;
            }
            catch (string s) {
                cout << s;
                cout << "\n Introdu un nume valid: ";
            }
        }
        return in;
    }

    virtual ostream &Afisare(ostream &out) const {
        out << "\n Brand-ul telefonului este: ";
        out << this->nume;
        out<<"\n ID telefonului este: "<<this->ID;
        return out;
    }

    friend istream &operator>>(istream &in, Telefon &t) {
        return t.Citire(in);
    }

    friend ostream &operator<<(ostream &out, const Telefon &t) {

        return t.Afisare(out);
    }

    string getNume() const {
        if (!this->nume.empty())

            return this->nume;

        throw runtime_error("Accesati o zona de memorie nula");
    }
    int getID() const{
        return this->ID;
    }
    virtual ~Telefon() {
        this->nume = "";
    }
};
int Telefon :: contorID  = 1000;
class Mobil : public virtual Telefon {
protected:
    int camera;
    int baterie;
public:
    Mobil() : Telefon() {
        this->camera = 0;
        this->baterie = 0;
    }

    Mobil(string nume, int camera, int baterie) : Telefon(nume) {
        this->camera = camera;
        this->baterie = baterie;
    }

    Mobil(const Mobil &t) : Telefon(t) {

        this->camera = t.camera;
        this->baterie = t.baterie;
    }

    Mobil &operator=(const Mobil &t) {

        if (this != &t) {
            Telefon::operator=(t);
            this->camera = t.camera;
            this->baterie = t.baterie;
        }
        return *this;
    }

    istream &Citire(istream &in) {
        Telefon::Citire(in);
        cout << "Camera principala a telefonului[MP]: ";
        while (true) {
            try {
                in >> this->camera;
                if (this->camera<0.1)
                    throw string("\n Input-ul introdus este invalid. ");
                break;
            }
            catch (string s) {
                cout << s;
                cout << "\n Camera principala a telefonului: ";
            }
        }
        cout << "Capacitatea bateriei telefonului[mAh]: ";
        while (true) {
            try {
                in >> this->baterie;
                if (this->baterie<100)
                    throw string("\n Input-ul introdus este invalid. ");
                break;
            }
            catch (string s) {
                cout << s;
                cout << "\n Capacitatea bateriei telefonului: ";
            }
        }
        return in;
    }

    ostream &Afisare(ostream &out) const {
        Telefon::Afisare(out);
        out << "\n Camera principala a telefonului are: " << this->camera << " MP";
        out << "\n Capacitate bateriei : " << this->baterie << " mAh";
        return out;
    }

    int getBaterie() const {
        if (this->baterie != 0)
            return this->baterie;

        throw runtime_error("Accesati o zona de memorie nula");
    }

    int getCamera() const {
        if (this->camera != 0)
            return this->camera;

        throw runtime_error("Accesati o zona de memorie nula");
    }
    int calculeazaAutonomie(){///autonomia telefonului
        return this->baterie/280;
    }
    virtual ~Mobil() {
        this->camera = 0;
        this->baterie = 0;
    }
};

class Smartphone : public Mobil {
private:
    int protectie;//rezistenta telefonului la praf si apa
public:
    Smartphone() : Telefon(), Mobil() {

        this->protectie = 0;
    }

    Smartphone(string nume, int camera, int baterie, int protectie) : Telefon(nume),
                                                                      Mobil(nume, camera, baterie) {

        this->protectie = protectie;
    }

    Smartphone(const Smartphone &t) : Telefon(t), Mobil(t) {


        this->protectie = t.protectie;
    }

    Smartphone &operator=(const Smartphone &t) {

        if (this != &t) {
            Mobil::operator=(t);
            this->protectie = t.protectie;
        }
        return *this;
    }

    istream &Citire(istream &in) {
        Mobil::Citire(in);
        cout << "Protectia telefonului la praf si apa?(IP)";
        while (true) {
            try {
                bool s;
                in >> this->protectie;
                if (this->protectie < 10)
                    throw s;
                break;
            }
            catch (bool s) {
                cout << "\n Input-ul introdus este invalid. ";
                cout << "\n Protectia telefonului?(IP)";
            }
        }
        return in;
    }

    ostream &Afisare(ostream &out) const {
        Mobil::Afisare(out);
        out << "\n Protectia telefonului la praf si apa este IP" << this->protectie;
        return out;
    }

    ~Smartphone() {
        this->protectie = 0;
    }
};

class Tableta {
private:
    float ecran;
public:
    Tableta() {
        this->ecran = 0;
    }

    Tableta(float ecran) {
        this->ecran = ecran;
    }

    Tableta(const Tableta &t) {
        this->ecran = t.ecran;
    }

    Tableta &operator=(const Tableta &t) {
        if (this != &t)
            this->ecran = t.ecran;
        return *this;
    }

    friend istream &operator>>(istream &in, Tableta &t) {
        cout << "Display inch: ";
        while (true) {
            try {
                float s;
                in >> t.ecran;
                if (t.ecran < 1)
                    throw s;
                break;
            }
            catch (float s) {
                cout << "\n Input-ul introdus este invalid. ";
                cout << "\n Display inch: ";
            }
        }
        return in;
    }

    friend ostream &operator<<(ostream &out, Tableta &t) {

        out << "\n Tableta are un display de " << t.ecran << " inch";
        return out;
    }

    ~Tableta() {
        this->ecran = 0;
    }

    float getEcran() const {
        if (this->ecran != 0)
            return this->ecran;

        throw runtime_error("Accesati o zona de memorie nula");
    }

    void setEcran(float ecran) {
        this->ecran = ecran;
    }

};

template<typename T>
class Base {
private:
    T x;
public:

    Base() = default;

    Base(T x) {
        this->x = x;
    }

    Base(const Base &a) {

        this->x = a.x;
    };

    Base &operator=(const Base &a) {

        if (this != &a)
            this->x = a.x;
        return *this;
    }

    friend istream &operator>>(istream &in, Base<T> &a) {
        in >> a.x;
        return in;
    }

    friend ostream &operator<<(ostream &out, const Base<T> &a) {
        out << a.x;
        return out;
    }

    T getX() const {
        return x;
    }

    void setX(T y) {
        this->x = y;
    }

    ~Base() {};

};

template<typename T>
T Max(T x, T y) {
    return (x > y) ? x : y;
}
template<typename T>
int Max(T x, string y){
    int l=y.size();
    if(l>x)
        return 1;
    return 0;
}

template<typename T>
T Egal(T x, T y) {
    return x == y;
}

class MeniuInteractiv {
private:
    vector<Telefon *> listaTelefoane;
    set<Mobil *> listaMobile;
    list<Smartphone *> listaSmartphone;
    vector<Base<int> *> listaAn;
    vector<Base<float> *> listaPret;
    map<int, Base<string> *> listaNume;
    map<int, Tableta *> listaTablete;


    static MeniuInteractiv *instanta;

    MeniuInteractiv() = default;

    MeniuInteractiv(const MeniuInteractiv &m) = default;

public:
    static MeniuInteractiv *getInstanta() {
        if (instanta == nullptr)
            instanta = new MeniuInteractiv();
        return instanta;
    }

    void start() {
        int optiune, k = 1, j = 0, i = 0;
        while (k == 1) {
            cout << "\n 1-Adauga Telefon Fix";
            cout << "\n 2-Adauga Telefon Mobil cu butoane";
            cout << "\n 3-Adauga Smartphone";
            cout << "\n 4-Sterge un telefon din lista";
            cout << "\n 5-Afiseaza lista cu toate telefoanele";
            cout << "\n 6-Adauga Tableta";
            cout << "\n 7-Afiseaza toate tabletele";
            cout << "\n 8-Sterge o tableta din lista";
            cout << "\n 9-Modifica o tableta";
            cout << "\n 10-Afiseaza lista cu telefoane mobile";
            cout << "\n 11-Afiseaza lista cu Smartphone-uri";
            cout << "\n 12-Pentru a compara 2 telefoane";
            cout << "\n 13-STOP";
            cout << endl;

            try {
                cin >> optiune;
                if (optiune < 0 || optiune > 13)
                    throw string("\n Optiune invalida");

                else {
                    switch (optiune) {
                        case 1: {
                            Telefon t;
                            cin >> t;
                            listaTelefoane.push_back(new Telefon(t));

                            Base<int> an;
                            cout << "An aparitie telefon: ";
                            while (true) {
                                try {
                                    cin >> an;
                                    if (an.getX() < 1876 || an.getX() > 2023)
                                        throw string("\n Input-ul este invalid. ");
                                    break;
                                }
                                catch (string s) {
                                    cout << s;
                                    cout << "\n An aparitie telefon: ";
                                }
                            }
                            listaAn.push_back(new Base<int>(an));

                            Base<float> pret;
                            cout << "Pret telefon: ";
                            while (true) {
                                try {
                                    cin >> pret;
                                    if (pret.getX() < 1)
                                        throw string("\n Input-ul este invalid. ");
                                    break;
                                }
                                catch (string s) {
                                    cout << s;
                                    cout << "\n Pret telefon: ";
                                }
                            }
                            listaPret.push_back(new Base<float>(pret));

                            break;
                        }
                        case 2: {
                            Mobil t;
                            cin >> t;
                            listaMobile.insert(new Mobil(t));
                            listaTelefoane.push_back(new Mobil(t));

                            Base<int> an;
                            cout << "An aparitie telefon mobil: ";
                            while (true) {
                                try {
                                    cin >> an;
                                    if (an.getX() < 1876 || an.getX() > 2023)
                                        throw string("\n Input-ul este invalid. ");
                                    break;
                                }
                                catch (string s) {
                                    cout << s;
                                    cout << "\n An aparitie telefon mobil: ";
                                }
                            }
                            listaAn.push_back(new Base<int>(an));

                            Base<float> pret;
                            cout << "Pret telefon mobil: ";
                            while (true) {
                                try {
                                    cin >> pret;
                                    if (pret.getX() < 1)
                                        throw string("\n Input-ul este invalid. ");
                                    break;
                                }
                                catch (string s) {
                                    cout << s;
                                    cout << "\n Pret telefon mobil: ";
                                }
                            }
                            listaPret.push_back(new Base<float>(pret));

                            break;
                        }
                        case 3: {
                            Smartphone t;
                            cin >> t;

                            listaTelefoane.push_back(new Smartphone(t));

                            Base<int> an;
                            cout << "An aparitie Smartphone: ";
                            while (true) {
                                try {
                                    cin >> an;
                                    if (an.getX() < 1876 || an.getX() > 2023)
                                        throw string("\n Input-ul este invalid. ");
                                    break;
                                }
                                catch (string s) {
                                    cout << s;
                                    cout << "\n An aparitie Smartphone: ";
                                }
                            }
                            listaAn.push_back(new Base<int>(an));

                            Base<float> pret;
                            cout << "Pret Smartphone: ";
                            while (true) {
                                try {
                                    cin >> pret;
                                    if (pret.getX() < 1)
                                        throw string("\n Input-ul este invalid. ");
                                    break;
                                }
                                catch (string s) {
                                    cout << s;
                                    cout << "\n Pret Smartphone: ";
                                }
                            }
                            listaPret.push_back(new Base<float>(pret));

                            break;
                        }
                        case 4: {
                            int index;
                            cout << "\n !Note: Indexul incepe de la 0";
                            cout << "\n Indexul telefonului pe care doriti sa l stergeti: ";
                            while (true) {
                                try {
                                    cin >> index;
                                    if (index < 0)
                                        throw string("\n Input-ul este invalid. ");
                                    break;
                                }
                                catch (string s) {
                                    cout << s;
                                    cout << "\n Indexul telefonului pe care doriti sa l stergeti: ";
                                }
                            }

                            listaTelefoane.erase(listaTelefoane.begin() + index);
                            listaAn.erase(listaAn.begin() + index);
                            listaPret.erase(listaPret.begin() + index);

                            break;
                        }
                        case 5: {
                            try{
                                if (listaTelefoane.empty())
                                    throw runtime_error("Accesati o zona de memorie nula");

                                cout << "\n Lista cu toate telefoanele: " << endl;
                                for (int i = 0; i < listaTelefoane.size(); i++) {
                                    cout << *listaTelefoane[i] << endl;
                                    if(dynamic_cast<Mobil*>(listaTelefoane[i]))
                                        cout<<"Autonomia telefonului este de: "<<dynamic_cast<Mobil*>(listaTelefoane[i])->calculeazaAutonomie()<<" de ore."<<endl;
                                    cout << "Anul aparitiei telefonului este: " << *listaAn[i] << endl;
                                    cout << "Pretul telefonului este: " << *listaPret[i] << endl;
                                }
                            }
                            catch (...)
                            {
                                cout<<"Trebuie sa introduceti date ca sa le afisati.";
                            }
                            break;
                        }
                        case 6: {
                            Base<string> name;
                            cout << "Brand-ul tabletei: ";
                            while (true) {
                                try {
                                    cin >> name;
                                    if (isNumber(name.getX()))
                                        throw string("\n Input-ul este invalid. ");

                                    if(Max(3,name.getX())==0)//vreau ca numele sa aiba o lungime minima
                                        throw runtime_error("\n");
                                    break;
                                }
                                catch (string s) {
                                    cout << s;
                                    cout << "\n Nume tableta: ";
                                }
                                catch(...){
                                    cout<<"\n Numele este prea scurt";
                                    cout<<"\n Introdu alt nume: ";
                                }
                            }
                            listaNume.emplace(++i, new Base<string>(name));

                            Tableta t;
                            cin >> t;
                            listaTablete.emplace(++j, new Tableta(t));
                            break;
                        };
                        case 7: {
                            try{
                                if (listaTablete.empty())
                                    throw runtime_error("Accesati o zona de memorie nula");

                                cout << "Tabletele sunt: " << endl;
                                map<int, Tableta *>::iterator it;
                                map<int, Base<string> *>::iterator it2;
                                for (it = listaTablete.begin(), it2 = listaNume.begin();
                                     it != listaTablete.end(); it++, it2++) {
                                    cout << "Brand tableta: " << *it2->second;
                                    cout << *it->second << endl;
                                }
                            }
                            catch (...)
                            {
                                cout<<"Trebuie sa introduceti date ca sa le afisati.";
                            }
                            break;
                        };
                        case 8: {
                            ///Tabletele raman cu indexul cu care au fost adaugate prima data
                            int index;
                            cout << "Indexul tabletei pe care doriti sa o stergeti: ";
                            while (true) {
                                try {
                                    cin >> index;
                                    if (index < 0)
                                        throw string("\n Input-ul este invalid. ");
                                    break;
                                }
                                catch (string s) {
                                    cout << s;
                                    cout << "\n Indexul tabletei pe care doriti sa o stergeti: ";
                                }
                            }
                            listaTablete.erase(index);
                            listaNume.erase(index);
                            break;
                        }
                        case 9: {

                            int index;
                            cout << "Indexul tabletei pe care doriti sa o modificati: ";
                            while (true) {
                                try {
                                    cin >> index;
                                    if (index < 0)
                                        throw string("\n Input-ul este invalid. ");
                                    break;
                                }
                                catch (string s) {
                                    cout << s;
                                    cout << "\n Indexul tabletei pe care doriti sa o modificati: ";
                                }
                            }

                            string name;
                            cout << "Brand tableta: ";
                            while (true) {
                                try {
                                    cin >> name;
                                    if (isNumber(name))
                                        throw string("\n Input-ul este invalid. ");
                                    break;
                                }
                                catch (string s) {
                                    cout << s;
                                    cout << "\n Brand tableta: ";
                                }
                            }

                            listaNume[index]->setX(name);

                            float ecran;
                            cout << "Display inch tableta: ";
                            while (true) {
                                try {
                                    cin >> ecran;
                                    if (ecran < 1)
                                        throw string("\n Input-ul introdus este invalid. ");
                                    break;
                                }
                                catch (string s) {
                                    cout << s;
                                    cout << "\n Display inch: ";
                                }
                            }
                            listaTablete[index]->setEcran(ecran);

                            break;
                        }
                        case 10: {
                            try{
                                if (listaMobile.empty())
                                    throw runtime_error("Accesati o zona de memorie nula");

                                cout << "\n Lista cu toate telefoanele mobile : " << endl;
                                set<Mobil *>::iterator itr;
                                for (itr = listaMobile.begin(); itr != listaMobile.end(); itr++)
                                    cout << **itr << endl;
                            }
                            catch (...)
                            {
                                cout<<"Trebuie sa introduceti date ca sa le afisati.";
                            }
                            break;
                        }
                        case 11: {
                            listaSmartphone.clear();
                            for (int i = 0; i < listaTelefoane.size(); i++) {
                                Smartphone *m = dynamic_cast<Smartphone *>(listaTelefoane[i]);
                                if (m!= nullptr)
                                    listaSmartphone.push_back(new Smartphone(*m));
                            }
                            try{
                                if (listaSmartphone.empty())
                                    throw runtime_error("Accesati o zona de memorie nula");

                                cout << "\n Lista cu toate Smartphone-uri: " << endl;
                                list<Smartphone *>::iterator itr;
                                for (itr = listaSmartphone.begin(); itr != listaSmartphone.end(); itr++)
                                    cout << **itr << endl;
                            }
                            catch (...)
                            {
                                cout<<"Trebuie sa introduceti date ca sa le afisati.";
                            }
                            break;
                        }
                        case 12: {
                            cout << "\n !Note: Indexul incepe de la 0";
                            int index1, index2;
                            cout << "\n Introdu indexul primului telefonu: ";
                            while (true) {
                                try {
                                    cin >> index1;
                                    if (index1 < 0)
                                        throw string("\n Input-ul este invalid. ");
                                    break;
                                }
                                catch (string s) {
                                    cout << s;
                                    cout << "\n Introdu indexul primului telefonu: ";
                                }
                            }
                            cout << "Introdu indexul al doilea telefon: ";
                            while (true) {
                                try {
                                    cin >> index2;
                                    if (index2 < 0)
                                        throw string("\n Input-ul este invalid. ");
                                    break;
                                }
                                catch (string s) {
                                    cout << s;
                                    cout << "\n Introdu indexul al doilea telefon: ";
                                }
                            }
                            if (Egal<int>(listaAn[index1]->getX(), listaAn[index2]->getX()))
                                cout << "\n Telefoanele au aparut in acelasi an, " << listaAn[index1]->getX();
                            else {

                                if (Max<int>(listaAn[index1]->getX(), listaAn[index2]->getX()) ==
                                    listaAn[index1]->getX())
                                    cout << "\n Telefonul mai nou este: " << listaTelefoane[index1]->getNume();
                                else
                                    cout << "\n Telefonul mai nou este: " << listaTelefoane[index2]->getNume();
                            }
                            cout << endl;
                            if (Egal<float>(listaPret[index1]->getX(), listaPret[index2]->getX()))
                                cout << "\n Telefoanele au acelasi pret, " << listaPret[index1]->getX() << " de lei.";
                            else {

                                if (Max<float>(listaPret[index1]->getX(), listaPret[index2]->getX()) ==
                                    listaPret[index1]->getX())
                                    cout << "\n Telefonul mai ieftin este: " << listaTelefoane[index2]->getNume();
                                else
                                    cout << "\n Telefonul mai ieftin este: " << listaTelefoane[index1]->getNume();
                            }
                            break;
                        }
                        case 13: {
                            k = 0;
                            break;
                        }
                    }

                }
            }
            catch (string s) {
                cout << s;
            }
        }
    }
};

MeniuInteractiv *MeniuInteractiv::instanta = nullptr;

int main() {
    MeniuInteractiv *meniu = meniu->getInstanta();
    meniu->start();


    return 0;
}
