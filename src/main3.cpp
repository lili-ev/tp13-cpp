
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <cstddef>

using namespace std;

// Exception : pile pleine
class StackOverflow : public exception {
public:
    const char* what() const noexcept override {
        return "Erreur : la pile est pleine !";
    }
};

// Exception : pile vide
class StackUnderflow : public exception {
public:
    const char* what() const noexcept override {
        return "Erreur : la pile est vide !";
    }
};

template <typename T>
class Stack {
private:
    unique_ptr<T[]> data;
    size_t capacity;
    size_t top;

public:
    // Constructeur avec capacite par defaut
    Stack(size_t c = 10) {
        capacity = c;
        top = 0;
        data = make_unique<T[]>(capacity);
    }

    // Constructeur avec iterateurs
    template <typename Iterator>
    Stack(Iterator debut, Iterator fin) {
        size_t n = 0;

        for (Iterator it = debut; it != fin; ++it) {
            n++;
        }

        capacity = n;
        top = 0;
        data = make_unique<T[]>(capacity);

        for (Iterator it = debut; it != fin; ++it) {
            data[top] = *it;
            top++;
        }
    }

    // Ajouter un element
    void push(const T& element) {
        if (top >= capacity) {
            throw StackOverflow();
        }

        data[top] = element;
        top++;
    }

    // Supprimer le dernier element
    void pop() {
        if (empty()) {
            throw StackUnderflow();
        }

        top--;
    }

    // Consulter le dernier element
    const T& peek() const {
        if (empty()) {
            throw StackUnderflow();
        }

        return data[top - 1];
    }

    // Verifier si la pile est vide
    bool empty() const {
        return top == 0;
    }

    // Afficher la taille
    size_t size() const {
        return top;
    }
};

int main() {

    try {
        // Test avec des entiers
        cout << "=== PILE D'ENTIERS ===" << endl;

        Stack<int> pile(5);

        pile.push(10);
        pile.push(20);
        pile.push(30);

        cout << "Dernier element : " << pile.peek() << endl;

        pile.pop();

        cout << "Apres pop : " << pile.peek() << endl;


        // Test StackOverflow
        cout << "\n=== TEST STACK OVERFLOW ===" << endl;

        pile.push(40);
        pile.push(50);
        pile.push(60);


    } catch (const StackOverflow& e) {
        cout << e.what() << endl;
    }


    try {
        // Test StackUnderflow
        cout << "\n=== TEST STACK UNDERFLOW ===" << endl;

        Stack<string> pile2(2);

        pile2.push("Bonjour");
        cout << pile2.peek() << endl;

        pile2.pop();
        pile2.pop();

    } catch (const StackUnderflow& e) {
        cout << e.what() << endl;
    }


    // Test avec une collection existante
    cout << "\n=== TEST AVEC ITERATEURS ===" << endl;

    int tab[] = {1, 2, 3, 4};

    Stack<int> pile3(tab, tab + 4);

    cout << "Dernier element : " << pile3.peek() << endl;


    // Test avec un grand nombre d'objets
    cout << "\n=== TEST GRAND NOMBRE D'ELEMENTS ===" << endl;

    Stack<int> grandePile(100000);

    for (int i = 0; i < 100000; i++) {
        grandePile.push(i);
    }

    cout << "Nombre d'elements : " << grandePile.size() << endl;
    cout << "Dernier element : " << grandePile.peek() << endl;

    cout << "\nFin du programme." << endl;

    return 0;
}
