#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Zakaznik {
protected:
    string jmeno;
    string email;

public:
    Zakaznik(string jmeno, string email) : jmeno(jmeno), email(email) {}

    virtual void zobrazInfo() const {
        cout << "Zakaznik: " << jmeno << endl;
        cout << "Email: " << email << endl;
    }
};

class RegularniZakaznik : public Zakaznik {
private:
    int bodyZaVernost;

public:
    RegularniZakaznik(string jmeno, string email, int bodyZaVernost) : Zakaznik(jmeno, email), bodyZaVernost(bodyZaVernost) {}

    void zobrazInfo() const override {
        Zakaznik::zobrazInfo();
        cout << "Body za vernost: " << bodyZaVernost << endl;
    }
};

class VIPZakaznik : public Zakaznik {
private:
    string urovenVIP;

public:
    VIPZakaznik(string jmeno, string email, string urovenVIP) : Zakaznik(jmeno, email), urovenVIP(urovenVIP) {}

    void zobrazInfo() const override {
        Zakaznik::zobrazInfo();
        cout << "VIP uroven: " << urovenVIP << endl;
    }
};

class Produkt {
protected:
    string nazev;
    double cena;

public:
    Produkt(string nazev, double cena) : nazev(nazev), cena(cena) {}

    virtual void zobrazInfo() const {
        cout << "Produkt: " << nazev << endl;
        cout << "Cena: $" << cena << endl;
    }
};

class DigitalniProdukt : public Produkt {
private:
    string odkazKeStazeni;

public:
    DigitalniProdukt(string nazev, double cena, string odkazKeStazeni) : Produkt(nazev, cena), odkazKeStazeni(odkazKeStazeni) {}

    void zobrazInfo() const override {
        Produkt::zobrazInfo();
        cout << "Odkaz ke stazeni: " << odkazKeStazeni << endl;
    }
};

class FyzickyProdukt : public Produkt {
private:
    double vaha;

public:
    FyzickyProdukt(string nazev, double cena, double vaha) : Produkt(nazev, cena), vaha(vaha) {}

    void zobrazInfo() const override {
        Produkt::zobrazInfo();
        cout << "Vaha: " << vaha << " kg" << endl;
    }
};

class PolozkaObjednavky {
private:
    Produkt* produkt;
    int mnozstvi;

public:
    PolozkaObjednavky(Produkt* produkt, int mnozstvi) : produkt(produkt), mnozstvi(mnozstvi) {}

    void zobrazInfo() const {
        produkt->zobrazInfo();
        cout << "Mnozstvi: " << mnozstvi << endl;
    }
};

class Objednavka {
private:
    Zakaznik* zakaznik;
    vector<PolozkaObjednavky> polozky;

public:
    Objednavka(Zakaznik* zakaznik) : zakaznik(zakaznik) {}

    void pridejPolozku(Produkt* produkt, int mnozstvi) {
        polozky.emplace_back(produkt, mnozstvi);
    }

    void zobrazInfo() const {
        cout << "Informace o objednavce:" << endl;
        zakaznik->zobrazInfo();
        cout << "Polozky:" << endl;
        for (const auto& polozka : polozky) {
            polozka.zobrazInfo();
        }
    }
};

int main() {
    RegularniZakaznik regularniZakaznik("Jan Novak", "jan@priklad.cz", 100);
    VIPZakaznik vipZakaznik("Eva Svobodova", "eva@priklad.cz", "Zlaty");

    DigitalniProdukt digitalniProdukt("E-kniha", 29.99, "https://priklad.com/ekniha");
    FyzickyProdukt fyzickyProdukt("Tricko", 19.99, 0.2);

    Objednavka objednavka1(&regularniZakaznik);
    objednavka1.pridejPolozku(&digitalniProdukt, 2);

    Objednavka objednavka2(&vipZakaznik);
    objednavka2.pridejPolozku(&fyzickyProdukt, 3);

    objednavka1.zobrazInfo();
    cout << endl;
    objednavka2.zobrazInfo();

    return 0;
}
