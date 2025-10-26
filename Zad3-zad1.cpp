#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

struct PositionVector {
    double x, y;
    
    PositionVector() : x(0.0), y(0.0) {}
    PositionVector(double x_val, double y_val) : x(x_val), y(y_val) {}
    PositionVector(const PositionVector& other) : x(other.x), y(other.y) {}
    
    double norm() const {
        return sqrt(x * x + y * y);
    }
    
    void print() const {
        cout << "x: " << x << ", y: " << y << ", norm: " << norm() << endl;
    }


};

int main() {
    PositionVector vectors[5] = {
	{2.3, 3.2}, 
	{4.3, 1.5}, 
	{2.9, 7.6}, 
	{5.4, 0.5}, 
	{0.0, 0.0}};
    
    cout << "Originalni redoslijed:" << endl;
    for (const auto& vec : vectors) {
        vec.print();
    }
    
    // Sortiranje vektora po normi u padajucem poretku
    sort(begin(vectors), end(vectors), [](const PositionVector& a, const PositionVector& b) {
        return a.norm() > b.norm();
    });
    
    cout << "\nSortirani redoslijed:" << endl;
    for (const auto& vec : vectors) {
        vec.print();
    }
    
    return 0;
}