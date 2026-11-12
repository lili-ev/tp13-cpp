
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstddef>

using namespace std;

template <typename T>
class ArrayDyn {
private:
    T* data;
    size_t taille;
    size_t capacite;

    // Agrandir le tableau
    void agrandir() {
        size_t nouvelleCapacite = (capacite == 0) ? 1 : capacite * 2;

        T* nouveau = new T[nouvelleCapacite];

        for (size_t i = 0; i < taille; i++) {
            nouveau[i] = data[i];
        }

        delete[] data;
        data = nouveau;
        capacite = nouvelleCapacite;
    }

public:
    // Constructeur par defaut
    ArrayDyn() {
        data = nullptr;
        taille = 0;
        capacite = 0;
    }

    // Constructeur avec capacite initiale
    ArrayDyn(size_t c) {
        taille = 0;
        capacite = c;
        data = (capacite > 0) ? new T[capacite] : nullptr;
    }

    // Constructeur de copie
    ArrayDyn(const ArrayDyn& autre) {
        taille = autre.taille;
        capacite = autre.capacite;

        data = (capacite > 0) ? new T[capacite] : nullptr;

        for (size_t i = 0; i < taille; i++) {
            data[i] = autre.data[i];
        }
    }

    // Operateur d'affectation
    ArrayDyn& operator=(const ArrayDyn& autre) {
        if (this != &autre) {
            T* nouveau = (autre.capacite > 0)
                         ? new T[autre.capacite] : nullptr;

            for (size_t i = 0; i < autre.taille; i++) {
                nouveau[i] = autre.data[i];
            }

            delete[] data;

            data = nouveau;
            taille = autre.taille;
            capacite = autre.capacite;
        }

        return *this;
    }

    // Destructeur
    ~ArrayDyn() {
        delete[] data;
    }

    // Ajouter un element
    void push_back(const T& element) {
        if (taille == capacite) {
            agrandir();
        }

        data[taille] = element;
        taille++;
    }

    // Supprimer le dernier element
    void pop_back() {
        if (taille == 0) {
            throw out_of_range("Tableau vide !");
        }

        taille--;
    }

    // Acces avec controle des bornes
    T& operator[](size_t indice) {
        if (indice >= taille) {
            throw out_of_range("Indice invalide !");
        }

        return data[indice];
    }

    // Version const
    const T& operator[](size_t indice) const {
        if (indice >= taille) {
            throw out_of_range("Indice invalide !");
        }

        return data[indice];
    }

    // Classe Iterator
    class Iterator {
    private:
        T* ptr;

    public:
        Iterator(T* p) {
            ptr = p;
        }

        // Acceder a l'element
        T& operator*() {
            return *ptr;
        }

        // Avancer
        Iterator& operator++() {
            ++ptr;
            return *this;
        }

        // Reculer
        Iterator& operator--() {
            --ptr;
            return *this;
        }

        // Comparer
        bool operator!=(const Iterator& autre) const {
            return ptr != autre.ptr;
        }
    };

    // Debut du tableau
    Iterator begin() {
        return Iterator(data);
    }

    // Fin du tableau
    Iterator end() {
        return Iterator(data + taille);
    }
};

// Classe Produit
class Produit {
public:
    string nom;
    double prix;

    // Constructeur par defaut
    Produit() {
        nom = "";
        prix = 0;
    }

    // Constructeur avec parametres
    Produit(string n, double p) {
        nom = n;
        prix = p;
    }
};

int main() {

    // Test avec int
    cout << "=== Tableau d'entiers ===" << endl;

    ArrayDyn<int> nombres;

    nombres.push_back(10);
    nombres.push_back(20);
    nombres.push_back(30);

    for (auto& e : nombres) {
        cout << e << " ";
    }

    cout << endl;


    // Test avec string
    cout << "\n=== Tableau de chaines ===" << endl;

    ArrayDyn<string> noms;

    noms.push_back("Ali");
    noms.push_back("Sara");
    noms.push_back("Amine");

    for (auto& e : noms) {
        cout << e << " ";
    }

    cout << endl;


    // Test avec Produit
    cout << "\n=== Tableau de produits ===" << endl;

    ArrayDyn<Produit> produits;

    produits.push_back(Produit("PC", 5000));
    produits.push_back(Produit("Telephone", 3000));

    for (auto& e : produits) {
        cout << e.nom << " : " << e.prix << " DH" << endl;
    }


    // Test du constructeur de copie
    cout << "\n=== Test de copie ===" << endl;

    ArrayDyn<int> copie = nombres;

    for (auto& e : copie) {
        cout << e << " ";
    }

    cout << endl;


    // Test de pop_back
    nombres.pop_back();

    cout << "\nApres suppression du dernier element :" << endl;

    for (auto& e : nombres) {
        cout << e << " ";
    }

    cout << endl;

    return 0;
}
