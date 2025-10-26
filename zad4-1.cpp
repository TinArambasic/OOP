#include <iostream>
using namespace std;

struct Node {
    double value;
    Node* next;

    Node() : value(0), next(nullptr) {}
    Node(double value) : value(value), next(nullptr) {}
    Node(const Node& n) : value(n.value), next(n.next) {}
    ~Node() {}

    void swap(Node& n) {
        double temp = value;
        value = n.value;
        n.value = temp;
    }

    void print() {
        cout << value << " ";
    }
};

class CSLL {
protected:
    Node* head;

public:
    CSLL() : head(nullptr) {}
    CSLL(const CSLL& c) : head(c.head) {
        if (c.head == nullptr) {
            head = nullptr;
        } else {
            // Kopiranje prvog čvora
            head = new Node(c.head->value);
            Node* current = head;
            Node* original = c.head->next;

            // Kopiranje ostalih čvorova
            while (original != c.head) {
                current->next = new Node(original->value);
                current = current->next;
                original = original->next;
            }

            current->next = head; // Povezivanje posljednjeg čvora s prvim
        }
    }

    ~CSLL() {
        if (head != nullptr) {
            Node* current = head->next;// Prvi čvor koji nije head
            Node* temp;

            // Oslobađanje svih čvorova u listi
            while (current != head) {
                temp = current;
                current = current->next;
                delete temp;
            }

            delete head;
        }
    }

    bool empty() {
        return head == nullptr;
    }
    
    void sort() {
        if (head == nullptr || head->next == head) {
            return; // So no head?
        }
        Node* i = head;
        do {
            Node* j = i->next;
            while (j != head) {
                if (i->value > j->value) {
                    i->swap(*j);
                }
                j = j->next;
            }
            i = i->next;
        } while (i != head);
    }

    void print() {
        if (head == nullptr) {
            cout << "Lista je prazna." << endl;
            return;
        }
        Node* temp = head;
        do {
            temp->print();
            temp = temp->next;
        } while (temp != head);
        cout << endl;
    }
    
    double removeFromHead() {
        if (head == nullptr) {
            return 0;
        }
        double value = head->value;
        Node* temp = head;
        if (head->next == head) {
            head = nullptr;
        } else {
            Node* last = head;
            while (last->next != head) {
                last = last->next;
            }
            head = head->next;
            last->next = head;
        }
        delete temp;
        return value;
    }

    void prepend(double value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            head->next = head;
        } else {
            Node* last = head;
            while (last->next != head) {
                last = last->next;
            }
            last->next = newNode;
            newNode->next = head;
            head = newNode;
        }
    }




};

int main() {
    CSLL list;
    list.print();

    list.append(59.9);
    list.append(13.7);
    list.append(10.0);
    list.append(98.44);
    list.append(16.7);
    list.append(20.269);
    list.append(1.5);
    list.print(); 

    cout << "Kreirana je lista2" << endl;
    CSLL list2(list);
    list2.sort();
    list2.print(); 
    
    list.~CSLL();
    list2.~CSLL();

    return 0;
}
