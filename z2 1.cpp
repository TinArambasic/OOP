
#include<iostream>
#include<vector>

using namespace std;

class Node
{
public:
    int n;
    Node* next;
    Node(int n, Node* N): n(n), next(N) {}
};

class List
{
protected:
    Node* head{}; // immediately set pointer to nullptr
public:
    List(){}
    void push_front(int);
    void display();
    bool erase(int);
    void eraseAll(int);
    void addKth(int,int);
    void eraseDuplicates();

    void destructorHelper(Node* a) {
        if (a == nullptr) {
            return;
        }

        destructorHelper(a->next);

        delete a;
    }
    ~List() {
        destructorHelper(head);
    };
};

void List::push_front(int n) {
    head = new Node(n, head);
}

void List::display() {
    Node* it = head;
    while (it != nullptr) {
        cout << it->n << '|' << it << " --> ";

        it = it->next;
    }

    cout << endl;
}

bool List::erase(int n) {
    if (head != nullptr && head->n == n) {
        Node* obrisati = head;
        head = head->next;

        delete obrisati;
        return true;
    }

    Node* it = head;
    while (it != nullptr) {
        if (it->next != nullptr && it->next->n == n) {
            Node* obrisati = it->next;
            it->next = obrisati->next;

            delete obrisati;
            return true;
        }

        it = it->next;
    }

    return false;
}

void List::eraseAll(int n) {
    if (head == nullptr) {
        return;
    }

    while (head != nullptr && head->n == n) {
        Node* obrisati = head;
        head = head->next;

        delete obrisati;
    }

    Node* it = head;
    while (it != nullptr) {
        if (it->next != nullptr && it->next->n == n) {
            Node* obrisati = it->next;
            it->next = obrisati->next;

            delete obrisati;
        }

        it = it->next;
    }
}

void List::addKth(int u, int n) {
    if (head == nullptr || u == 0) {
        push_front(n);

        return;
    }

    Node* it = head;
    int i = 0;

    while (i != u && it->next != nullptr) {
        it = it->next;
        i++;
    }

    it->next = new Node(n, it->next);
}

bool vec_exists(vector<int>& v, int n) {
    for (int x: v) {
        if (x == n) return true;
    }

    return false;
}

void List::eraseDuplicates() {
    vector<int> pojavili;

    if (head == nullptr) {
        return;
    }

    pojavili.push_back(head->n);

    Node* it = head;
    while (it->next != nullptr) {
        while (it->next != nullptr && vec_exists(pojavili, it->next->n)) {
            Node* obrisati = it->next;
            it->next = obrisati->next;

            delete obrisati;
        }
            
        pojavili.push_back(it->next->n); 

        it = it->next;
    }
}

int main()
{
    List L;     
    L.push_front(2);
    L.push_front(-1);
    L.push_front(7);
    L.push_front(4);
    L.push_front(-1);
    L.push_front(4);
    L.push_front(7);
    L.push_front(4);
    L.display();
    L.erase(4);
    L.display();
    L.addKth(2,8);
    L.addKth(0,-5);
    L.addKth(20,-7);
    L.display();
    L.eraseAll(4);
    L.display();
    L.eraseDuplicates();
    L.display();
    return 0;
}