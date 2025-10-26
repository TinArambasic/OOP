#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

struct Student {
    int scores[5];

    Student() {
        fill_n(scores, 5, 0);
    }

    void fillScores(int(&arr)[5]) {
        copy(begin(arr), end(arr), begin(scores));
    }

    int calculateTotalScore() const {
        return accumulate(begin(scores), end(scores), 0);
    }

    void print() const {
        for (int i = 0; i < 5; ++i) {
            cout << scores[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    ifstream file("data.txt");
    if (!file.is_open()) {
        cerr << "Nije moguce otvoriti datoteku." << endl;
        return 1;
    }

    int numStudents;
    file >> numStudents;

    Student* students = new Student[numStudents];
    int markoScores[5];

    
    for (int i = 0; i < 5; ++i) {
        file >> markoScores[i];
    }

    
    for (int i = 0; i < numStudents; ++i) {
        int studentScores[5];
        for (int j = 0; j < 5; ++j) {
            file >> studentScores[j];
        }
        students[i].fillScores(studentScores);
    }
    file.close();

   
    int markoTotalScore = accumulate(begin(markoScores), end(markoScores), 0);

    int betterThanMarko = count_if(students, students + numStudents, [&](const Student& s) {
        return s.calculateTotalScore() >= markoTotalScore;
    });

    cout << "Broj studenata koji su napisali ispit bolje ili jednako kao Marko: " << betterThanMarko << endl;

    delete[] students;

    return 0;
}
