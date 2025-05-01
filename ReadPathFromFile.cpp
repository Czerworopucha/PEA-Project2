//
// Created by czerw on 30/11/2023.
//

#include "ReadPathFromFile.h"

ReadPathFromFile::ReadPathFromFile(Matrix *matrixPointer) {
    numberOfCities = 0;
    distanceMatrix = matrixPointer->distanceMatrix;
    path = nullptr;
    distance = 0;
}

ReadPathFromFile::~ReadPathFromFile() {
    for (int i = 0; i < numberOfCities; i++) {
        delete[] distanceMatrix[i];

    }
    delete[] distanceMatrix;
    delete[] path;
}

/* Zczytanie ścieżki z pliku,
 * bedacej w wymaganym formacie:
 * liczba wierzcholkow \n
 * sciezka
 */
void ReadPathFromFile::readFromFile(const std::string &filename) {
    std::ifstream file;
    file.open(filename);
    if (file.good()) {
        file >> numberOfCities;
        path = new int[numberOfCities + 1];
        int next;
        for (int i = 0; i < numberOfCities + 1; i++) {
            file >> next;
            path[i] = next;
        }
        file.close();
    } else {
        std::cout << "Blad wczytywania z pliku" << std::endl;
    }
}

/* Obliczenie kosztu na podstawie zczytanej sciezki i wczytanego grafu
 *
 */
void ReadPathFromFile::calculateDistance() {
    int curCity;
    int nextCity;

    for(int i = 0; i < numberOfCities; i++){
        curCity = path[i];
        nextCity = path[i+1];
        distance += distanceMatrix[curCity][nextCity];
    }
}

/* Wyswietlenie obliczonego wczesniej kosztu
 *
 */
void ReadPathFromFile::display() {
    std::cout << std::endl;
    std::cout << "Koszt: " << distance;
}
