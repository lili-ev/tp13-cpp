
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <concepts>

using namespace std;

// Concept Sortable
template<typename T>
concept Sortable = requires(T a, T b) {
    { a < b } -> convertible_to<bool>;
};

// Foncteur pour le tri croissant
struct Asc {
    template<typename T>
    bool operator()(const T& a, const T& b) const {
        return a < b;
    }
};

// Foncteur pour le tri decroissant
struct Desc {
    template<typename T>
    bool operator()(const T& a, const T& b) const {
        return a > b;
    }
};

// Fonction quickSort
template<Sortable T, typename Comp = less<T>>
void quickSort(vector<T>& v, Comp comp = Comp{}) {
    sort(v.begin(), v.end(), comp);
}

// Structure utilisateur
struct Etudiant {
    string nom;
    int note;

    bool operator<(const Etudiant& autre) const {
        return note < autre.note;
    }

    bool operator>(const Etudiant& autre) const {
        return note > autre.note;
    }
};

// Fonction pour verifier si un vecteur est trie
template<typename T, typename Comp>
bool estTrie(const vector<T>& v, Comp comp) {
    return is_sorted(v.begin(), v.end(), comp);
}

int main() {

    // Test avec des entiers
    cout << "=== TRI DES ENTIERS ===" << endl;

    vector<int> nombres = {5, 2, 8, 1, 9};

    quickSort(nombres, Asc{});

    for (int n : nombres) {
        cout << n << " ";
    }

    cout << endl;

    cout << "Test : "
         << (estTrie(nombres, Asc{}) ? "REUSSI" : "ECHEC")
         << endl;


    // Test avec des chaines
    cout << "\n=== TRI DES CHAINES ===" << endl;

    vector<string> noms = {"Sara", "Ali", "Youssef", "Amine"};

    quickSort(noms, Desc{});

    for (string nom : noms) {
        cout << nom << " ";
    }

    cout << endl;

    cout << "Test : "
         << (estTrie(noms, Desc{}) ? "REUSSI" : "ECHEC")
         << endl;


    // Test avec une structure utilisateur
    cout << "\n=== TRI DES ETUDIANTS ===" << endl;

    vector<Etudiant> etudiants = {
        {"Sara", 15},
        {"Ali", 12},
        {"Youssef", 18},
        {"Amine", 10}
    };

    quickSort(etudiants, Asc{});

    for (const Etudiant& e : etudiants) {
        cout << e.nom << " : " << e.note << endl;
    }

    cout << "Test : "
         << (estTrie(etudiants, Asc{}) ? "REUSSI" : "ECHEC")
         << endl;

    return 0;
}
