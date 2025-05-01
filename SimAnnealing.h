//
// Created by czerw on 23/11/2023.
//

#ifndef PEA_PROJEKT_2_SIMANNEALING_H
#define PEA_PROJEKT_2_SIMANNEALING_H

#include "Matrix.h"
#include "chrono"
#include "random"
#include "fstream"
#include "iostream"
#include "vector"

class SimAnnealing {
public:
    int numberOfCities;
    int **distanceMatrix;
    double temperature;
    double coolingRate; //stała a
    int *bestSolution;
    int *currentSolution;
    int *newSolution;
    double bestDistance;
    double currentDistance;
    double newDistance;
    int maxTime;
    int iterations;
    int BestSolutionFoundTime;
    std::vector<int> rozwiazania;
    std::vector<int> czasy;

    explicit SimAnnealing(Matrix*, int);
    ~SimAnnealing();
    void RunSimAnnealing();
    void startingSolution();
    void swapRandomCities();
    void DisplayResults();
    int CalculateStartingTemperature();
    void CalculateDistance();
    void cooling();
    void coolingChoice(int);
    void saveToFile();

    void tests();
    void startingSolutionVer2();

};


#endif //PEA_PROJEKT_2_SIMANNEALING_H
