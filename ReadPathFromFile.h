//
// Created by czerw on 30/11/2023.
//

#ifndef PEA_PROJEKT_2_READPATHFROMFILE_H
#define PEA_PROJEKT_2_READPATHFROMFILE_H

#include "Matrix.h"

class ReadPathFromFile {
public:
    int **distanceMatrix;
    int *path;
    int distance;
    int numberOfCities;

    explicit ReadPathFromFile(Matrix*);
    ~ReadPathFromFile();
    void readFromFile(const std::string &filename);
    void calculateDistance();
    void display();
};


#endif //PEA_PROJEKT_2_READPATHFROMFILE_H
