#include <iostream>
#include <cmath>
using namespace std;

class Triangle;

class Point {
public:
    double x, y;
    Point() : x(0), y(0) {}
    Point(double x_, double y_) : x(x_), y(y_) {}
    ~Point() {}
    
    bool isInsideTriangle(const Triangle&);
    void print() const {
        cout << "(" << x << ", " << y << ")";
    }

private:
    bool isIntersect(const Point&, const Point&);
};

class Triangle {
public:
    Point A, B, C;
    Triangle(const Point& A_, const Point& B_, const Point& C_) : A(A_), B(B_), C(C_) {}
    ~Triangle() {}
    
    void print() {
        cout << "Trokut: ";
        A.print(); cout << ", ";
        B.print(); cout << ", ";
        C.print(); cout << endl;
    }
    
    double triangleCircumference() {
        return distance(A, B) + distance(B, C) + distance(C, A);
    }
    
    int triangleType() {
        double sideAB = distance(A, B);
        double sideBC = distance(B, C);
        double sideCA = distance(C, A);
        
        if (sideAB == sideBC && sideBC == sideCA)
            return 1; // Jednakostranicni
        else if (sideAB == sideBC || sideBC == sideCA || sideCA == sideAB)
            return 2; // Jednakokracni
        else
            return 3; // Raznostranican
    }

private:
    double distance(const Point& p1, const Point& p2) {
        return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
    }
};

bool Point::isIntersect(const Point& p1, const Point& p2) {
    
    if (y < min(p1.y, p2.y) || y > max(p1.y, p2.y))
        return false;

    // Provjeravamo je li točka na lijevoj strani
    if (x >= max(p1.x, p2.x))
        return false;

    if (x < min(p1.x, p2.x))
        return true;

    // Izračunamo smjer bridova
    double dx1 = p1.x - x;
    double dy1 = p1.y - y;
    double dx2 = p2.x - x;
    double dy2 = p2.y - y;

    return (dx1 * dy2 - dy1 * dx2) > 0;
}

bool Point::isInsideTriangle(const Triangle& t) {
    int intersections = 0;

    // Provjeravamo s kime se zraka sječe
    if (isIntersect(t.A, t.B) && isIntersect(t.B, t.C) && isIntersect(t.C, t.A))
        intersections = 3;
    else if (isIntersect(t.A, t.B) && isIntersect(t.B, t.C))
        intersections = 2;
    else if (isIntersect(t.B, t.C) && isIntersect(t.C, t.A))
        intersections = 2;
    else if (isIntersect(t.C, t.A) && isIntersect(t.A, t.B))
        intersections = 2;
    else if (isIntersect(t.A, t.B) || isIntersect(t.B, t.C) || isIntersect(t.C, t.A))
        intersections = 1;

    if (intersections % 2 == 1) {
        cout << "Tocka je unutar trokuta." << endl;
        return 1;
    } else {
        cout << "Tocka je van trokuta." << endl;
        return 0;
    }
}

int main() {
    //Instanciranje
    Point* p1 = new Point(0, 0);
    Point* p2 = new Point(4, 0);
    Point* p3 = new Point(2, 3);
    Point* p5 = new Point(2, 2);
    
    Triangle* t1 = new Triangle(*p1, *p2, *p3);
    
    cout<<"Vrhovi trokuta:"<<endl;
    t1->print();
    
    cout<<"Vrsta trokuta:"<<endl;
    cout<<t1->triangleType();
    cout<<endl;
    
    cout<<"Opseg trokuta:"<<endl;
    cout<<t1->triangleCircumference();
    cout<<endl;
    
    cout<<p5->isInsideTriangle(*t1)<<endl;
    
    
    delete p1;
    delete p2;
    delete p3;
    delete p5;
    delete t1;
    
}
