
#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;

class Point {
    double x, y;
public:
    Point(): x{}, y{} {};
    Point(double x, double y): x{x}, y{y} {};
    Point(const Point& p): x{p.x}, y{p.y} {};

    void setx(double a) {x = a;}
    void sety(double b) {y = b;};

    bool operator==(Point p) const { return x == p.getx() && y == p.gety(); }

    double getx() const {return x;};
    double gety() const {return y;};
    double euclideanDistance(const Point& p) const;
};

ostream& operator<<(ostream& out, const Point& p){

    out << '(' << p.getx() << ", " << p.gety() << ')' << endl;

    return out;   
}

double Point::euclideanDistance(const Point& p) const {
    return sqrt(pow(x - p.getx(), 2.0) + pow(y - p.gety(), 2.0));
}

/* Implementirati */
class Paket{
private:
    string prezime;
    Point adresa;
public:
    Paket(string& s, Point& p) { prezime = s; adresa = p; };
    Paket(const Paket& p) { prezime = p.getPrezime(); adresa = p.getAdresa(); };

    void setPrezime(string& s) { prezime = s; };
    void setAdresa(Point& p) { adresa = p; };

    bool operator==(Paket& p) { return prezime == p.getPrezime() && adresa == p.getAdresa(); }

    string getPrezime() const { return prezime; };
    Point getAdresa() const { return adresa; };
};

class Dostavljac{
private:
    vector<Paket> paketi;
public:
    Dostavljac() {};
    Dostavljac(vector<Paket>& c) { paketi = c; };

    bool dodajPaket(Paket&);
    bool makniPaket(Point&);

    void napraviRutu();
    vector<Paket>& getPaketi() { return paketi; };
};

bool Dostavljac::dodajPaket(Paket& c) {
    for (auto& p: paketi) {
        if (p.getAdresa() == c.getAdresa()) return false;
    }

    paketi.push_back(c);

    return true;
}

bool Dostavljac::makniPaket(Point& c) {
    auto it = paketi.begin();
    while (it != paketi.end()) {
        if ((*it).getAdresa() == c) {
            paketi.erase(it);
            return true;
        }

        it++;
    }

    return false;
}

ostream& operator<<(ostream& out, const Paket& p){
    out << "Adresa: " << p.getAdresa() << " , Prezime: " << p.getPrezime() << endl;

    return out;
}

void ispisPaketa(vector<Paket>& paketi) {
    for (auto& x: paketi) {
        cout << x;
    }
}

void Dostavljac::napraviRutu() {
    if (paketi.empty()) return;

    // prvi korak
    double minx = paketi[0].getAdresa().getx();
    int minxi = 0;
    for (int i = 0; i < paketi.size(); i++) {
        if (paketi[i].getAdresa().getx() < minx) {
            minx = paketi[i].getAdresa().getx();
            minxi = i;
        }
    }

    swap(paketi[0], paketi[minxi]);

    for (int i = 0; i < paketi.size() - 1; i++) {
        double minDist = paketi[i].getAdresa().euclideanDistance(paketi[i + 1].getAdresa());
        int minDistI = i + 1;

        for (int j = i + 1; j < paketi.size(); j++) {
            if (paketi[i].getAdresa().euclideanDistance(paketi[j].getAdresa()) < minDist) {
                minDist = paketi[i].getAdresa().euclideanDistance(paketi[j].getAdresa());
                minDistI = j;
            }
        }

        swap(paketi[i + 1], paketi[minDistI]);
    }
}

int main() {
    string prezime = "Horvat";

    Point adresa{2,5};

    Paket p1{prezime, adresa};

    string prezime2 = "Ivanov";

    Point adresa2{-1,2};

    Paket p2{prezime2, adresa2};

    string prezime3 = "Lovric";

    Point adresa3{1,3};

    Paket p3{prezime3, adresa3};

    string prezime4 = "Horvatic";

    Point adresa4{2,5};

    Paket p4{prezime4, adresa4};

    string prezime5 = "Bilic";

    Point adresa5{3,1};

    Paket p5{prezime5, adresa5};

    string prezime6 = "Nakic";

    Point adresa6{13,2};

    Paket p6{prezime6, adresa6};

    Dostavljac d{};

    cout << d.dodajPaket(p1) << endl;
    cout << d.dodajPaket(p2) << endl;
    cout << d.dodajPaket(p3) << endl;
    cout << d.dodajPaket(p4) << endl;
    cout << d.dodajPaket(p5) << endl;
    cout << d.dodajPaket(p6) << endl;

    ispisPaketa(d.getPaketi());
    Point adresa_makni1{-2,3};
    Point adresa_makni2{3,1};

    cout << d.makniPaket(adresa_makni1) << endl;
    cout << d.makniPaket(adresa_makni2) << endl;
    cout << "-------------------------"<< endl;

    ispisPaketa(d.getPaketi());
    cout << "-------------------------"<< endl;

    d.napraviRutu();
    ispisPaketa(d.getPaketi());

    return 0;
}