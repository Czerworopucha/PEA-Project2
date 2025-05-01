//
// Created by czerw on 23/11/2023.
//

#ifndef PEA_PROJEKT_2_MATRIX_H
#define PEA_PROJEKT_2_MATRIX_H

#include "fstream"
#include "iostream"

class Matrix {
public:
    int numberOfCities;
    int **distanceMatrix;

    Matrix();
    ~Matrix();
    void LoadMatrixFromFile(const std::string &filename);
    void DisplayMatrix();
};


#endif //PEA_PROJEKT_2_MATRIX_H
