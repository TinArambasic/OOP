#include <iostream>
using namespace std;

struct Node {
    double value;
    Node* next;

    Node() : value(0), next(nullptr) {}
    Node(double value) : value(value), next(nullptr) {}
    void print(){
    	cout << value << " ";
	};
};


class CSLL {
protected:
    Node* head;

public:
    CSLL() : head(nullptr) {}
    CSLL(const CSLL& c) : head(nullptr) 
{	
    if (c.head == nullptr){
    	return;
	}
    head = new Node(c.head->value);
    Node* current = head;
    Node* original = c.head->next;
    while (original != c.head) {
        current->next = new Node(original->value);
        current = current->next;
        original = original->next;
    }
    current->next = head; 
}

    ~CSLL() {
	if (head == nullptr) return;
    Node* current = head;
    do {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    } while (current != head);
	}

    bool empty() {
        return head == nullptr;
    }

    void append(double value) {
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
        }
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
};


class DynamicQueue {
protected:
    CSLL container;

public:
    DynamicQueue() {}

    DynamicQueue(const DynamicQueue& q) : container(q.container) {}

    ~DynamicQueue() {}

    bool empty() {
        return container.empty();
    }

    void enqueue(double x) {
        container.append(x);
    }

    double dequeue() {
        return container.removeFromHead();
    }

    void print() {
        container.print();
    }
};

int main() {
    DynamicQueue* queue = new DynamicQueue();
    queue->print();

    
    queue->enqueue(59.9);
    queue->enqueue(13.7);
    queue->enqueue(10.0);
    queue->enqueue(98.44);
    queue->enqueue(16.7);
    queue->enqueue(20.269);
    queue->enqueue(1.5);

    queue->print();

    DynamicQueue* Q = new DynamicQueue(*queue); //copy
    Q->print();

    
    delete queue;
    delete Q;

    return 0;
}
