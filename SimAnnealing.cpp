//
// Created by czerw on 23/11/2023.
//

#include "SimAnnealing.h"


/* TODO
 *
 */

SimAnnealing::SimAnnealing(Matrix *matrixPointer, int stopTime) {
    numberOfCities = matrixPointer->numberOfCities;
    distanceMatrix = matrixPointer->distanceMatrix;
    coolingRate = 0;
    temperature = CalculateStartingTemperature();
    bestSolution = new int[numberOfCities + 1];
    currentSolution = new int[numberOfCities + 1];
    newSolution = new int[numberOfCities + 1];
    bestDistance = 0;
    currentDistance = 0;
    newDistance = 0;
    iterations = 1000;
    BestSolutionFoundTime = 0;

    if (stopTime == 1) {
        maxTime = 120;
    } else if (stopTime == 2) {
        maxTime = 240;
    } else if (stopTime == 3) {
        maxTime = 360;
    } else {
        if (numberOfCities < 150) {
            maxTime = 120;
        } else if (numberOfCities < 250) {
            maxTime = 240;
        } else {
            maxTime = 360;
        }
    }
}

SimAnnealing::~SimAnnealing() {
    delete[] bestSolution;
    delete[] currentSolution;
    delete[] newSolution;
    for (int i = 0; i < numberOfCities; i++) {
        delete[] distanceMatrix[i];

    }
    delete[] distanceMatrix;
}

/* Algorytm Symulowanego wyzarzania,
 * dokladny opis dzialania w sprawozdaniu
 */
void SimAnnealing::RunSimAnnealing() {
    startingSolution();
    std::chrono::time_point breakPoint = std::chrono::system_clock::now() + std::chrono::duration_cast<std::chrono::seconds>(std::chrono::duration<int>(maxTime));
    std::random_device rd;
    std::mt19937 generate(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    auto startTime = std::chrono::system_clock::now();

    do{
        for (int i = 0; i < iterations; i ++) {
            swapRandomCities();
            CalculateDistance();
            //Porownanie i zmiana najlepszego rozwiazania
            if (newDistance < currentDistance || exp(-(newDistance - currentDistance) / temperature) > dist(generate)) {
                for(int j = 0; j < numberOfCities + 1; j++){
                    currentSolution[j] = newSolution[j];
                }
                currentDistance = newDistance;
            }
            if (currentDistance < bestDistance){
                for(int j = 0; j < numberOfCities + 1; j++){
                    bestSolution[j] = currentSolution[j];
                }
                bestDistance = currentDistance;
                BestSolutionFoundTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - startTime).count();
                rozwiazania.push_back(bestDistance);
                czasy.push_back(BestSolutionFoundTime);
            }
        }
        cooling();
    } while ((breakPoint - std::chrono::system_clock::now()).count() > 0);
    //temperature > 0.01 &&
    //(breakPoint - std::chrono::system_clock::now()).count() > 0
}

/* Metoda Zachłanna:
 * Od wierzchołka startowego (0), wybieramy drogę o najmniejszej wadze do nastepnego wierzcholka, i tak do konca.
 */
void SimAnnealing::startingSolution() {
    //Inicjalizacja
    int curCity = 0;
    int nextCity = 0;
    int best;
    bool *visited = new bool [numberOfCities];
    for(int i = 0; i < numberOfCities; i++){
        visited[i] = false;
    }

    //Sciezka metoda zachlanna
    for(int i = 0; i < numberOfCities; i++){
        visited[curCity] = true;
        best = INT_MAX;
        currentSolution[i] = curCity;
        for(int j = 0; j < numberOfCities; j++){
            if((distanceMatrix[curCity][j] < best) && !visited[j]){
                best = distanceMatrix[curCity][j];
                nextCity = j;
            }
        }
        if(best == INT_MAX){
            //dopisanie 0 na koniec sciezki zeby byla petla
            int lastCity = currentSolution[numberOfCities-1];
            currentDistance += distanceMatrix[lastCity][0];
            currentSolution[numberOfCities] = 0;
            break;
        }
        currentDistance += best;
        curCity = nextCity;
    }

    bestDistance = currentDistance;
    for(int j = 0; j < numberOfCities + 1; j++){
        bestSolution[j] = currentSolution[j];
    }
    rozwiazania.push_back(bestDistance);
    czasy.push_back(BestSolutionFoundTime);

    DisplayResults();
}

/* Zamiana losowych miast w sciezce:
 * Losujemy 2 miasta z aktualnej sciezki (poza startowym i koncowym),
 * Zapisujemy sciezke z zamienionymi miastami do newSolution,
 * Porownanie czy jest lepsze czy gorsza od starej,
 * if newDistance < currentDistance {
 * currentSolution = newSolution
 * currentDistance = newDistance
 * }
 */
void SimAnnealing::swapRandomCities() {
    //Losowanie z miast
    std::random_device rng;
    std::mt19937 gen(rng());
    std::uniform_int_distribution<> distribution(1, numberOfCities-1);
    int swap1 = distribution(gen);
    int swap2 = distribution(gen);
    //Zabezpieczenie zeby nie wylosowaly sie 2 te same
    while(swap2 == swap1){
        swap2 = distribution(gen);
    }

    //Zamiana w tablicy
    //newSolution = currentSolution;
    //std::copy(currentSolution, currentSolution + numberOfCities, newSolution);
    for(int i = 0; i<numberOfCities + 1; i++){
        newSolution[i] = currentSolution[i];
    }
    newSolution[swap1] = currentSolution[swap2];
    newSolution[swap2] = currentSolution[swap1];

}

/* Wyświetlanie potrzebnych danych o przebiegu algorytmu
 */
