
#include<iostream>
#include<cmath>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

class Complex {
protected:
    float r, fi;
public:
    Complex(); 
    Complex(float, float);
    Complex(const Complex&);

    float getModul() const { return r; };
    float getArgument() const { return fi; };
    void setModul(float nr) { r = nr; normal(); }; 
    void setArgument(float nfi) { fi = nfi; normal(); };

    Complex potencija(int);
    Complex& operator=(const Complex&);
    Complex& operator*=(const Complex&);
    Complex& operator/=(const Complex&);
    Complex operator*(const Complex&) const;
    Complex operator/(const Complex&) const;

    bool operator==(const Complex& c) const { return r == c.getModul() && fi == c.getArgument(); };
    bool operator!=(const Complex& c) const { return !((*this) == c); };

    void normal() {
        if (fi < 0) {
            fi += ceil(abs(fi) / (2 * M_PI)) * 2 * M_PI;
        }

        if (fi > 2 * M_PI) {
            fi -= floor(abs(fi) / (2 * M_PI)) * 2 * M_PI;
        }
    }
};

Complex::Complex() {}
Complex::Complex(float a, float b) {
    r = a;
    fi = b;

    normal();
}
Complex::Complex(const Complex& c) {
    fi = c.getArgument();
    r = c.getModul();

    normal();
}

Complex& Complex::operator=(const Complex& c) {
    fi = c.getArgument();
    r = c.getModul();

    normal();

    return *this;
}

// (a1 + b1i) * (a2 + b2i)
// a1 * a2 + (a1 * b2)i + (b1 * a2)i - (b1 * b2)
Complex& Complex::operator*=(const Complex& c) {
    r = r * c.getModul();
    fi = fi + c.getArgument();

    normal();

    return *this;
}

// (a1 + b1i) / (a2 + b2i)
// ((a1 + b1i) * (a2 - b2i)) / (a2^2 + b2^2)
Complex& Complex::operator/=(const Complex& c) {
    r = r / c.getModul();
    fi = fi - c.getArgument();

    normal();

    return *this;
}

Complex Complex::operator*(const Complex& c) const {
    Complex t(r, fi);
    t *= c;

    return t;
}

Complex Complex::operator/(const Complex& c) const {
    Complex t(r, fi);
    t /= c;

    return t;
}

Complex Complex::potencija(int e) {
    Complex t(r, fi);

    t.setModul(pow(r, e));
    t.setArgument(e * fi);

    t.normal();

    return t;
}

ostream& operator<<(ostream& os, const Complex& c) {
    os << c.getModul() << " ( cos " << c.getArgument() << " + i sin " << c.getArgument() << ')' << endl;

    return os;
};

int main() {
    Complex c1{2,M_PI};
    cout << c1;
    Complex c2{1,1.5*M_PI};
    cout << c2;
    c2*=c1;
    cout << c2;
    Complex c3 = c2.potencija(-3);
    cout << c3;
    c3/=c1;
    cout << c3;
    cout << (c1 == c2) << endl;
    cout << (c1 != c2) << endl;
    Complex c4 = c2/c3;
    cout << c4;
    Complex c5 = c3 *c4;
    cout << c5;
    return 0;
}