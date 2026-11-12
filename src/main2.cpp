
#include <iostream>
using namespace std;

template <typename T, int N, int M>
class Matrice {
private:
    T data[N][M];

public:
    // Constructeur par defaut
    Matrice() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                data[i][j] = 0;
            }
        }
    }

    // Constructeur avec liste d'initialisation
    Matrice(T valeurs[N][M]) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                data[i][j] = valeurs[i][j];
            }
        }
    }

    // Surcharge de +
    Matrice operator+(const Matrice& autre) const {
        Matrice resultat;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                resultat.data[i][j] = data[i][j] + autre.data[i][j];
            }
        }

        return resultat;
    }

    // Surcharge de -
    Matrice operator-(const Matrice& autre) const {
        Matrice resultat;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                resultat.data[i][j] = data[i][j] - autre.data[i][j];
            }
        }

        return resultat;
    }

    // Surcharge de * pour multiplication matricielle
    template <int P>
    Matrice<T, N, P> operator*(const Matrice<T, M, P>& autre) const {
        Matrice<T, N, P> resultat;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < P; j++) {
                for (int k = 0; k < M; k++) {
                    resultat.data[i][j] += data[i][k] * autre.data[k][j];
                }
            }
        }

        return resultat;
    }

    // Fonction amie pour afficher la matrice
    friend ostream& operator<<(ostream& os, const Matrice& mat) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                os << mat.data[i][j] << "\t";
            }
            os << endl;
        }

        return os;
    }
};

int main() {

    // MATRICES D'ENTIERS
    cout << "=== MATRICES D'ENTIERS ===" << endl;

    Matrice<int, 2, 2> A;
    Matrice<int, 2, 2> B;

    int valeursA[2][2] = {
        {1, 2},
        {3, 4}
    };

    int valeursB[2][2] = {
        {5, 6},
        {7, 8}
    };

    A = Matrice<int, 2, 2>(valeursA);
    B = Matrice<int, 2, 2>(valeursB);

    cout << "Matrice A :" << endl;
    cout << A;

    cout << "Matrice B :" << endl;
    cout << B;

    cout << "Addition A + B :" << endl;
    cout << A + B;

    cout << "Soustraction A - B :" << endl;
    cout << A - B;

    cout << "Multiplication A * B :" << endl;
    cout << A * B;


    // MATRICES DOUBLE
    cout << "\n=== MATRICES DOUBLE ===" << endl;

    double valeursC[2][2] = {
        {1.5, 2.5},
        {3.5, 4.5}
    };

    double valeursD[2][2] = {
        {2.0, 1.0},
        {1.0, 2.0}
    };

    Matrice<double, 2, 2> C(valeursC);
    Matrice<double, 2, 2> D(valeursD);

    cout << "Matrice C :" << endl;
    cout << C;

    cout << "Matrice D :" << endl;
    cout << D;

    cout << "Addition C + D :" << endl;
    cout << C + D;

    cout << "Soustraction C - D :" << endl;
    cout << C - D;

    cout << "Multiplication C * D :" << endl;
    cout << C * D;

    return 0;
}