void SimAnnealing::DisplayResults() {
    std::cout << std::endl;
    std::cout << "Temperatura: " << temperature << std::endl;
    std::cout << "Wartosc wyrazenia: " << exp(-1/temperature) << std::endl;
    std::cout << "Wspolczynnik chlodzenia: " << coolingRate << std::endl;
    std::cout << "Sciezka:" << std::endl;
    for (int i = 0; i < numberOfCities + 1; i++){
        std::cout << "[" << bestSolution[i] << "] ";
    }
    std::cout << std::endl;
    std::cout << "Koszt: " << bestDistance << std::endl;
    std::cout << "Czas po ktorym znaleziono najlepsze rozwiazanie: " << BestSolutionFoundTime << std::endl;
}

/* Obliczanie temperatury startowej,
 * wzór wymyślony na podstawie przeprowadzania testów, dla jakich temperatur startowych działa dobrze
 */
int SimAnnealing::CalculateStartingTemperature() {
    int temp = 100*numberOfCities;
    return temp;
}

/* Policzenie dlugosci nowej sciezki,
 */
void SimAnnealing::CalculateDistance() {
    int prevCity;
    int nextCity;
    newDistance = 0;

    for(int i = 0; i < numberOfCities; i++){
        prevCity = newSolution[i];
        nextCity = newSolution[i+1];
        newDistance += distanceMatrix[prevCity][nextCity];
    }
}

/*
 * Wzór funkcji schładzającej
 */
void SimAnnealing::cooling() {

    temperature = temperature * coolingRate;
    /*
    else if(coolingFactor == 2){
        temperature = temperature/((1+coolingRate)*temperature);
    }
     */
}

/* Wybór współczynnika schładzania a na podstawie wyboru z menu, bądź automatyczny jeśli nie wybrano
 */
void SimAnnealing::coolingChoice(int cF) {
     if(cF == 1){
         //coolingRate = 0.999;
         coolingRate = 0.99987;
         //iterations = 1000;
     }
     else if(cF == 2){
         //coolingRate = 0.99935;
         coolingRate = 0.99993;
         //iterations = 1000;
     }
     else if(cF == 3){
         //coolingRate = 0.9995;
         coolingRate = 0.99994;
         //iterations = 1000;
     }
     else if(cF == 4){
         coolingRate = 0.9994;
     }
     else{
         if (numberOfCities < 150) {
             coolingRate = 0.99987;
         } else if (numberOfCities < 250) {
             coolingRate = 0.99993;
         } else {
             coolingRate = 0.99994;
         }
     }
     /*
     else if(coolingFactor == 2){
         coolingRate = 0.00005;
         iterations = 1;
     }
      */
}

/*
 * Zapis ścieżki i liczby wierzchołków do pliku
 */
void SimAnnealing::saveToFile() {
    std::ofstream fileName;
    fileName.open("wynik.txt", std::ios::app);
    fileName << "--------------------\n";
    fileName << numberOfCities << "\n";
    for (int i = 0; i < numberOfCities + 1; i++) {
        fileName << " " << bestSolution[i];
    }
    fileName << "\n";
    fileName.close();

    std::ofstream fileName1;
    fileName1.open("czasy.txt", std::ios::app);
    fileName1 << "--------------------\n";
    for(int i = 0; i < rozwiazania.size(); i++){
        fileName1 << rozwiazania[i] << "\n";
        fileName1 << czasy[i] << "\n";
    }
    fileName1 << "\n";
    fileName1.close();
}

/*
 * używana tylko do testów, niedostepna w normalnym użytkowaniu
 */
void SimAnnealing::tests() {
    saveToFile();
    std::ofstream fileName;
    fileName.open("tests.txt", std::ios::app);
    fileName << "--------------------\n";
    fileName << numberOfCities << "\n";
    fileName << coolingRate << "\n";
    fileName << temperature << "\n";
    fileName << exp(-1/temperature) << "\n";
    fileName << bestDistance << "\n";
    fileName << BestSolutionFoundTime << "\n";
    fileName.close();
}

/*
 * Funkcja dopisana w celu znalezienia jak najlepszych możliwych wyników dla każdego grafu,
 * Testy przeprowadzane były z założeniem, że każda ścieżka zaczyna się w wierzchołku 0.
 * Sprawdzamy ścieżki metoda zachlanna dla wszystkich wierzchołków jako startowe i bierzemy najlepszą
 */
void SimAnnealing::startingSolutionVer2() {
    bestDistance = INT_MAX;
    bool *visited = new bool[numberOfCities];
    for(int k = 0; k < numberOfCities; k++) {
        int curCity = k;
        int nextCity = 0;
        int best;
        currentDistance = 0;
        for (int i = 0; i < numberOfCities; i++) {
            visited[i] = false;
        }

        //Sciezka metoda zachlanna
        for (int i = 0; i < numberOfCities; i++) {
            visited[curCity] = true;
            best = INT_MAX;
            currentSolution[i] = curCity;
            for (int j = 0; j < numberOfCities; j++) {
                if ((distanceMatrix[curCity][j] < best) && !visited[j]) {
                    best = distanceMatrix[curCity][j];
                    nextCity = j;
                }
            }
            if (best == INT_MAX) {
                //dopisanie 0 na koniec sciezki zeby byla petla
                int lastCity = currentSolution[numberOfCities - 1];
                currentDistance += distanceMatrix[lastCity][k];
                currentSolution[numberOfCities] = k;
                break;
            }
            currentDistance += best;
            curCity = nextCity;
        }
        if(currentDistance < bestDistance) {
            bestDistance = currentDistance;
            for (int j = 0; j < numberOfCities + 1; j++) {
                bestSolution[j] = currentSolution[j];
            }
        }
    }
    DisplayResults();
}
