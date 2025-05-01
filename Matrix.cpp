//
// Created by czerw on 23/11/2023.
//

#include "Matrix.h"

Matrix::Matrix() {
    numberOfCities = 0;
    distanceMatrix = nullptr;
}

Matrix::~Matrix() {
    for (int i = 0; i < numberOfCities; i++) {
        delete[] distanceMatrix[i];

    }
    delete[] distanceMatrix;
}

/* Wczytywanie grafu z pliku .atsp jako macierz sąsiedztwa
 *
 */
void Matrix::LoadMatrixFromFile(const std::string &filename) {

    std::ifstream file(filename);
    if (file.good()) {
        std::string data;

        do {
            file >> data;
        } while (data != "DIMENSION:");
        file >> numberOfCities;

        do {
            file >> data;
        } while (data != "EDGE_WEIGHT_SECTION");

        distanceMatrix = new int *[numberOfCities];
        for (int i = 0; i < numberOfCities; i++) {
            distanceMatrix[i] = new int[numberOfCities];
        }

        int distance;
        for (int i = 0; i < numberOfCities; i++) {
            for (int j = 0; j < numberOfCities; j++) {
                file >> distance;
                distanceMatrix[i][j] = distance;
            }
        }
        file.close();
    } else {
        std::cout << "Blad wczytywania z pliku" << std::endl;
    }
}

/* Wyswietlanie wczytanej macierzy,
 * uzywane tylko do debugu w celu sprawdzenia poprawnosci wczytywania
 */
void Matrix::DisplayMatrix() {
    std::cout << "Ilosc miast: " << numberOfCities << std::endl;
    for (int i = 0; i < numberOfCities; i++) {
        for (int j = 0; j < numberOfCities; j++) {
            std::cout << "[" << distanceMatrix[i][j] << "] ";
        }
        std::cout << std::endl;
    }
}
